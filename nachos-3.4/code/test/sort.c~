/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

/*int A[1024];*/	/* size of physical memory; with code, we'll run out of space!*/
#define MAX_LENGTH 100

int
main()
{
    int i, j, tmp;
	int order, n, a[MAX_LENGTH+1];

	//Input array length
	PrintString("Nhap so luong phan tu mang: ");
	n = ReadInt();

	//Handle valid length
	while (n < 0 || n > MAX_LENGTH) {
		PrintString("***ERROR: So luong khong hop le\n")
		PrintString("Nhap lai n: ");
		n = ReadInt();
	}

	//Input array
	for (i = 0; i < n; ++i) {
		PrintString("a[");
		PrintInt(i);
		PrintString("] = ");
		a[i] = ReadInt();
	}

	//Input order
	PrintString("Nhap thu tu muon sap xep ");
	PrintString("[0 - tang dan, 1 - giam dan] : ");
	order = ReadInt();
	while (order != 0 && order != 1) {
		PrintString("***ERROR: Thu tu khong hop le\n");
		PrintString("Nhap thu tu muon sap xep: ");
		order = ReadInt();
	}

    /* first initialize the array, in reverse sorted order */
	/*
    for (i = 0; i < 1024; i++)		
        A[i] = 1024 - i;
	*/
    /* then sort! */
	/*
    for (i = 0; i < 1023; i++)
        for (j = i; j < (1023 - i); j++)
	   if (A[j] > A[j + 1])*/ {	/* out of order -> need to swap ! */
	/*
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
    Exit(A[0]);
	*/
	/* and then we're done -- should be 0! */
}
