#pragma once
#define AIMBOT_HOTKEY VK_LSHIFT
#define ZOOM_HOTKEY VK_RBUTTON
#define SCOPED_HOTKEY 0x59 // y
#define TRIGGERBOT_HOTKEY VK_MENU



bool HideThread(HANDLE hThread)
{
    typedef NTSTATUS(NTAPI* pNtSetInformationThread)
        (HANDLE, UINT, PVOID, ULONG);
    NTSTATUS Status;

    // Get NtSetInformationThread
    pNtSetInformationThread NtSIT = (pNtSetInformationThread)
        GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")),
            "NtSetInformationThread");

    // Shouldn't fail
    if (NtSIT == NULL)
        return false;

    // Set the thread info
    if (hThread == NULL)
        Status = NtSIT(GetCurrentThread(),
            0x11, // HideThreadFromDebugger
            0, 0);
    else
        Status = NtSIT(hThread, 0x11, 0, 0);

    if (Status != 0x00000000)
        return false;
    else
        return true;
}

template <class T> static 
T read(uintptr_t address)
{
    //T buffer{ };
    //if (ReadProcessMemory(GetCurrentProcess(), (LPVOID)address, &buffer, sizeof(T), 0))
    //    return buffer;
    ////if (!IsBadReadPtr(reinterpret_cast<void*>(address), sizeof(T)))
    ////    return *reinterpryet_cast<T*>(address);


    if (!(IsBadReadPtr)(reinterpret_cast<void*>(address), sizeof(T)))
        return *reinterpret_cast<T*>(address);

    return T{};

    //__try {
    //    return *(T*)(address);
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) {
    //    return T{};
    //}
}


template <typename T> static
bool write(uintptr_t address, const T* buffer)
{
    if (address > 0x7FFFFFFFFFFF || address < 1) return 0;
    *(T*)address = *buffer;
    return true;
        
    //__try {
    //    *(T*)(address) = buffer;
    //    return true;
    //}
    //__except (EXCEPTION_EXECUTE_HANDLER) { return FALSE; }
}

bool isKeyTapped(int key) {
    SHORT keyState = GetKeyState(key);
    bool isDown = keyState & 0x8000;
    return isDown;
}
bool isKeyPressed(int key) {
    SHORT keyState = GetAsyncKeyState(key);
    return keyState != 0; //isDown
}


std::wstring StringToWString(const std::string& s)
{
    std::wstring temp(s.length(), L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}


std::string WStringToString(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}