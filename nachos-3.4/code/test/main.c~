#include "syscall.h"
#include "copyright.h"

int main()
{
	SpaceId fin, fout, fsv, fres;
	int n = 0, i = 0;
	char temp;

	if(CreateSemaphore("main",0) == -1)	return 1;
	if(CreateSemaphore("sinhvien",0) == -1)	return 1;
	if(CreateSemaphore("voinuoc",0)	== -1)	return 1;
	if(CreateSemaphore("end",0) == -1)	return 1;


	if(CreateFile("output.txt") == -1)	return 1;


	fin = Open("input.txt", 1);
	if(fin == -1) return 1;


	fout = Open("output.txt", 0);

	if(fout == -1)
	{
		Close(fin);
		return 1;
	}

	while(1)
	{
		Read(&temp, 1, fin);
		if(temp != '\n')
		{
			if(temp >= '0' && temp <= '9')
				n = n * 10 + (temp - '0');
		}
		else
			break;
	}


	if(Exec("./test/sinhvien") == -1)
	{
		Close(fin);
		Close(fout);
		return 1;
	}

	if(Exec("./test/voinuoc") == -1)
	{
		Close(fin);
		Close(fout);
		return 1;
	}

	for (i; i < n; i++)
	{
		if (CreateFile("sinhvien.txt") == -1){
			Close(fin);
			Close(fout);
			return 1;	
		}

		PrintString("TREO O DAY\n");
		
		fsv = Open("sinhvien.txt", 0);
		if (fsv == -1){
			Close(fin);
			Close(fout);
			return 1;
		}
	
		PrintString("TREO O DAY 1\n");
		
		while(1)
		{
			if(Read(&temp, 1, fin) < 1)
			{
				break;
			}

			if(temp != '\n')
			{
				Write(&temp, 1, fsv);
			}
			else
				break;
						
		}
		// Dong file sinhvien.txt lai
		Close(fsv);
			
		// Goi tien trinh sinhvien hoat dong
		Up("sinhvien");

		// Tien trinh chinh phai cho 
		Down("main");	
		
		// Thuc hien doc file tu result va ghi vao ket qua o output.txt
		fres = Open("result.txt", 1);
		if(fres == -1)
		{
			Close(fin);
			Close(fout);
			return 1;
		}

		// Doc cac voi vao output.txt		
		while(1)
		{
			if(Read(&temp, 1, fres)  < 1)
			{
				Write("\r\n", 2, fout);
				Close(fres);
				Up("end");
				break;
			}
			Write(&temp, 1, fout);
			Write(" ", 1, fout);
			
		}
	}

	Close(fin);
	Close(fout);
	Halt();
	return 0;
}
