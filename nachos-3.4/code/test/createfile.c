#include "syscall.h"

// type = -2 --> stdin (console input)
// type = -1 --> stdout (console output) 
// type = 0  --> doc va ghi
// type = 1  --> chi doc
int main()
{
	// Test SC_Open & SC_Close
	/*
	int a = CreateFile("test2.txt");
	int open = Open("test1.txt", 1);
	PrintInt(open);
	PrintChar('\n');

	open = Open("test2.txt", 1);
	PrintInt(open);
	PrintChar('\n');

	Close(open);
	*/

	// Test SC_Read
	/*
	int test1 = Open("test1.txt", 1);
	int numBytes = Read("test1.txt", 50, test1);
	PrintInt(numBytes);
	*/
	
	int temp = CreateFile("test3.txt");
	int open = Open("test3.txt", 0);
	int w = Write("CON CAC TAO TO BANG COT DINH", 50, open);

	PrintInt(w);
	PrintChar('\n');
	Halt();
}
