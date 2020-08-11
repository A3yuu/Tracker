#include <iostream>
#include <Windows.h>

int main()
{
    const LPCWSTR SharedMemoryKey = L"A3TrackerOut";
    const int SharedMemorySize = 1024;
    HANDLE fileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SharedMemorySize, SharedMemoryKey);
    if (!fileMap || fileMap == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    LPVOID mapView = MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (mapView == NULL)
    {
        CloseHandle(fileMap);
        return -1;
    }
    float* SharedRam = (float*)mapView;
    //
    while (true)
    {
        for (int i = 0;i < 7 * 3;i++) {
            printf("%.2f,", SharedRam[i]);
        }
        printf("\n");
        Sleep(100);
    }
    UnmapViewOfFile(mapView);
    CloseHandle(fileMap);
}
