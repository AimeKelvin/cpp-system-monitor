#include <iostream>
#include <windows.h>
#include <psapi.h>

void displayMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    std::cout << "\n🖥️ RAM Usage:";
    std::cout << "\n🔹 Total RAM: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB";
    std::cout << "\n🔹 Available RAM: " << memInfo.ullAvailPhys / (1024 * 1024) << " MB";
    std::cout << "\n🔹 RAM Usage: " << 100 - (memInfo.ullAvailPhys * 100 / memInfo.ullTotalPhys) << "%\n";
}

void displayRunningProcesses() {
    DWORD processIDs[1024], bytesReturned;
    if (EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned)) {
        int processCount = bytesReturned / sizeof(DWORD);
        std::cout << "\n🔍 Running Processes (" << processCount << " total):\n";
        
        for (int i = 0; i < std::min(processCount, 10); ++i) { // Limit output to 10 processes
            std::cout << "🔹 Process ID: " << processIDs[i] << "\n";
        }
    } else {
        std::cerr << "Failed to retrieve process list.\n";
    }
}

void runSystemMonitor() {
    system("cls"); // Clears the screen
    std::cout << "🔧 Windows System Monitor\n";

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "\n💻 System Info:";
    std::cout << "\n🔹 Number of Processors: " << sysInfo.dwNumberOfProcessors;
    std::cout << "\n🔹 Processor Architecture: " 
              << (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ? "x64 (AMD/Intel)" : "x86") << "\n";

    displayMemoryUsage();
    displayRunningProcesses();

    std::cout << "\n✅ System info retrieved successfully!\n";
}

int main() {
    char choice;
    
    do {
        runSystemMonitor();
        std::cout << "\n🔄 Do you want to re-run the system monitor? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    std::cout << "\n👋 Exiting... Have a great day!\n";
    return 0;
}
