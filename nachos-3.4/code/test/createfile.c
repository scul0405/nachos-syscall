#include "syscall.h"

int main()
{
	int status = CreateFile("random.txt");	
	PrintInt(status);
	PrintChar('\n');

	Halt();
}
