#include <Windows.h>

class SharedMemory {
    const LPCWSTR SharedMemoryKeyOut = L"A3TrackerOut";
    const LPCWSTR SharedMemoryKeyIn = L"A3TrackerIn";
    const static int SharedMemorySize = 1024;
    HANDLE fileMapIn;
    HANDLE fileMapOut;
    LPVOID mapViewIn;
    LPVOID mapViewOut;
public:
    static const int dataSize = 7 * 3;
    float data[dataSize];
    static const int dataHMDSize = 3 * 4;
    float dataHMD[dataHMDSize];
    SharedMemory();
    void Update();
};