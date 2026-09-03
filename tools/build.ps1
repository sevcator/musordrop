param(
    [string]$OutDir = "build"
)

$ErrorActionPreference = "Stop"

New-Item -ItemType Directory -Force -Path $OutDir | Out-Null
Push-Location $OutDir
try {
    $prefix = ""
    if (Get-Command "x86_64-w64-mingw32-windres" -ErrorAction SilentlyContinue) {
        $prefix = "x86_64-w64-mingw32-"
    } elseif (-not (Get-Command "windres" -ErrorAction SilentlyContinue)) {
        throw "windres not found in PATH"
    }
    Copy-Item ../src/musordrop.rc musordrop.rc -Force
    & "$($prefix)windres" musordrop.rc -O coff -o musordrop_res.o
    if ($LASTEXITCODE -ne 0) { throw "windres failed" }
    Remove-Item musordrop.rc -Force
    Write-Host "resources: $((Get-Item musordrop_res.o).Length) bytes"

    & "$($prefix)gcc" ../src/musordrop.c musordrop_res.o -o musordrop.exe -O2 -mwindows -lgdi32 -lwinmm -lole32 -loleaut32 -luuid -ldwmapi -lversion -lmsimg32
    if ($LASTEXITCODE -ne 0) { throw "gcc failed" }
    Remove-Item musordrop_res.o -Force
    Write-Host "exe: $((Get-Item musordrop.exe).Length) bytes"

    if (Get-Command upx -ErrorAction SilentlyContinue) {
        & upx --best --lzma musordrop.exe | Out-Null
        if ($LASTEXITCODE -ne 0) { throw "upx failed" }
        Write-Host "packed: $((Get-Item musordrop.exe).Length) bytes"
    } else {
        Write-Host "upx not found, skipping compression"
    }
} finally {
    Pop-Location
}
