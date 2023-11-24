#include "syscall.h"

int main()
{
	int number = ReadInt();
	PrintInt(number);
	
	Halt();
}
