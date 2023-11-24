/* ascii.c 
 *    Test program to ascii table.
 *
 *    Intention is to stress virtual memory system.
 */

#include "syscall.h"

int
main()
{
    int i;
	
	PrintString("\n--Chuong trinh in bang ma ascii (cac ki tu co the thay duoc)--\n");
    for (i = 32; i <= 126; i++){
		// PrintString("Ki tu thu i: ");		
		// PrintInt(i);
		// PrintString(": ");
		PrintChar((char)i);
		PrintChar('\n');
	}
	
	Halt();
}
