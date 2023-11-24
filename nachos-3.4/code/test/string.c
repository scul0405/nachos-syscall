#include "syscall.h"

int main()
{
	char a[255];
	// test
	ReadString(a, 255);
	PrintString(a);
	Halt();
}
