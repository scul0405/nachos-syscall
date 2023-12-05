#include "syscall.h"

int main()
{
	// Doc so nguyen tu man hinh console
	int number = ReadInt();

	// In so nguyen ra man hinh
	PrintInt(number);
	
	Halt();
}
