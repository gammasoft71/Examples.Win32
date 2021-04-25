#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <CommCtrl.h>

HWND form = nullptr;
HWND label = nullptr;
WNDPROC defWndProc = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_CLOSE && hwnd == form) {
    PostQuitMessage(0);
    return 0;
  }
  if (message == WM_ERASEBKGND && hwnd == label) { 
    SetBkColor((HDC)wParam, GetBkColor(GetDC(form))); 
    return 0; 
  }
  if (message == WM_SIZE && hwnd == form) {
    RECT rect;
    GetWindowRect(label, &rect);
    SetWindowPos(form, HWND_TOP, 0, 0, rect.right - rect.left + 16, rect.bottom - rect.top + 46, SWP_NOMOVE);
  }

  return CallWindowProc(defWndProc, hwnd, message, wParam, lParam);
}

int main() {
  form = CreateWindowEx(0, WC_DIALOG, L"Hello world (emoticons)", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 316, 330, nullptr, nullptr, nullptr, nullptr);
  label = CreateWindowEx(0, WC_STATIC, L"\U0001F44B, \U0001F30E\U00002757", WS_CHILD | WS_VISIBLE, 0, 0, 319, 123, form, nullptr, nullptr, nullptr);

  defWndProc = (WNDPROC)SetWindowLongPtr(form, GWLP_WNDPROC, (LONG_PTR)WndProc);

  SendMessage(form, WM_CTLCOLORSTATIC, (WPARAM)GetDC(label), (LPARAM)label);
  SendMessage(label, WM_SETFONT, (WPARAM)CreateFont(int(-72 / 72.0f * GetDeviceCaps(GetDC(form), LOGPIXELSY)), 0, 0, 0, FW_BOLD, false, false, false, 0, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial"), true);

  ShowWindow(form, SW_SHOW);

  MSG message = { 0 };
  while (GetMessage(&message, nullptr, 0, 0))
    DispatchMessage(&message);
  return (int)message.wParam;
}