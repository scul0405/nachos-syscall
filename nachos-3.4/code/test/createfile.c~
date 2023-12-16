#include "syscall.h"

int main()
{
	int a = CreateFile("test2.txt");
	int open = Open("test1.txt", 1);
	PrintInt(open);
	PrintChar('\n');

	open = Open("test2.txt", 1);
	PrintInt(open);
	PrintChar('\n');

	Close(open);


	Halt();
}
