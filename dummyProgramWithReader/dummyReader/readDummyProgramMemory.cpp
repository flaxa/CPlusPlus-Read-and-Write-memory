

#include <iostream>
#include <Windows.h>
#include <string>

int readInt(HANDLE programAccess, LPCVOID BaseLocation);
std::string readString(HANDLE programAccess, LPCVOID BaseLocation);
int readIntWithPointer(HANDLE programAccess, LPCVOID BaseLocation);
int readIntWithPointer2(HANDLE programAccess, LPCVOID BaseLocation);

int main()
{
    //setup to get the PID
    int PID;
    uintptr_t baseAddress = 0x0;
    std::cout << "What is the PID of the dummy program? :";
    std::cin >> PID;
    std::cout << "What is the address of varInt:";
    std::cin >> std::hex >> baseAddress;

    //create the Handle using the PID
    HANDLE dummyProgramHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID );
    
    //read the first variable in the program
    int intRead = readInt(dummyProgramHandle, (LPCVOID)baseAddress);

    //read first variable with pointer to get there
    int intReadWithPointer = readIntWithPointer(dummyProgramHandle, (LPCVOID)(baseAddress - 0x000000B8));

    //read first variable with  2 pointers to get there
    int intReadWithPointer2 = readIntWithPointer2(dummyProgramHandle, (LPCVOID)(baseAddress - 0x000000C4));

    //read string variable
    std::string readStrings = readString(dummyProgramHandle, (LPCVOID)(baseAddress - (uintptr_t)0x00000020));

    CloseHandle(dummyProgramHandle);
    
    //print out the read data
    std::cout << "intRead = " << std::dec << intRead << std::endl;
    std::cout << "intReadFWithPointer = " << std::dec << intReadWithPointer << std::endl;
    std::cout << "intReadFWithPointer2 = " << std::dec << intReadWithPointer2 << std::endl;
    
    std::cout << "varString = " << readStrings << std::endl;
    std::cout << "Press ENTER to quit" << std::endl;
    std::cin.get();

}



int readInt(HANDLE programAccess, LPCVOID BaseLocation) {
    int result = 0;
    ReadProcessMemory(programAccess, BaseLocation, &result, sizeof(int), NULL);
    
    return result;

    
}

std::string readString(HANDLE programAccess, LPCVOID BaseLocation) {
    char results[14];

    ReadProcessMemory(programAccess, BaseLocation, &results, 13, NULL);
    
    
    results[13] = NULL;
    return results;
}

int readIntWithPointer(HANDLE programAccess, LPCVOID BaseLocation) {
    int *pointerToInt;
    int result;
    ReadProcessMemory(programAccess, BaseLocation, &pointerToInt, sizeof(int*), NULL);
    ReadProcessMemory(programAccess, pointerToInt, &result, sizeof(int), NULL);

    return result;


}

int readIntWithPointer2(HANDLE programAccess, LPCVOID BaseLocation) {
    int** pointerToPointer;
    int* pointerToInt;
    int result;
    ReadProcessMemory(programAccess, BaseLocation, &pointerToPointer, sizeof(int**), NULL);
    ReadProcessMemory(programAccess, pointerToPointer, &pointerToInt, sizeof(int*), NULL);
    ReadProcessMemory(programAccess, pointerToInt, &result, sizeof(int), NULL);
    return result;


}