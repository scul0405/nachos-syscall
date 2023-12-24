include "syscall.h"
#include "copyright.h"

int main()
{
	SpaceId fin, fout;
	int n = 0;
	char temp;

	if(CreateSemaphore("main",0) == -1)	return 1;
	if(CreateSemaphore("sinhvien",0) == -1)	return 1;
	if(CreateSemaphore("voinuoc",0)	== -1)	return 1;
	if(CreateSemaphore("end",0) == -1)	return 1;
	if(CreateFile("output.txt") == -1)	return 1;

	fin = Open("input.txt", 1);
	if(fin != -1) return 1;

	fout = Open("output.txt", 0);

	if(fout != -1)
	{
		Close(fin);
		return 1;
	}

	while(true)
	{
		Read(&temp, 1, fin);
		if(temp != '\n')
		{
			if(c_readFile >= '0' && c_readFile <= '9')
				SLTD = SLTD * 10 + (c_readFile - '0');
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

	for (int i = 0; i < n; i++)
	{
		while(1)
		{
			if(Read(&c_readFile, 1, si_input) < 1)
			{
				// Doc toi cuoi file
				break;
			}
			if(c_readFile != '\n')
			{
				Write(&c_readFile, 1,si_sinhvien);	
			}
			else
				break;
						
		}
		// Dong file sinhvien.txt lai
		Close(si_sinhvien);
			
		// Goi tien trinh sinhvien hoat dong
		Signal("sinhvien");

		// Tien trinh chinh phai cho 
		Wait("main");	
		
		// Thuc hien doc file tu result va ghi vao ket qua o output.txt
		si_result = Open("result.txt", 1);
		if(si_result == -1)
		{
			Close(si_input);
			Close(si_output);
			return 1;
		}

		PrintString("\n Lan thu: ");
		PrintInt(SLTD);
		PrintString("\n");	

		// Doc cac voi vao output.txt		
		while(1)
		{
			if(Read(&c_readFile, 1, si_result)  < 1)
			{
				Write("\r\n", 2, si_output);
				Close(si_result);
				Signal("m_vn");
				break;
			}
			Write(&c_readFile, 1, si_output);
			Write(" ", 1, si_output);
			
		}
	}

	Halt();
}
