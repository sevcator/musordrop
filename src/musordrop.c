#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <dwmapi.h>
#include <shellapi.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <stdarg.h>
#include <math.h>

#ifndef PROCESS_SUSPEND_RESUME
#define PROCESS_SUSPEND_RESUME 0x0800
#endif

#define WM_APP_END (WM_APP + 1)
#define STATE_MAGIC 0x5052444Du
#define MAX_FROZEN 256
#define WATCHDOG_MS (15 * 60 * 1000)
#define OVERLAY_MAX_PIXELS 1000000.0

typedef LONG NTSTATUS;
typedef NTSTATUS (NTAPI *PFN_NtSuspendProcess)(HANDLE);
typedef NTSTATUS (NTAPI *PFN_NtResumeProcess)(HANDLE);
typedef BOOL (WINAPI *PFN_PlaySoundW)(LPCWSTR, HMODULE, DWORD);
typedef DWORD (WINAPI *PFN_TimeBeginPeriod)(UINT);
typedef DWORD (WINAPI *PFN_TimeEndPeriod)(UINT);

typedef struct GpBitmap GpBitmap;
typedef struct IStreamX IStreamX;
typedef struct GpRectX { INT X, Y, Width, Height; } GpRectX;
typedef struct BmpDataX {
    UINT Width;
    UINT Height;
    INT Stride;
    INT PixelFormat;
    VOID *Scan0;
    INT_PTR Reserved;
} BmpDataX;
typedef int GpStatus;
typedef GpStatus (WINAPI *PFN_BmpFromStream)(IStreamX *, GpBitmap **);
typedef GpStatus (WINAPI *PFN_BmpLock)(GpBitmap *, const GpRectX *, UINT, INT, BmpDataX *);
typedef GpStatus (WINAPI *PFN_BmpUnlock)(GpBitmap *, BmpDataX *);
typedef GpStatus (WINAPI *PFN_ImgDispose)(GpBitmap *);
typedef struct {
    UINT32 GdiplusVersion;
    void *DebugEventCallback;
    BOOL SuppressBackgroundThread;
    BOOL SuppressExternalCodecs;
} GdipStartIn;
typedef GpStatus (WINAPI *PFN_GdipStart)(ULONG_PTR *, const GdipStartIn *, void *);
typedef void (WINAPI *PFN_GdipStop)(ULONG_PTR);
typedef struct IStreamXVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IStreamX *, REFIID, void **);
    ULONG (STDMETHODCALLTYPE *AddRef)(IStreamX *);
    ULONG (STDMETHODCALLTYPE *Release)(IStreamX *);
    void *pad[11];
} IStreamXVtbl;
struct IStreamX { IStreamXVtbl *lpVtbl; };

enum { MODE_PRANK = 0 };

static const CLSID k_CLSID_MMDeviceEnumerator = {0xBCDE0395,0xE52F,0x467C,{0x8E,0x3D,0xC4,0x57,0x92,0x91,0x69,0x2E}};
static const IID k_IID_IMMDeviceEnumerator = {0xA95664D2,0x9614,0x4F35,{0xA7,0x46,0xDE,0x8D,0xB6,0x36,0x17,0xE6}};
static const IID k_IID_IAudioEndpointVolume = {0x5CDF2C82,0x841E,0x4546,{0x97,0x22,0x0C,0xF7,0x40,0x78,0x22,0x9A}};

typedef struct IMMDeviceX IMMDeviceX;
typedef struct IMMDeviceEnumeratorX IMMDeviceEnumeratorX;
typedef struct IAudioEndpointVolumeX IAudioEndpointVolumeX;

typedef struct IMMDeviceXVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IMMDeviceX *, REFIID, void **);
    ULONG (STDMETHODCALLTYPE *AddRef)(IMMDeviceX *);
    ULONG (STDMETHODCALLTYPE *Release)(IMMDeviceX *);
    HRESULT (STDMETHODCALLTYPE *Activate)(IMMDeviceX *, REFIID, DWORD, PROPVARIANT *, void **);
    HRESULT (STDMETHODCALLTYPE *OpenPropertyStore)(IMMDeviceX *, DWORD, void **);
    HRESULT (STDMETHODCALLTYPE *GetId)(IMMDeviceX *, LPWSTR *);
    HRESULT (STDMETHODCALLTYPE *GetState)(IMMDeviceX *, DWORD *);
} IMMDeviceXVtbl;
struct IMMDeviceX { IMMDeviceXVtbl *lpVtbl; };

typedef struct IMMDeviceEnumeratorXVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IMMDeviceEnumeratorX *, REFIID, void **);
    ULONG (STDMETHODCALLTYPE *AddRef)(IMMDeviceEnumeratorX *);
    ULONG (STDMETHODCALLTYPE *Release)(IMMDeviceEnumeratorX *);
    HRESULT (STDMETHODCALLTYPE *EnumAudioEndpoints)(IMMDeviceEnumeratorX *, DWORD, DWORD, void **);
    HRESULT (STDMETHODCALLTYPE *GetDefaultAudioEndpoint)(IMMDeviceEnumeratorX *, DWORD, DWORD, IMMDeviceX **);
    HRESULT (STDMETHODCALLTYPE *GetDevice)(IMMDeviceEnumeratorX *, LPCWSTR, IMMDeviceX **);
    HRESULT (STDMETHODCALLTYPE *RegisterEndpointNotificationCallback)(IMMDeviceEnumeratorX *, void *);
    HRESULT (STDMETHODCALLTYPE *UnregisterEndpointNotificationCallback)(IMMDeviceEnumeratorX *, void *);
} IMMDeviceEnumeratorXVtbl;
struct IMMDeviceEnumeratorX { IMMDeviceEnumeratorXVtbl *lpVtbl; };

typedef struct IAudioEndpointVolumeXVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IAudioEndpointVolumeX *, REFIID, void **);
    ULONG (STDMETHODCALLTYPE *AddRef)(IAudioEndpointVolumeX *);
    ULONG (STDMETHODCALLTYPE *Release)(IAudioEndpointVolumeX *);
    HRESULT (STDMETHODCALLTYPE *RegisterControlChangeNotify)(IAudioEndpointVolumeX *, void *);
    HRESULT (STDMETHODCALLTYPE *UnregisterControlChangeNotify)(IAudioEndpointVolumeX *, void *);
    HRESULT (STDMETHODCALLTYPE *GetChannelCount)(IAudioEndpointVolumeX *, UINT *);
    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevel)(IAudioEndpointVolumeX *, float, LPCGUID);
    HRESULT (STDMETHODCALLTYPE *SetMasterVolumeLevelScalar)(IAudioEndpointVolumeX *, float, LPCGUID);
    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevel)(IAudioEndpointVolumeX *, float *);
    HRESULT (STDMETHODCALLTYPE *GetMasterVolumeLevelScalar)(IAudioEndpointVolumeX *, float *);
    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevel)(IAudioEndpointVolumeX *, UINT, float, LPCGUID);
    HRESULT (STDMETHODCALLTYPE *SetChannelVolumeLevelScalar)(IAudioEndpointVolumeX *, UINT, float, LPCGUID);
    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevel)(IAudioEndpointVolumeX *, UINT, float *);
    HRESULT (STDMETHODCALLTYPE *GetChannelVolumeLevelScalar)(IAudioEndpointVolumeX *, UINT, float *);
    HRESULT (STDMETHODCALLTYPE *SetMute)(IAudioEndpointVolumeX *, BOOL, LPCGUID);
    HRESULT (STDMETHODCALLTYPE *GetMute)(IAudioEndpointVolumeX *, BOOL *);
} IAudioEndpointVolumeXVtbl;
struct IAudioEndpointVolumeX { IAudioEndpointVolumeXVtbl *lpVtbl; };

static HINSTANCE g_hInst;
static DWORD g_selfPid;
static HWND g_hwnd;
static PFN_NtSuspendProcess pNtSuspendProcess;
static PFN_NtResumeProcess pNtResumeProcess;
static PFN_PlaySoundW pPlaySoundW;
static PFN_TimeBeginPeriod pTimeBeginPeriod;
static PFN_TimeEndPeriod pTimeEndPeriod;
static HHOOK g_hKbHook, g_hMsHook;
static DWORD g_hookThreadId;
static DWORD g_candPids[MAX_FROZEN];
static int g_nCand;
static DWORD g_frozenPids[MAX_FROZEN];
static int g_nFrozen;
static int g_hasVol;
static float g_savedVol;
static int g_savedMute;
static int g_volRestored;
static wchar_t g_wavPath[MAX_PATH * 2];
static int g_hasWav;
static volatile LONG g_torn;
static int g_endErr;
static int g_frameMs;
static BYTE *g_pack;
static DWORD g_packSize;
static int g_nFrames;
static const BYTE **g_framePtr;
static DWORD *g_frameLen;
static HMODULE g_gdip;
static ULONG_PTR g_gdipToken;
static PFN_BmpFromStream pGdipCreateBitmapFromStream;
static PFN_BmpLock pGdipBitmapLockBits;
static PFN_BmpUnlock pGdipBitmapUnlockBits;
static PFN_ImgDispose pGdipDisposeImage;
static PFN_GdipStart pGdiplusStartup;
static PFN_GdipStop pGdiplusShutdown;
static int g_surfW, g_surfH, g_winX, g_winY;
static BYTE *g_mask;
static int g_maskW, g_maskH;
static HBITMAP g_dib;
static HDC g_mdc;
static BYTE *g_px;

static void Log(const wchar_t *fmt, ...)
{
    wchar_t path[MAX_PATH + 32];
    wchar_t msg[512];
    wchar_t line[600];
    va_list ap;
    va_start(ap, fmt);
    wvsprintfW(msg, fmt, ap);
    va_end(ap);
    SYSTEMTIME st;
    GetLocalTime(&st);
    wsprintfW(line, L"[%02u:%02u:%02u.%03u] %s\r\n", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, msg);
    GetTempPathW(MAX_PATH, path);
    lstrcatW(path, L"musordrop.log");
    HANDLE f = CreateFileW(path, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f != INVALID_HANDLE_VALUE) {
        DWORD wr = 0;
        WriteFile(f, line, (DWORD)(lstrlenW(line) * sizeof(wchar_t)), &wr, NULL);
        CloseHandle(f);
    }
}

static void StatePath2(LPWSTR out)
{
    GetTempPathW(MAX_PATH, out);
    lstrcatW(out, L"musordrop.state");
}

static void StateDelete(void)
{
    wchar_t p[MAX_PATH + 32];
    StatePath2(p);
    DeleteFileW(p);
}

