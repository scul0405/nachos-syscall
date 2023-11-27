/* ascii.c 
 *    Test program to ascii table.
 *
 *    Intention is to stress virtual memory system.
 */

#include "syscall.h"

int
main()
{
    int i,j,curr;
	
	PrintString("\n--Chuong trinh in bang ma ascii (cac ki tu co the thay duoc)--\n");
/*
    for (i = 0; i <= 126; i++){
		// PrintString("Ki tu thu i: ");		
		// PrintInt(i);
		// PrintString(": ");

		PrintChar((char)i);
		PrintChar('\n');
	}
*/
    for (i = 32; i <= 52; i++){
		curr = i;
		for (j = 0; j <= 6; j++){
			if (curr<=127){
				PrintInt(curr);
				PrintString("\t");
				PrintChar((char)curr);

			}
			PrintString("\t");
			curr+=20;
		}
		PrintChar('\n');
	}
	Halt();
}
