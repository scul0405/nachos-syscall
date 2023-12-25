#include "syscall.h"
#include "copyright.h"

void main()
{
	// Khai bao
	SpaceId  fvn, fres;	// Bien id cho file
	char temp;	// Bien ki tu luu ki tu doc tu file
	int v1, v2;		// Voi 1, voi 2
	int v;			// Dung tich nuoc cua sinh vien
	int flag_done_result;	// Bien co luu dau hieu doc xong file result

	//-----------------------------------------------------------
	
	v1 = v2 = 0;
	// Xu ly voi nuoc
	while(1)
	{
		Wait("end");

		// Mo file result.txt de ghi voi nao su dung
		fres = Open("result.txt", 0);
		if(fres == -1)
		{		//?
			Signal("sinhvien");
			return;
		}
		while(1)
		{
			Wait("voinuoc");
			temp = 0;			
			// Mo file voi nuoc .txt de doc dung tich
			fvn = Open("voinuoc.txt", 1);
			if(fvn == -1)
			{
				//?
				Close(fres);
				Signal("sinhvien");
			
				return;
			}
		
			v = 0;
			flag_done_result = 0;
			while(1)
			{			
				if(Read(&temp, 1, fvn)  == -2)
				{	
					Close(fvn);			
					break;
				}
				if(temp != '*')
				{
					v = v* 10 + (temp - 48);
				}
				else
				{
					flag_done_result = 1;				
					Close(fvn);
					break;			
				}
			
			}
			if(v!= 0)
			{
				// Dung voi 1
				if(v1 <= v2)
				{
					v1 += v;
					Write("1", 1, fres);
				}
				else	// Dung voi 2
				{					
					v2 += v;
					Write("2", 1, fres);
					
				}
			}
		
			if(flag_done_result == 1)
			{
				v1 = v2 = 0;
				Close(fres);				
				Signal("sinhvien");
				break;				
			}

			Signal("sinhvien");
		}	
	}		
}