static void StateWrite(void)
{
    wchar_t p[MAX_PATH + 32];
    StatePath2(p);
    HANDLE f = CreateFileW(p, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
    if (f == INVALID_HANDLE_VALUE) {
        Log(L"state write FAILED (err %u)", GetLastError());
        return;
    }
    struct {
        DWORD magic, ver, hasVol;
        float vol;
        DWORD mute, cnt;
    } hdr;
    hdr.magic = STATE_MAGIC;
    hdr.ver = 1;
    hdr.hasVol = (DWORD)g_hasVol;
    hdr.vol = g_savedVol;
    hdr.mute = (DWORD)g_savedMute;
    hdr.cnt = (DWORD)g_nFrozen;
    DWORD wr = 0;
    WriteFile(f, &hdr, sizeof(hdr), &wr, NULL);
    if (g_nFrozen > 0)
        WriteFile(f, g_frozenPids, sizeof(DWORD) * (DWORD)g_nFrozen, &wr, NULL);
    CloseHandle(f);
}

static int VolAcquire(IAudioEndpointVolumeX **out)
{
    IMMDeviceEnumeratorX *en = NULL;
    IMMDeviceX *dev = NULL;
    IAudioEndpointVolumeX *v = NULL;
    if (FAILED(CoCreateInstance(&k_CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &k_IID_IMMDeviceEnumerator, (void **)&en)))
        return 0;
    if (FAILED(en->lpVtbl->GetDefaultAudioEndpoint(en, 0, 0, &dev))) {
        en->lpVtbl->Release(en);
        return 0;
    }
    if (FAILED(dev->lpVtbl->Activate(dev, &k_IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (void **)&v))) {
        dev->lpVtbl->Release(dev);
        en->lpVtbl->Release(en);
        return 0;
    }
    dev->lpVtbl->Release(dev);
    en->lpVtbl->Release(en);
    *out = v;
    return 1;
}

static void VolSaveAndMax(void)
{
    IAudioEndpointVolumeX *v;
    if (!VolAcquire(&v)) {
        Log(L"volume: endpoint unavailable, skip");
        return;
    }
    float cur = 0.0f;
    BOOL mu = FALSE;
    if (SUCCEEDED(v->lpVtbl->GetMasterVolumeLevelScalar(v, &cur)) && SUCCEEDED(v->lpVtbl->GetMute(v, &mu))) {
        g_savedVol = cur;
        g_savedMute = mu ? 1 : 0;
        g_hasVol = 1;
    }
    v->lpVtbl->SetMute(v, FALSE, NULL);
    v->lpVtbl->SetMasterVolumeLevelScalar(v, 1.0f, NULL);
    v->lpVtbl->Release(v);
    Log(L"volume: saved %u%%, set 100%%", (int)(g_savedVol * 100.0f + 0.5f));
}

static void VolRestore(void)
{
    if (!g_hasVol || g_volRestored)
        return;
    g_volRestored = 1;
    IAudioEndpointVolumeX *v;
    if (!VolAcquire(&v)) {
        Log(L"volume restore: endpoint unavailable");
        return;
    }
    v->lpVtbl->SetMasterVolumeLevelScalar(v, g_savedVol, NULL);
    v->lpVtbl->SetMute(v, (BOOL)g_savedMute, NULL);
    v->lpVtbl->Release(v);
    Log(L"volume restored to %u%%", (int)(g_savedVol * 100.0f + 0.5f));
}

static int StateResume(void)
{
    wchar_t p[MAX_PATH + 32];
    StatePath2(p);
    HANDLE f = CreateFileW(p, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    int resumed = 0, total = 0;
    int hasVol = 0;
    float vol = 0.0f;
    DWORD mute = 0;
    if (f == INVALID_HANDLE_VALUE)
        return 0;
    struct {
        DWORD magic, ver, hasVol;
        float vol;
        DWORD mute, cnt;
    } hdr;
    DWORD rd = 0;
    if (ReadFile(f, &hdr, sizeof(hdr), &rd, NULL) && rd == sizeof(hdr) && hdr.magic == STATE_MAGIC && hdr.cnt <= MAX_FROZEN) {
        DWORD pids[MAX_FROZEN];
        if (hdr.cnt > 0 && ReadFile(f, pids, sizeof(DWORD) * hdr.cnt, &rd, NULL)) {
            total = (int)hdr.cnt;
            for (DWORD i = 0; i < hdr.cnt; i++) {
                HANDLE ph = OpenProcess(PROCESS_SUSPEND_RESUME, FALSE, pids[i]);
                if (ph) {
                    if (pNtResumeProcess && pNtResumeProcess(ph) >= 0)
                        resumed++;
                    CloseHandle(ph);
                }
            }
        }
        hasVol = (int)hdr.hasVol;
        vol = hdr.vol;
        mute = hdr.mute;
    }
    CloseHandle(f);
    if (hasVol && !g_volRestored) {
        g_hasVol = 1;
        g_savedVol = vol;
        g_savedMute = (int)mute;
        VolRestore();
    }
    StateDelete();
    Log(L"resume: %d/%d processes", resumed, total);
    return total;
}

static void WcsLower(wchar_t *s)
{
    for (; *s; s++)
        *s = (wchar_t)towlower(*s);
}

static BOOL QueryImagePath(DWORD pid, wchar_t *out, DWORD cch)
{
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!h)
        return FALSE;
    DWORD sz = cch;
    BOOL ok = QueryFullProcessImageNameW(h, 0, out, &sz);
    CloseHandle(h);
    return ok && sz > 0;
}

static BOOL CompanyIsMicrosoft(const wchar_t *path)
{
    DWORD h = 0;
    DWORD sz = GetFileVersionInfoSizeW(path, &h);
    if (!sz || sz > (1u << 20))
        return FALSE;
    void *buf = LocalAlloc(LMEM_FIXED, sz);
    if (!buf)
        return FALSE;
    int is = 0;
    if (GetFileVersionInfoW(path, 0, sz, buf)) {
        struct {
            WORD lang, cp;
        } *tr = NULL;
        UINT tl = 0;
        wchar_t sub[160];
        if (VerQueryValueW(buf, L"\\VarFileInfo\\Translation", (void **)&tr, &tl) && tl >= 4 && tr)
            wsprintfW(sub, L"\\StringFileInfo\\%04x%04x\\CompanyName", tr[0].lang, tr[0].cp);
        else
            lstrcpyW(sub, L"\\StringFileInfo\\040904b0\\CompanyName");
        wchar_t *val = NULL;
        UINT vl = 0;
        if (VerQueryValueW(buf, sub, (void **)&val, &vl) && val) {
            wchar_t low[128];
            UINT i = 0;
            for (; i < 127 && val[i]; i++)
                low[i] = (wchar_t)towlower(val[i]);
            low[i] = 0;
            if (wcsstr(low, L"microsoft"))
                is = 1;
        }
    }
    LocalFree(buf);
    return is;
}

static BOOL CALLBACK WndEnumProc(HWND hwnd, LPARAM lp)
{
    (void)lp;
    if (g_nCand >= MAX_FROZEN)
        return FALSE;
    if (!IsWindowVisible(hwnd))
        return TRUE;
    if (GetWindow(hwnd, GW_OWNER))
        return TRUE;
    LONG_PTR ex = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    if (ex & WS_EX_TOOLWINDOW)
        return TRUE;
    int cloaked = 0;
    DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (cloaked)
        return TRUE;
    if (hwnd == GetShellWindow())
        return TRUE;
    wchar_t cls[64];
    GetClassNameW(hwnd, cls, 64);
    if (!lstrcmpW(cls, L"Progman") || !lstrcmpW(cls, L"WorkerW") || !lstrcmpW(cls, L"Windows.UI.Core.CoreWindow"))
        return TRUE;
    if (wcsstr(cls, L"Shell_"))
        return TRUE;
    if (GetWindowTextLengthW(hwnd) <= 0 && lstrcmpW(cls, L"ApplicationFrameWindow") != 0)
        return TRUE;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || pid == g_selfPid)
        return TRUE;
    for (int i = 0; i < g_nCand; i++)
        if (g_candPids[i] == pid)
            return TRUE;
    g_candPids[g_nCand++] = pid;
    return TRUE;
}

