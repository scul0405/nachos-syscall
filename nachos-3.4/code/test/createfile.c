#include "syscall.h"

int main()
{
	int a = CreateFile("test1.txt");
	int status = Open("random.txt", 1);
	PrintInt(status);
	PrintChar('\n');
	status = Open("", 1);
	PrintInt(status);
	PrintChar('\n');

	Halt();
}
