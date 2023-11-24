/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"
#define MAX_LENGTH 100

int compare(int* a, int* b, int order){
	//Ascen
	if (order == 0){
		if (*a < *b)
		{
			return 1;
		}
		return 0;
	}
	
	//Descen
	if (*a < *b)
	{
		return 0;
	}
	return 1;
}

int
main()
{
    int i, j, tmp;
	int order, n, a[MAX_LENGTH+1];
	/*
	//Input array length
	PrintString("Nhap so luong phan tu mang: ");
	n = ReadInt();

	//Handle valid length
	while (n < 0 || n > MAX_LENGTH) {
		PrintString("***ERROR: So luong khong hop le\n");
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

	//Sort
	for (i = 0; i < n - 1; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (!compare(a+i, a+j, order)){
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}

	//Print result
	PrintString("Mang sau khi duoc sap xep:\n\t");
	for (i = 0; i < n; ++i) {
		PrintInt(a[i]);
		PrintChar(' ');
	}
	PrintChar('\n');
	*/
	Halt();
}