static void FreezeApps(void)
{
    g_nCand = 0;
    g_nFrozen = 0;
    EnumWindows(WndEnumProc, 0);
    wchar_t windir[MAX_PATH];
    GetWindowsDirectoryW(windir, MAX_PATH);
    int wl = lstrlenW(windir);
    for (int i = 0; i < g_nCand; i++) {
        wchar_t path[MAX_PATH * 2];
        if (!QueryImagePath(g_candPids[i], path, MAX_PATH * 2))
            continue;
        WcsLower(path);
        Log(L"cand pid %u path=%s", g_candPids[i], path);
        if (!_wcsnicmp(path, windir, wl) && (path[wl] == L'\\' || path[wl] == 0)) {
            Log(L"  skip: windows dir");
            continue;
        }
        const wchar_t *base = wcsrchr(path, L'\\');
        base = base ? base + 1 : path;
        if (wcsstr(base, L"cord")) {
            Log(L"  skip: cord exception");
            continue;
        }
        if (CompanyIsMicrosoft(path)) {
            Log(L"  skip: microsoft");
            continue;
        }
        HANDLE ph = OpenProcess(PROCESS_SUSPEND_RESUME, FALSE, g_candPids[i]);
        if (!ph) {
            Log(L"  skip: OpenProcess failed err=%u", GetLastError());
            continue;
        }
        NTSTATUS st = pNtSuspendProcess ? pNtSuspendProcess(ph) : (NTSTATUS)0xC0000001;
        CloseHandle(ph);
        if (st >= 0 && g_nFrozen < MAX_FROZEN) {
            g_frozenPids[g_nFrozen++] = g_candPids[i];
            StateWrite();
            Log(L"  frozen pid %u (%s)", g_candPids[i], base);
        } else {
            Log(L"  skip: suspend failed ntstatus=0x%08X", (unsigned)st);
        }
    }
    Log(L"freeze done: %d suspended, candidates %d", g_nFrozen, g_nCand);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_APP_END:
        g_endErr = (int)lp;
        PostQuitMessage(0);
        return 0;
    case WM_SETCURSOR:
        if (LOWORD(lp) == HTCLIENT) {
            SetCursor(NULL);
            return TRUE;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static int CreateOverlayWindow(void)
{
    WNDCLASSW wc;
    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = g_hInst;
    wc.hCursor = NULL;
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszClassName = L"musordrop_vwnd";
    if (!RegisterClassW(&wc))
        return 0;
    g_hwnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
                             L"musordrop_vwnd", L"", WS_POPUP,
                             g_winX, g_winY, g_surfW, g_surfH,
                             NULL, NULL, g_hInst, NULL);
    return g_hwnd != NULL;
}

static LRESULT CALLBACK KbProc(int code, WPARAM wp, LPARAM lp)
{
    if (code >= 0)
        return 1;
    return CallNextHookEx(NULL, code, wp, lp);
}

static LRESULT CALLBACK MsProc(int code, WPARAM wp, LPARAM lp)
{
    if (code >= 0)
        return 1;
    return CallNextHookEx(NULL, code, wp, lp);
}

static DWORD WINAPI HookThread(LPVOID p)
{
    (void)p;
    g_hKbHook = SetWindowsHookExW(WH_KEYBOARD_LL, KbProc, g_hInst, 0);
    g_hMsHook = SetWindowsHookExW(WH_MOUSE_LL, MsProc, g_hInst, 0);
    Log(L"hooks: kb=%d ms=%d", g_hKbHook ? 1 : 0, g_hMsHook ? 1 : 0);
    MSG m;
    while (GetMessageW(&m, NULL, 0, 0) > 0) {
    }
    return 0;
}

static DWORD WINAPI WatchDogThread(LPVOID p)
{
    (void)p;
    Sleep(WATCHDOG_MS);
    if (!g_torn && g_hwnd) {
        Log(L"watchdog fired, forcing restore");
        PostMessageW(g_hwnd, WM_APP_END, 0, 2);
    }
    return 0;
}

static void Teardown(void)
{
    if (InterlockedExchange(&g_torn, 1))
        return;
    Log(L"teardown begin");
    BlockInput(FALSE);
    if (g_hKbHook)
        UnhookWindowsHookEx(g_hKbHook);
    if (g_hMsHook)
        UnhookWindowsHookEx(g_hMsHook);
    if (g_hookThreadId)
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
    if (pPlaySoundW)
        pPlaySoundW(NULL, NULL, 0);
    StateResume();
    VolRestore();
    if (pTimeEndPeriod)
        pTimeEndPeriod(1);
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    if (g_mdc) {
        DeleteDC(g_mdc);
        g_mdc = NULL;
    }
    if (g_dib) {
        DeleteObject(g_dib);
        g_dib = NULL;
    }
    if (g_mask) {
        LocalFree(g_mask);
        g_mask = NULL;
    }
    if (g_pack) {
        VirtualFree(g_pack, 0, MEM_RELEASE);
        g_pack = NULL;
    }
    if (g_framePtr) {
        LocalFree(g_framePtr);
        g_framePtr = NULL;
    }
    if (g_frameLen) {
        LocalFree(g_frameLen);
        g_frameLen = NULL;
    }
    if (g_gdip && g_gdipToken) {
        pGdiplusShutdown(g_gdipToken);
        g_gdipToken = 0;
    }
    if (g_gdip) {
        FreeLibrary(g_gdip);
        g_gdip = NULL;
    }
    if (g_hwnd) {
        DestroyWindow(g_hwnd);
        g_hwnd = NULL;
    }
    Log(L"teardown done");
}

static void AbortPreLock(const wchar_t *reason)
{
    Log(L"abort before lock: %s", reason);
    StateResume();
    VolRestore();
    StateDelete();
    if (g_mdc) {
        DeleteDC(g_mdc);
        g_mdc = NULL;
    }
    if (g_dib) {
        DeleteObject(g_dib);
        g_dib = NULL;
    }
    if (g_mask) {
        LocalFree(g_mask);
        g_mask = NULL;
    }
    if (g_hwnd) {
        DestroyWindow(g_hwnd);
        g_hwnd = NULL;
    }
}

static void ComposeBmp(const BYTE *scan0, INT stride)
{
    int W = g_surfW, H = g_surfH;
    for (int y = 0; y < H; y++) {
        const BYTE *sl = scan0 + (size_t)y * stride;
        const BYTE *ml = g_mask + (size_t)y * g_maskW;
        BYTE *dl = g_px + (size_t)y * W * 4;
        for (int x = 0; x < W; x++) {
            BYTE *o = dl + (size_t)x * 4;
            const BYTE *sc = sl + (size_t)x * 4;
            unsigned a = (unsigned)ml[x] * sc[3] / 255;
            if (!a) {
                o[0] = 0;
                o[1] = 0;
                o[2] = 0;
                o[3] = 0;
            } else {
                o[0] = (BYTE)(sc[0] * a / 255);
                o[1] = (BYTE)(sc[1] * a / 255);
                o[2] = (BYTE)(sc[2] * a / 255);
                o[3] = (BYTE)a;
            }
        }
    }
}

static void PresentOverlay(void)
{
    if (!g_hwnd || !g_mdc)
        return;
    HDC sdc = GetDC(NULL);
    if (!sdc)
        return;
    HGDIOBJ old = SelectObject(g_mdc, g_dib);
    POINT dst = { g_winX, g_winY };
    POINT src = { 0, 0 };
    SIZE sz = { g_surfW, g_surfH };
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    UpdateLayeredWindow(g_hwnd, sdc, &dst, &sz, g_mdc, &src, 0, &bf, ULW_ALPHA);
    SelectObject(g_mdc, old);
    ReleaseDC(NULL, sdc);
}

static DWORD WINAPI VideoThread(LPVOID p)
{
    (void)p;
    DWORD t0 = GetTickCount();
    int i = 0;
    for (;;) {
        if (i > 0) {
            DWORD target = t0 + (DWORD)i * (DWORD)g_frameMs;
            DWORD now = GetTickCount();
            if ((int)(target - now) > 0)
                Sleep(target - now);
        }
        if (i >= g_nFrames) {
            Log(L"pack: end after %d frames", i);
            break;
        }
        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, g_frameLen[i]);
        if (!hg) {
            i++;
            continue;
        }
        void *pm = GlobalLock(hg);
        if (pm) {
            memcpy(pm, g_framePtr[i], g_frameLen[i]);
            GlobalUnlock(hg);
        }
        IStream *stm = NULL;
        GpBitmap *bmp = NULL;
        BOOL drawn = FALSE;
        if (SUCCEEDED(CreateStreamOnHGlobal(hg, FALSE, &stm)) && stm) {
            if (pGdipCreateBitmapFromStream((IStreamX *)stm, &bmp) == 0 && bmp) {
                BmpDataX bd;
                GpRectX rc;
                rc.X = 0;
                rc.Y = 0;
                rc.Width = g_surfW;
                rc.Height = g_surfH;
                if (pGdipBitmapLockBits(bmp, &rc, 1, 0x0026200A, &bd) == 0 && bd.Scan0) {
                    ComposeBmp((const BYTE *)bd.Scan0, bd.Stride);
                    PresentOverlay();
                    pGdipBitmapUnlockBits(bmp, &bd);
                    drawn = TRUE;
                }
                pGdipDisposeImage(bmp);
            }
            stm->lpVtbl->Release(stm);
        }
        GlobalFree(hg);
        if (!drawn)
            Log(L"frame %d: decode skipped", i);
        i++;
    }
    PostMessageW(g_hwnd, WM_APP_END, 0, 0);
    return 0;
}

