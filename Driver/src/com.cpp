#include "com.h"

SharedMemory::SharedMemory() {
    fileMapIn = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SharedMemorySize, SharedMemoryKeyIn);
    if (!fileMapIn || fileMapIn == INVALID_HANDLE_VALUE)
    {
        mapViewIn = NULL;
        return;
    }
    mapViewIn = MapViewOfFile(fileMapIn, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (mapViewIn == NULL)
    {
        CloseHandle(fileMapIn);
    }
    fileMapOut = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SharedMemorySize, SharedMemoryKeyOut);
    if (!fileMapOut || fileMapOut == INVALID_HANDLE_VALUE)
    {
        mapViewOut = NULL;
        return;
    }
    mapViewOut = MapViewOfFile(fileMapOut, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (mapViewOut == NULL)
    {
        CloseHandle(fileMapOut);
    }
}
void SharedMemory::Update() {
    {
        float* SharedRam = (float*)mapViewIn;
        for (int i = 0;i < dataSize;i++) {
            data[i] = SharedRam[i];
        }
    }
    {
        float* SharedRam = (float*)mapViewOut;
        for (int i = 0;i < dataHMDSize;i++) {
            SharedRam[i] = dataHMD[i];
        }
    }
}