#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

    string windowName;
    //cout << "Please provide me with a name of the Terraria game Window: "; cin >> windowName; cout << endl;
    int dw_Health = 0x408; // Health offset
    int ad_Health = 0x3AA3AB0C; // STATIC HAHAHAH Health pointer
    int writeHealth = 999; // Set amount of health to your desired value (e.g., 999)

    DWORD health = (DWORD)(ad_Health + dw_Health); // Turn health offset and pointer into DWORD

    HWND hwnd = FindWindowA(NULL, "Terraria: zagraj też w Stardew"); // find window with title

    if (hwnd == NULL) { //Check if game isn't open
        cout << "Cannot find game!" << endl; // Write message in Console
        Sleep(3000); // Wait for 3 seconds
        exit(-1); // Close Console (Hack)
    } else { //Run if game is open
        DWORD procID; //Variable to save process ID if not found
        GetWindowThreadProcessId(hwnd, &procID); // Get game process ID
        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID); //Give all permissions to game

        if (handle == NULL) { // Run if handle isn't found
            cout << "Cannot obtain process!" << endl; // Write message in Console
            Sleep(3000); // Wait for 3 seconds
            exit(-1); // Close Console (Hack)
        } else { // run if handle isn't null
            for (;;) { //run infinite loop
                WriteProcessMemory(handle, (PBYTE*)health, &writeHealth, sizeof(writeHealth), 0); // Write amount of health in memory
                Sleep(1000);
            }
        }
        CloseHandle(handle); // Close the handle after use
    }

    return 0;
}