static BOOL ExtractResourceRc(int rcId, const wchar_t *dst)
{
    HRSRC hs = FindResourceW(g_hInst, MAKEINTRESOURCEW(rcId), RT_RCDATA);
    if (!hs)
        return FALSE;
    HGLOBAL hg = LoadResource(g_hInst, hs);
    if (!hg)
        return FALSE;
    void *data = LockResource(hg);
    DWORD size = SizeofResource(g_hInst, hs);
    if (!data || !size)
        return FALSE;
    HANDLE f = CreateFileW(dst, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f == INVALID_HANDLE_VALUE)
        return FALSE;
    DWORD wr = 0;
    BOOL ok = WriteFile(f, data, size, &wr, NULL) && wr == size;
    CloseHandle(f);
    return ok;
}

static wchar_t g_maskPath[MAX_PATH * 2];
static wchar_t g_packPath[MAX_PATH * 2];

static int FindVideo(void)
{
    wchar_t dir[MAX_PATH];
    GetModuleFileNameW(NULL, dir, MAX_PATH);
    wchar_t *sl = wcsrchr(dir, L'\\');
    if (sl)
        *sl = 0;
    wchar_t temp[MAX_PATH];
    GetTempPathW(MAX_PATH, temp);
    wchar_t sub[MAX_PATH * 2];
    lstrcpyW(sub, temp);
    lstrcatW(sub, L"musordrop_extract");
    CreateDirectoryW(sub, NULL);
    lstrcpyW(g_packPath, dir);
    lstrcatW(g_packPath, L"\\musordrop.pack");
    if (GetFileAttributesW(g_packPath) == INVALID_FILE_ATTRIBUTES) {
        lstrcpyW(g_packPath, sub);
        lstrcatW(g_packPath, L"\\musordrop.pack");
        if (!ExtractResourceRc(101, g_packPath)) {
            Log(L"pack: not found external, embedded extract failed (err %u)", GetLastError());
            return 0;
        }
        Log(L"pack: extracted from exe");
    } else {
        Log(L"pack: external file");
    }
    lstrcpyW(g_maskPath, dir);
    lstrcatW(g_maskPath, L"\\musordrop_mask.bin");
    if (GetFileAttributesW(g_maskPath) == INVALID_FILE_ATTRIBUTES) {
        lstrcpyW(g_maskPath, sub);
        lstrcatW(g_maskPath, L"\\musordrop_mask.bin");
        if (!ExtractResourceRc(103, g_maskPath)) {
            Log(L"mask: not found external, embedded extract failed (err %u)", GetLastError());
            return 0;
        }
    }
    lstrcpyW(g_wavPath, dir);
    lstrcatW(g_wavPath, L"\\musordrop.wav");
    g_hasWav = GetFileAttributesW(g_wavPath) != INVALID_FILE_ATTRIBUTES;
    if (!g_hasWav) {
        lstrcpyW(g_wavPath, sub);
        lstrcatW(g_wavPath, L"\\musordrop.wav");
        g_hasWav = ExtractResourceRc(102, g_wavPath);
    }
    Log(L"assets ready (wav=%d)", g_hasWav);
    return 1;
}

