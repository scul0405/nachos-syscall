#include "syscall.h"

int main()
{
	char* a;
	ReadString(a, 100);
	PrintString(a);
	return 0;
}
