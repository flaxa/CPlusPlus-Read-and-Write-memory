#include <iostream>
#include <Windows.h>

int main() {
	int varInt = 123456;
	std::string varString = "defaultString";
	char arrChar[128] = "Long char array right there ->";

	int* ptr2int = &varInt;
	int** ptr2ptr = &ptr2int;
	int*** ptr2ptr2 = &ptr2ptr;

	while (true) {
			
		std::cout << "Process ID: " << GetCurrentProcessId() << std::endl;
		std::cout << "varInt      0x" << ptr2int << " = " << varInt << std::endl;
		std::cout << "varString   0x" << &varString << " = " + varString << std::endl << std::endl;
		std::cout << "ptr2int    0x" << ptr2ptr << " = 0x" << ptr2int << std::endl;
		std::cout << "ptr2ptr    0x" << ptr2ptr2 << " = 0x" << ptr2ptr << std::endl;
		std::cout << "ptr2ptr2   0x" << &ptr2ptr2 << " = 0x" << ptr2ptr2 << std::endl << std::endl;
		std::cout << "Press ENTER to print again.";
		std::cin.get();

		std::cout << std::endl << "----------------------------------------------------" << std::endl;










	}
}