static int LoadMask(void)
{
    HANDLE f = CreateFileW(g_maskPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE) {
        Log(L"mask open failed err %u", GetLastError());
        return 0;
    }
    struct {
        DWORD magic;
        int w, h;
    } hdr;
    DWORD rd = 0;
    if (!ReadFile(f, &hdr, sizeof(hdr), &rd, NULL) || rd != sizeof(hdr) || hdr.magic != 0x314B534Du) {
        Log(L"mask header bad");
        CloseHandle(f);
        return 0;
    }
    if (hdr.w < 4 || hdr.h < 4 || hdr.w > 4096 || hdr.h > 4096) {
        Log(L"mask size insane %dx%d", hdr.w, hdr.h);
        CloseHandle(f);
        return 0;
    }
    DWORD need = (DWORD)hdr.w * (DWORD)hdr.h;
    g_mask = (BYTE *)LocalAlloc(LMEM_FIXED, need);
    if (!g_mask) {
        Log(L"mask alloc failed");
        CloseHandle(f);
        return 0;
    }
    if (!ReadFile(f, g_mask, need, &rd, NULL) || rd != need) {
        Log(L"mask read short %u/%u", rd, need);
        LocalFree(g_mask);
        g_mask = NULL;
        CloseHandle(f);
        return 0;
    }
    CloseHandle(f);
    g_maskW = hdr.w;
    g_maskH = hdr.h;
    for (DWORD i = 0; i < need; i++)
        g_mask[i] = (g_mask[i] >= 128) ? 255 : 0;
    Log(L"mask loaded %dx%d", g_maskW, g_maskH);
    return 1;
}

