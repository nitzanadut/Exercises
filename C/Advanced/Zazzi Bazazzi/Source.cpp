#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>  

// Counting the keys
int count = 1;

// Last time the function was called
auto last = std::chrono::system_clock::now();

LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - last;
    last = std::chrono::system_clock::now();

    // This function gets called more than once for every keypress, this if makes it so we evaluate every keypress once
    if (elapsed_seconds.count() < .01)
        return CallNextHookEx(NULL, nCode, wParam, lParam);

    // Detect keypress
	if (wParam == WM_KEYDOWN) {
        INPUT ip;
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0;
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Sending a backspace
        ip.ki.wVk = VK_BACK;
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        // Setting the current zazzi bazazi letter
        if (count % 11 == 1)       ip.ki.wVk = 0x5a;
        else if (count % 11 == 2)  ip.ki.wVk = 0x54;
        else if (count % 11 == 3)  ip.ki.wVk = 0x5a;
        else if (count % 11 == 4)  ip.ki.wVk = 0x48;
        else if (count % 11 == 5)  ip.ki.wVk = 0x20;
        else if (count % 11 == 6)  ip.ki.wVk = 0x43;
        else if (count % 11 == 7)  ip.ki.wVk = 0x5a;
        else if (count % 11 == 8)  ip.ki.wVk = 0x54;
        else if (count % 11 == 9)  ip.ki.wVk = 0x5a;
        else if (count % 11 == 10) ip.ki.wVk = 0x48;
        else if (count % 11 == 0)  ip.ki.wVk = 0x20;

        // Sending the letter
        ip.ki.dwFlags = 0;
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));

        count++;
	}
    
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // Set windows hook
    HHOOK keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        keyboardHookProc,
        hInstance,
        0);

    MessageBox(NULL, _T("Press OK to stop zazzing."), _T("Zazzi Bazazi of DOOM"), MB_OK);
    return 0;
}