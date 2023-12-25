#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	SpaceId fsv, fvn;
	char temp;
	int flagVN;
	int flagMAIN;
	int lengthFile;
	int filePtr;
	//-----------------------------------------------------------
	Up("end");	

	while(1)
	{
		lengthFile = 0;

		Down("sinhvien");
		
		if(CreateFile("result.txt") == -1)
		{
			Up("main"); // tro ve tien trinh chinh
			return;
		}

		// Mo file sinhvien.txt len de doc
		fsv = Open("sinhvien.txt", 1);
		if(fsv == -1)
		{
			Up("main"); // tro ve tien trinh chinh
			return;
		}
		
		lengthFile = Seek(-1, fsv);
		Seek(0, fsv);
		filePtr = 0;
	
		// Tao file voinuoc.txt
		if(CreateFile("voinuoc.txt") == -1)
		{
			Close(fsv);
			Up("main"); // tro ve tien trinh chinh
			return;
		}
		

		// Mo file voinuoc.txt de ghi tung dung tich nuoc cua sinhvien
		fvn = Open("voinuoc.txt", 0);
		if(fvn == -1)
		{
			Close(fsv);
			Up("main"); // tro ve tien trinh chinh
			return;
		}
		
		// Ghi dung tich vao file voinuoc.txt tu file sinhvien.txt
		while(filePtr < lengthFile)
		{
			flagVN = 0;
			Read(&temp, 1, fsv);
			if(temp != ' ')
			{
				Write(&temp, 1, fvn);
			}
			else
			{
				flagVN = 1;
			}
			if(filePtr == lengthFile - 1)
			{
				Write("*", 1, fvn);
				flagVN = 1;
			}
			
				
			if(flagVN == 1)
			{
				Close(fvn);
				Up("voinuoc");
				// Dung chuong trinh sinhvien lai de voinuoc thuc thi
				Down("sinhvien");
				
				// Tao file voinuoc.txt
				if(CreateFile("voinuoc.txt") == -1)
				{
					Close(fsv);
					Up("main"); // tro ve tien trinh chinh
					return;
				}
		

				// Mo file voinuoc.txt de ghi tung dung tich nuoc cua sinhvien
				fvn = Open("voinuoc.txt", 0);
				if(fvn == -1)
				{
					Close(fsv);
					Up("main"); // tro ve tien trinh chinh
					return;
				}
				
			}
			filePtr++;			
							
		}				
		// Ket thuc tien trinh sinhvien va voinuoc quay lai ham main
		Up("main");			
	}
	// Quay lai ham main
}

