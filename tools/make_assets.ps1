param(
    [Parameter(Mandatory = $true)][string]$Video,
    [Parameter(Mandatory = $true)][string]$Mask,
    [Parameter(Mandatory = $true)][string]$OutDir,
    [double]$Fps = 30
)

$ErrorActionPreference = "Stop"

if (-not (Get-Command ffmpeg -ErrorAction SilentlyContinue)) { throw "ffmpeg not found in PATH" }
if (-not (Get-Command ffprobe -ErrorAction SilentlyContinue)) { throw "ffprobe not found in PATH" }

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$fs = [IO.File]::OpenRead($Mask)
$b = New-Object byte[] 12
[void]$fs.Read($b, 0, 12)
$fs.Close()
$magic = [BitConverter]::ToUInt32($b, 0)
if ($magic -ne 0x314B534D) { throw "bad mask magic 0x$($magic.ToString('X8'))" }
$W = [BitConverter]::ToInt32($b, 4)
$H = [BitConverter]::ToInt32($b, 8)
if ($W -lt 4 -or $H -lt 4 -or $W -gt 4096 -or $H -gt 4096) { throw "bad mask size $W x $H" }
Write-Host "mask: $W x $H"

$framesDir = Join-Path $OutDir "frames"
New-Item -ItemType Directory -Force -Path $framesDir | Out-Null

& ffmpeg -y -v error -i $Video -vf "fps=$Fps,scale=${W}:${H}:flags=lanczos,colorkey=0x00FE00:0.12:0.06" -start_number 0 (Join-Path $framesDir "f%04d.png")
if ($LASTEXITCODE -ne 0) { throw "ffmpeg frame extraction failed" }

$frames = @(Get-ChildItem $framesDir -Filter "f*.png" | Sort-Object Name)
if ($frames.Count -eq 0) { throw "no frames extracted" }
Write-Host "frames: $($frames.Count)"

$i = 0
foreach ($fr in $frames) {
    $pal = Join-Path $framesDir ("p{0:d4}.png" -f $i)
    $tmp = Join-Path $framesDir ("t{0:d4}.png" -f $i)
    & ffmpeg -y -v error -i $fr.FullName -vf "palettegen=max_colors=256" $pal
    if ($LASTEXITCODE -ne 0) { throw "palettegen failed on $($fr.Name)" }
    & ffmpeg -y -v error -i $fr.FullName -i $pal -lavfi "paletteuse=dither=sierra2_4a" $tmp
    if ($LASTEXITCODE -ne 0) { throw "paletteuse failed on $($fr.Name)" }
    Move-Item $tmp $fr.FullName -Force
    Remove-Item $pal -Force
    $i++
}

$frameDur = [uint32][math]::Floor(10000000 / $Fps)
$frames = @(Get-ChildItem $framesDir -Filter "f*.png" | Sort-Object Name)
$packPath = Join-Path $OutDir "musordrop.pack"
$fs = [IO.File]::Create($packPath)
$bw = New-Object IO.BinaryWriter($fs)
$sizes = @($frames | ForEach-Object { [uint32]$_.Length })
$bw.Write([uint32]0x504B534D)
$bw.Write([uint32]$sizes.Count)
$bw.Write([int32]$W)
$bw.Write([int32]$H)
$bw.Write($frameDur)
foreach ($s in $sizes) { $bw.Write($s) }
foreach ($fr in $frames) { $bw.Write([IO.File]::ReadAllBytes($fr.FullName)) }
$bw.Close()
$fs.Close()

Remove-Item $framesDir -Recurse -Force
Write-Host "pack: $((Get-Item $packPath).Length) bytes, $($sizes.Count) frames, $frameDur us/frame"

$hasAudio = (& ffprobe -v error -select_streams a -show_entries stream=codec_type -of csv=p=0 $Video) -match "audio"
if (-not $hasAudio) { throw "no audio stream in $Video" }
& ffmpeg -y -v error -i $Video -vn -acodec pcm_s16le -ar 48000 -ac 2 (Join-Path $OutDir "musordrop.wav")
if ($LASTEXITCODE -ne 0) { throw "audio extraction failed" }
Write-Host "wav: $((Get-Item (Join-Path $OutDir 'musordrop.wav')).Length) bytes"

Copy-Item $Mask (Join-Path $OutDir "musordrop_mask.bin") -Force
Write-Host "mask copied"