static int PackLoad(void)
{
    HANDLE f = CreateFileW(g_packPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (f == INVALID_HANDLE_VALUE) {
        Log(L"pack open failed err %u", GetLastError());
        return 0;
    }
    LARGE_INTEGER sz;
    if (!GetFileSizeEx(f, &sz) || sz.QuadPart < 24) {
        Log(L"pack size bad");
        CloseHandle(f);
        return 0;
    }
    DWORD size = (DWORD)sz.QuadPart;
    BYTE *p = (BYTE *)VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!p) {
        Log(L"pack alloc failed");
        CloseHandle(f);
        return 0;
    }
    DWORD rd = 0;
    if (!ReadFile(f, p, size, &rd, NULL) || rd != size) {
        Log(L"pack read short %u/%u", rd, size);
        VirtualFree(p, 0, MEM_RELEASE);
        CloseHandle(f);
        return 0;
    }
    CloseHandle(f);
    DWORD magic = *(DWORD *)(p + 0);
    DWORD cnt = *(DWORD *)(p + 4);
    int w = *(int *)(p + 8);
    int h = *(int *)(p + 12);
    DWORD fdur = *(DWORD *)(p + 16);
    if (magic != 0x504B534Du || cnt == 0 || cnt > 4096) {
        Log(L"pack header bad magic=0x%08X cnt=%u", magic, cnt);
        VirtualFree(p, 0, MEM_RELEASE);
        return 0;
    }
    if (w < 4 || h < 4 || w > 4096 || h > 4096) {
        Log(L"pack size insane %dx%d", w, h);
        VirtualFree(p, 0, MEM_RELEASE);
        return 0;
    }
    if (fdur < 10000 || fdur > 10000000)
        fdur = 333333;
    g_frameMs = (int)(fdur / 10000);
    if (g_frameMs < 10 || g_frameMs > 200)
        g_frameMs = 33;
    const BYTE *offs = p + 20;
    const BYTE *base = offs + (size_t)cnt * 4;
    if ((size_t)(base - p) > (size_t)size) {
        Log(L"pack truncated (index)");
        VirtualFree(p, 0, MEM_RELEASE);
        return 0;
    }
    g_pack = p;
    g_packSize = size;
    g_nFrames = (int)cnt;
    g_framePtr = (const BYTE **)LocalAlloc(LMEM_FIXED, sizeof(BYTE *) * cnt);
    g_frameLen = (DWORD *)LocalAlloc(LMEM_FIXED, sizeof(DWORD) * cnt);
    if (!g_framePtr || !g_frameLen) {
        Log(L"frame index alloc failed");
        return 0;
    }
    const BYTE *cur = base;
    const BYTE *end = p + size;
    for (DWORD i = 0; i < cnt; i++) {
        DWORD len = *(DWORD *)(offs + (size_t)i * 4);
        if (len < 8 || cur + (size_t)len > end) {
            Log(L"pack frame %u bad len %u", i, len);
            return 0;
        }
        g_framePtr[i] = cur;
        g_frameLen[i] = len;
        cur += len;
    }
    if (!LoadMask())
        return 0;
    if (w != g_maskW || h != g_maskH) {
        Log(L"pack %dx%d != mask %dx%d", w, h, g_maskW, g_maskH);
        return 0;
    }
    int scrW = GetSystemMetrics(SM_CXSCREEN);
    int scrH = GetSystemMetrics(SM_CYSCREEN);
    g_surfW = g_maskW;
    g_surfH = g_maskH;
    g_winX = (scrW - g_surfW) / 2;
    g_winY = (scrH - g_surfH) / 2;
    g_gdip = LoadLibraryW(L"gdiplus.dll");
    if (!g_gdip) {
        Log(L"gdiplus.dll missing");
        return 0;
    }
    pGdipCreateBitmapFromStream = (PFN_BmpFromStream)GetProcAddress(g_gdip, "GdipCreateBitmapFromStream");
    pGdipBitmapLockBits = (PFN_BmpLock)GetProcAddress(g_gdip, "GdipBitmapLockBits");
    pGdipBitmapUnlockBits = (PFN_BmpUnlock)GetProcAddress(g_gdip, "GdipBitmapUnlockBits");
    pGdipDisposeImage = (PFN_ImgDispose)GetProcAddress(g_gdip, "GdipDisposeImage");
    pGdiplusStartup = (PFN_GdipStart)GetProcAddress(g_gdip, "GdiplusStartup");
    pGdiplusShutdown = (PFN_GdipStop)GetProcAddress(g_gdip, "GdiplusShutdown");
    if (!pGdipCreateBitmapFromStream || !pGdipBitmapLockBits || !pGdipBitmapUnlockBits || !pGdipDisposeImage || !pGdiplusStartup || !pGdiplusShutdown) {
        Log(L"gdiplus exports missing");
        return 0;
    }
    GdipStartIn si;
    memset(&si, 0, sizeof(si));
    si.GdiplusVersion = 1;
    if (pGdiplusStartup(&g_gdipToken, &si, NULL) != 0) {
        Log(L"GdiplusStartup failed");
        return 0;
    }
    BITMAPINFO bi;
    memset(&bi, 0, sizeof(bi));
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = g_surfW;
    bi.bmiHeader.biHeight = -g_surfH;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void *pv = NULL;
    g_dib = CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, &pv, NULL, 0);
    if (!g_dib || !pv) {
        Log(L"CreateDIBSection failed");
        return 0;
    }
    g_px = (BYTE *)pv;
    memset(g_px, 0, (size_t)g_surfW * g_surfH * 4);
    g_mdc = CreateCompatibleDC(NULL);
    if (!g_mdc) {
        Log(L"CreateCompatibleDC failed");
        return 0;
    }
    Log(L"pack ready: %d frames %dx%d, %d ms/frame", g_nFrames, g_surfW, g_surfH, g_frameMs);
    return 1;
}
static void RunPrank(void)
{
    g_nFrozen = 0;
    VolSaveAndMax();
    StateWrite();
    if (!PackLoad()) {
        AbortPreLock(L"video init failed");
        MessageBoxW(NULL, L"Не удалось загрузить кадры (нужен musordrop.pack рядом с exe).\nНичего не изменено, всё восстановлено.", L"musordrop", MB_OK | MB_ICONERROR);
        return;
    }
    if (!CreateOverlayWindow()) {
        Log(L"window create failed");
        AbortPreLock(L"window failed");
        return;
    }
    ShowWindow(g_hwnd, SW_SHOWNOACTIVATE);
    SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);
    SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    if (pTimeBeginPeriod)
        pTimeBeginPeriod(1);
    FreezeApps();
    CreateThread(NULL, 0, HookThread, NULL, 0, &g_hookThreadId);
    BlockInput(TRUE);
    Log(L"input blocked");
    if (g_hasWav && pPlaySoundW) {
        pPlaySoundW(g_wavPath, NULL, SND_FILENAME | SND_ASYNC);
        Log(L"audio started");
    }
    CreateThread(NULL, 0, VideoThread, NULL, 0, NULL);
    CreateThread(NULL, 0, WatchDogThread, NULL, 0, NULL);
    MSG m;
    while (GetMessageW(&m, NULL, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    Teardown();
    if (g_endErr == 1)
        MessageBoxW(NULL, L"Ошибка воспроизведения видео.\nВсё восстановлено: ввод включён, процессы разморожены, громкость возвращена.", L"musordrop", MB_OK | MB_ICONWARNING);
    else if (g_endErr == 2)
        MessageBoxW(NULL, L"Сработал аварийный таймер (15 мин).\nВсё восстановлено: ввод включён, процессы разморожены, громкость возвращена.", L"musordrop", MB_OK | MB_ICONWARNING);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdA, int nShow)
{
    (void)hPrev;
    (void)cmdA;
    (void)nShow;
    g_hInst = hInst;
    g_selfPid = GetCurrentProcessId();
    SetProcessDPIAware();
    Log(L"=== musordrop start, pid %u ===", g_selfPid);
    if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
        Log(L"CoInitializeEx failed");
        return 1;
    }
    HMODULE nt = GetModuleHandleW(L"ntdll.dll");
    pNtSuspendProcess = nt ? (PFN_NtSuspendProcess)GetProcAddress(nt, "NtSuspendProcess") : NULL;
    pNtResumeProcess = nt ? (PFN_NtResumeProcess)GetProcAddress(nt, "NtResumeProcess") : NULL;
    Log(L"ntdll suspend=%d resume=%d", pNtSuspendProcess ? 1 : 0, pNtResumeProcess ? 1 : 0);
    HMODULE winmm = LoadLibraryW(L"winmm.dll");
    if (winmm) {
        pPlaySoundW = (PFN_PlaySoundW)GetProcAddress(winmm, "PlaySoundW");
        pTimeBeginPeriod = (PFN_TimeBeginPeriod)GetProcAddress(winmm, "timeBeginPeriod");
        pTimeEndPeriod = (PFN_TimeEndPeriod)GetProcAddress(winmm, "timeEndPeriod");
    }
    if (!FindVideo()) {
        Log(L"video not found");
        MessageBoxW(NULL, L"Не найден musordrop.pack (кадры) рядом с musordrop.exe.\nПранк не запущен, ничего не изменено.", L"musordrop", MB_OK | MB_ICONERROR);
        CoUninitialize();
        return 1;
    }
    RunPrank();
    CoUninitialize();
    Log(L"=== musordrop exit ===");
    return 0;
}
