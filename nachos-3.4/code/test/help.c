/* help.c 
 *    Test program to print information about team, describe about program sort and ascii.
 */

#include "syscall.h"

int
main(){
	PrintString("--THONG TIN NHOM--\n");
	PrintString("\t21120262 - Nguyen Huynh Huu Khang\n");
	PrintString("\t21120300 - Phan Thanh Ha Nguyen\n");
	PrintString("\t21120353 - Vi Ly Duy Truong\n");
	PrintString("\t21120359 - Pham Quang Tuyen\n");
	PrintString("\t21120530 - Nguyen Hoang Phuc\n\n");
	
	PrintString("--MO TA CHUONG TRINH--\n");
	PrintString("- ascii: Chuong trinh in ra bang ma ascii");
	PrintString(", chi in cac ki tu co the thay duoc (32-127).\n");	
	PrintString("- sort: Chuong trinh nhap vao mang so nguyen ");
	PrintString("de sap xep bang thuat toan bubble sort. ");
	PrintString("Co the sap xep theo thu tu tang dan hoac giam dan.\n");
	Halt();
}
