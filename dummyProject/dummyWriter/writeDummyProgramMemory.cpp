

#include <iostream>
#include <Windows.h>

void writeInt(HANDLE dummyProgram, int dataToWrite, LPVOID address);
void writeString(HANDLE dummyProgram, std::string dataToWrite, LPVOID address);


int main()
{
    int PID;
    uintptr_t baseAddress = 0x0;
    int dataToWriteInt;
    std::string dataToWriteString;
    std::cout << "Whats the PID of the dummy program? :";
    std::cin >> PID;
    std::cout << "whats the address of varInt? :";
    std::cin >> std::hex >> baseAddress;
    std::cout << "what value would you like to write to varInt: ";
    std::cin >> std::dec >> dataToWriteInt;
    std::cout << "What string would you like to write to varString: ";
    std::cin >> dataToWriteString;
    


    HANDLE dummyProgram =  OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    writeInt(dummyProgram, dataToWriteInt, (LPVOID)baseAddress);
    writeString(dummyProgram, dataToWriteString, (LPVOID)(baseAddress - 0x00000024));
    CloseHandle(dummyProgram);
    EXIT_SUCCESS;

} 


void writeInt(HANDLE dummyProgram, int dataToWrite, LPVOID address) {

 BOOL indicator = WriteProcessMemory(dummyProgram, address, &dataToWrite, sizeof(int), NULL );
 if (indicator == FALSE) {
     std::cout << "Error Code: " << GetLastError() << std::endl;
     EXIT_FAILURE;

 }

}

void writeString(HANDLE dummyProgram, std::string dataToWrite, LPVOID address) {

  BOOL indicator =   WriteProcessMemory(dummyProgram, address, &dataToWrite, (dataToWrite.length() + 4), NULL);
  if (indicator == FALSE) {
      std::cout << "Error Code: " << GetLastError() << std::endl;
      EXIT_FAILURE;
  }
}
