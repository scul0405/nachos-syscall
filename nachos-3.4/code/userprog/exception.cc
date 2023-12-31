// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "console.h"

#define MaxFileLength 32

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

char* User2System(int virtAddr, int limit)
{
	int i; //chi so index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; //can cho chuoi terminal
	if (kernelBuf == NULL)
		return kernelBuf;
		
	memset(kernelBuf, 0, limit + 1);
	
	for (i = 0; i < limit; i++)
	{
		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0;
	do{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}

void IncreasePC()
{
	int pcAfter = machine->registers[NextPCReg] + 4; // tang next PC len 4 (vi int 4 byte)

	machine->registers[PrevPCReg] = machine->registers[PCReg]; // gan previous PC register = current PC register
	machine->registers[PCReg] = machine->registers[NextPCReg]; // gan current PC register = next PC register
	machine->registers[NextPCReg] = pcAfter;	
}

void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch(which)
    {
	case NoException:
		return;
	case PageFaultException:
		DEBUG('a', "\nPage Fault Error.");
		printf("\n\nPage Fault Error.");
		interrupt->Halt();
		break;
	case ReadOnlyException:
		DEBUG('a', "\nRead Only Error.");
		printf("\n\nRead Only Error.");
		interrupt->Halt();
		break;
	case BusErrorException:
		DEBUG('a', "\nBus Error.");
		printf("\n\nBus Error.");
		interrupt->Halt();
		break;
	case AddressErrorException:
		DEBUG('a', "\nAddress Error.");
		printf("\n\nAddress Error.");
		interrupt->Halt();
		break;
	case OverflowException:
		DEBUG('a', "\nOverflow Error.");
		printf("\n\nOverflow Error.");
		interrupt->Halt();
		break;
	case IllegalInstrException:
		DEBUG('a', "\nIllegal Instruction Error.");
		printf("\n\nIllegal Instruction Error.");
		interrupt->Halt();
		break;
	case SyscallException:
		switch (type)
		{
			case SC_Halt:
				DEBUG('a', "\nShutdown, initiated by user program.");
				printf("\n\nShutdown, initiated by user program.");
				interrupt->Halt();
				break;
			case SC_ReadInt:
			/*
				Input: khong
				Output: tra ve so nguyen doc tu console
				Chuc nang: doc mot so nguyen tu console
			*/
			{
				char* str;
				int MAX_LENGTH = 255;	
				str = new char[255];

				memset(str, 0, MAX_LENGTH);

				int lenStr = gSynchConsole->Read(str, 255);

				// Dam bao chuoi ket thuc dung cach
				if (str[lenStr - 1] == '\n') {
					str[lenStr - 1] = '\0';
				}		

				// Kiem tra va in ket qua
				bool isInteger = true;
				bool isNegative = false;
				int number = 0;
				int startIndex = 0;

				// Kiem tra so am hay so duong
				if (str[0] == '-') {
					isNegative = true;
					startIndex = 1;
				} 
				else if (str[0] == '+') {
					startIndex = 1;
				}

				// Kiem tra tung ky tu trong chuoi
				for (int i = startIndex; str[i] != '\0'; i++) {
					if (str[i] < '0' || str[i] > '9') {
						isInteger = false;
						break;
					}
					number = number * 10 + (str[i] - '0');
				}

				if (isNegative) {
					number = -number;
				}

				if (isInteger) {
					machine->WriteRegister(2, number);
				}
				else {
					printf("  Invalid number ! ");
					DEBUG('a', "\nERROR: Invalid number ! ");
					machine->WriteRegister(2, 0);
				}
			
				delete str;
				IncreasePC();
				return;	
			}
			case SC_PrintInt:
			/*
				Input: 1 so nguyen
				Output: khong
				Chuc nang: in so nguyen ra man hinh console
			*/
			{
				int number = machine->ReadRegister(4);
				int temp;
				int digitCount = 0;
    				bool isNegative = false;

				// Kiem tra so am
				if (number < 0) {
					isNegative = true;
        				temp = -number;
				}
				temp = number;

				// Truong hop number == 0
				if (number == 0) {
					digitCount = 1;
				}

				while (temp != 0) {
					temp /= 10;
					digitCount++;
				}
				
				// Chuyen doi tu int sang char[] de in ra man hinh
				char buffer[100];
				int startIndex = 0;

				if (isNegative) {
					buffer[0] = '-';
					startIndex = 1;
					number = -number;
				}
		
				for (int i = digitCount + startIndex - 1; i >= startIndex; i--) {
					buffer[i] = '0' + (number % 10);
					number /= 10;
				}

				buffer[digitCount + startIndex] = '\0';
				gSynchConsole->Write(buffer, digitCount + startIndex);
				IncreasePC();
				return;

			}			

			case SC_ReadChar:
			/*
				Input: khong
				Output: mot ky tu
				Chuc nang: doc mot ky tu tu man hinh
			*/
			{
				int maxBuffer;
				char *buffer_RC;
				char c_RC;

				maxBuffer = 255;
				buffer_RC = new char[255];

				memset(buffer_RC, 0, maxBuffer);

				gSynchConsole->Read(buffer_RC, maxBuffer); // read buffer from screen        
				c_RC = buffer_RC[0];
				machine->WriteRegister(2, c_RC); // return c to register 2
				
				delete[] buffer_RC;
				IncreasePC();
				return;
			}
			case SC_PrintChar:
			/*
				Input: mot ky tu
				Output: khong
				Chuc nang: xuat mot ky tu ra man hinh
			*/
			{ 
				char buffer_PC;

				buffer_PC = machine->ReadRegister(4); // read the input params
				gSynchConsole->Write(&buffer_PC, 1);
				
						IncreasePC();
				return;
			}
			case SC_ReadString:
			/*
				Input: mot chuoi ky tu
				Output: khong
				Chuc nang: doc mot chuoi ky tu ra man hinh
			*/
			{
				
				int virtAddr_RS;
				int len_RS;
				char* buffer_RS;
				virtAddr_RS = machine->ReadRegister(4); // get buffer position
				len_RS = machine->ReadRegister(5); // get buffer length
				buffer_RS = User2System(virtAddr_RS, len_RS); // get buffer
				gSynchConsole->Read(buffer_RS, len_RS); // read buffer
				System2User(virtAddr_RS, len_RS, buffer_RS); // return to user
				delete buffer_RS;
				IncreasePC();
				return; 
			}
			case SC_PrintString:
			/*
				Input: mot chuoi ky tu
				Output: khong
				Chuc nang: xuat mot chuoi ky tu ra man hinh
			*/
			{ 
				int virtAddr_PR;
				char* buffer_PR;
				int len_PR;
				
				virtAddr_PR = machine->ReadRegister(4); // get buffer position
				buffer_PR = User2System(virtAddr_PR, 255); // get buffer
				len_PR = 1;
				
				while(buffer_PR[len_PR] != 0 && len_PR < 255) // get buffer length and max len is 255
				{
					len_PR++;
				}
				
				gSynchConsole->Write(buffer_PR, len_PR); // write buffer
				delete buffer_PR;
				IncreasePC();
				return;
        }
		case SC_Seek:
		{
			// Input: Vi tri(int), id cua file(OpenFileID)
			// Output: -1: Loi, Vi tri thuc su: Thanh cong
			// Cong dung: Di chuyen con tro den vi tri thich hop trong file voi tham so la vi tri can chuyen va id cua file
			int pos = machine->ReadRegister(4); // Lay vi tri can chuyen con tro den trong file
			int id = machine->ReadRegister(5); // Lay id cua file
			// Kiem tra id cua file truyen vao co nam ngoai bang mo ta file khong
			if (id < 0 || id > 14)
			{
				printf("\nKhong the seek vi id nam ngoai bang mo ta file.");
				machine->WriteRegister(2, -1);
				IncreasePC();
				return;
			}
			// Kiem tra file co ton tai khong
			if (fileSystem->fileTable[id] == NULL)
			{
				printf("\nKhong the seek vi file nay khong ton tai.");
				machine->WriteRegister(2, -1);
				IncreasePC();
				return;
			}
			// Kiem tra co goi Seek tren console khong
			if (id == 0 || id == 1)
			{
				printf("\nKhong the seek tren file console.");
				machine->WriteRegister(2, -1);
				IncreasePC();
				return;
			}
			// Neu pos = -1 thi gan pos = Length nguoc lai thi giu nguyen pos
			pos = (pos == -1) ? fileSystem->fileTable[id]->Length() : pos;
			if (pos > fileSystem->fileTable[id]->Length() || pos < 0) // Kiem tra lai vi tri pos co hop le khong
			{
				printf("\nKhong the seek file den vi tri nay.");
				machine->WriteRegister(2, -1);
			}
			else
			{
				// Neu hop le thi tra ve vi tri di chuyen thuc su trong file
				fileSystem->fileTable[id]->Seek(pos);
				machine->WriteRegister(2, pos);
			}
			IncreasePC();
			return;
		}
		case SC_CreateSemaphore:
		{
			int virtAddr = machine->ReadRegister(4);
			int semVal = machine->ReadRegister(5);

			char *name = User2System(virtAddr, MaxFileLength + 1);
			if (name == NULL){
				DEBUG('a', "\n Not enough memory in System");
				printf("\n Not enough memory in System");

				machine->WriteRegister(2, -1);
				delete[] name;
				IncreasePC();
				return;			
			}

			int res = stab->Create(name, semVal);

			if(res == -1) // 0 for success, -1 for failed
			{
				DEBUG('a', "\n Cannot create semaphore");
				printf("\n Cannot create semaphore");
				machine->WriteRegister(2, -1);
				delete[] name;
				IncreasePC();
				return;				
			}
			
			delete[] name;
			machine->WriteRegister(2, res);
			IncreasePC();
			return;
		}
			case SC_CreateFile:
			{
			/*
				Input: dia chi ten file
				Output: tra ve 0 - Success / 1 - Error
				Chuc nang: tao 1 file bat ki
			*/
				int virtAddr;
				char* filename;

				DEBUG('a',"\n SC_Create call ...");
				DEBUG('a',"\n Reading virtual address of filename");

				// check for exception
				virtAddr = machine->ReadRegister(4);
				DEBUG ('a',"\n Reading filename.");

				filename = User2System(virtAddr,MaxFileLength + 1); // MaxFileLength = 32

				// Neu khong lay duoc ten file
				if (filename == NULL)
				{
					printf("\n Not enough memory in system");
					DEBUG('a',"\n Not enough memory in system");
					machine->WriteRegister(2,-1); // Tra ve -1 o thanh ghi R2
					delete filename;
					IncreasePC();
					return;
				}

				// Neu nguoi dung khong nhap ten file
				if (strlen(filename) == 0)
				{
					printf("\n INVALID filename");
					DEBUG('a',"\n INVALID filename");
					machine->WriteRegister(2,-1); // Tra ve -1 o thanh ghi R2
					delete filename;
					IncreasePC();
					return;	
				}

				DEBUG('a',"\n Finish reading filename.");

				// Dung fileSystem cua OpenFile class de tao file
				if (!fileSystem->Create(filename, 0))
				{
					// Tao file loi
					printf("\n Error create file '%s'",filename);
					machine->WriteRegister(2,-1);
					delete filename;
					IncreasePC();
					return;
				}

				// Tao file
				printf("\n\nCreate file '%s' successfully.", filename);
				machine->WriteRegister(2, 0);
				delete filename;
				IncreasePC();
				return;
					
			}

			case SC_Open:
			{
			/*
				Input: dia chi ten file & bien so nguyen type
				Output: tra ve OpenFileID -- Success / -1 -- Error
				Chuc nang: tra ve ID cua file open
			*/
				int virtAddr;
				int type;
				char* filename;

				DEBUG('a',"\n SC_Open call ...");
				DEBUG('a',"\n Reading virtual address of filename");

				// check for exception
				virtAddr = machine->ReadRegister(4);		// Doc dia chi cua ten file tai thanh ghi R4
				type = machine->ReadRegister(5);		// doc type tai thanh ghi R5

				filename = User2System(virtAddr,MaxFileLength); // MaxFileLength = 32 

				// Neu ten file khong co
				if (strlen(filename) == 0) {
					machine->WriteRegister(2, -1);
					delete filename;

					IncreasePC();
					return;
				}
				
				int NullPos = fileSystem->findNullPos();

				if (NullPos != -1)	// Neu con vi tri trong
				{
					// Console input
					if (type == -2) {
						machine->WriteRegister(2, 0);
					}
					// Console output
					else if (type == -1) {
						machine->WriteRegister(2, 1);
					}
					else if (type == 0 || type == 1) {
						fileSystem->fileTable[NullPos] = fileSystem->Open(filename, type);

						// Neu khong tim thay file trong directory
						if (fileSystem->fileTable[NullPos] == NULL) {
							machine->WriteRegister(2, -1);
						}

						// Mo file thanh cong
						if (fileSystem->fileTable[NullPos] != NULL) {
							machine->WriteRegister(2, NullPos);
						}
					}
					delete filename;
					IncreasePC();
					return;
				}
				machine->WriteRegister(2, -1);
				delete filename;

				IncreasePC();
				return;
			}

			case SC_Close:
			/*
				Input: ID cua file
				Output: tra ve 0 -- Success / -1 -- Error
				Chuc nang: xoa vung nho cua file
			*/
			{
				int fileID;
						
				// Lay tham so ID tu thanh ghi R4
				fileID = machine->ReadRegister(4);	

				// Nam trong bang mo ta [0, 9]
				if (fileID <= 9 && fileID >= 0) {
					// Ton tai file
					if (fileSystem->fileTable[fileID] != NULL) {
						delete fileSystem->fileTable[fileID];
						fileSystem->fileTable[fileID] = NULL;
						printf("\nClose successfully.");
						machine->WriteRegister(2, 0);
						IncreasePC();
						return;				
					}
				}
				
						
				machine->WriteRegister(2, -1);
				IncreasePC();
				return;	
			
			}

			case SC_Read:
			/*
				Input: char *buffer (dia chi ten file, int charcount (so ki tu), OpenFileID id (id file)
				Output: -1: Error / so byte thuc su: Success / -2: het file 
				Chuc nang: doc file 
			*/
			{
				// Lay dia chi ten file
				int virtAddr = machine->ReadRegister(4);

				// Lay so ki tu cho phep
				int charcount = machine->ReadRegister(5);

				// Lay id file
				int id = machine->ReadRegister(6);

				// Neu id file khong nam trong bang mo ta file
				if (id > 9 || id < 0) {
					printf("\nINVALID ID.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Neu file khong ton tai
				if (fileSystem->fileTable[id] == NULL) {
					printf("\nFile doesn't exist.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Neu file la stdout (type == -1)
				if (fileSystem->fileTable[id]->_type == -1) {
					printf("\nCannot read on stdout.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Bo dem de xu li giua User Space va System Space
				char* tempBuffer = User2System(virtAddr, charcount);

				// Lay vi tri dau tien cua file noi con tro dang tro toi
				int beginPos = fileSystem->fileTable[id]->getCurrentOffset();	

				
				// Neu file la stdin (type == -2)
				if (fileSystem->fileTable[id]->_type == -2) {
					// Read file va tra ve so byte thuc su doc duoc
					int numBytes = gSynchConsole->Read(tempBuffer, charcount);

					System2User(virtAddr, numBytes, tempBuffer);

					// Tra ve so byte thuc su doc duoc
					machine->WriteRegister(2, numBytes);
					delete tempBuffer;
					IncreasePC();
					return;
				}

				// File binh thuong
				int checker = fileSystem->fileTable[id]->Read(tempBuffer, charcount);
				// Doc file thanh cong
				if (checker > 0) {
					int endPos = fileSystem->fileTable[id]->getCurrentOffset();
					int numBytes = endPos - beginPos;

					System2User(virtAddr, numBytes, tempBuffer);
					machine->WriteRegister(2, numBytes);
				} 
				// Cuoi file -> file rong -> doc NULL
				else {
					printf("\nEmpty file.");
					machine->WriteRegister(2, -2);
				}

				delete tempBuffer;
				IncreasePC();
				return;
			}

			case SC_Write:
			/*
				Input: char *buffer (noi dung can ghi vao file), int charcount (so ki tu ), OpenFileID id (id file)
				Output: -1: Error / so byte write thuc su: Success / -2: het file 
				Chuc nang: ghi file
			*/
			{
				// Lay dia chi ten file
				int virtAddr = machine->ReadRegister(4);

				// Lay so ki tu cho phep
				int charcount = machine->ReadRegister(5);

				// Lay id file
				int id = machine->ReadRegister(6);

				// Neu id file khong nam trong bang mo ta file
				if (id > 9 || id < 0) {
					printf("\nINVALID ID.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Neu file khong ton tai
				if (fileSystem->fileTable[id] == NULL) {
					printf("\nFile doesn't exist.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Neu la file stdin (type == -2) || file chi doc (type == 1)
				if (fileSystem->fileTable[id]->_type == -2 || fileSystem->fileTable[id]->_type == 1) {
					printf("\nINVALID File Type.");
					machine->WriteRegister(2, -1);
					IncreasePC();
					return;
				}

				// Bo dem de xu li giua User Space va System Space
				char* tempBuffer = User2System(virtAddr, charcount);
				
				// Lay vi tri dau tien cua file noi con tro dang tro toi
				int beginPos = fileSystem->fileTable[id]->getCurrentOffset();

				// Neu la stdout (type == -1) thi se output ra console chu khong ghi vao 
				if (fileSystem->fileTable[id]->_type == -1) {
					// Vong lap den khi gap '\n' hoac ket thuc chuoi '\0'
					int i = 0;
					for (i; ;i++) {
						if (tempBuffer[i] == '\0' || tempBuffer[i] == '\n') {
							break;
						}
						gSynchConsole->Write(tempBuffer + i, 1);
					}
					
					// Xuong dong
					tempBuffer[i] = '\n';

					gSynchConsole->Write(tempBuffer + i, 1); // Write ky tu '\n'
					machine->WriteRegister(2, i); // Tra ve so byte thuc su write duoc
					delete tempBuffer;
					IncreasePC();
					return;

				}

				// Neu la file doc va ghi
				int checker = fileSystem->fileTable[id]->Write(tempBuffer, charcount);
				// Ghi file thanh cong
				if (checker > 0) {
					int endPos = fileSystem->fileTable[id]->getCurrentOffset();
					int numBytes = endPos - beginPos;

					machine->WriteRegister(2, numBytes);
				} 
				// Cuoi file 
				else {
					printf("\nEmpty file.");
					machine->WriteRegister(2, -2);
				}

				delete tempBuffer;
				IncreasePC();
				return;
			}
			case SC_Exec:
			/*
				Input: mot chuoi ky tu
				Output: khong
				Chuc nang: xuat mot chuoi ky tu ra man hinh
			*/
			{
				int virtAddr;
				virtAddr = machine->ReadRegister(4);	// get filename position
				char* filename;
				filename = User2System(virtAddr, 255); // get filename
				
			if (filename == NULL)
			{
				printf("\nNot enough memory in System");
				machine->WriteRegister(2, -1);
				IncreasePC();
				return;
			}

			OpenFile *oFile = fileSystem->Open(filename);
			
			if (oFile == NULL)
			{
				printf("\nUnable to open file %s", filename);
				machine->WriteRegister(2,-1);
				IncreasePC();
				return;
			}
			
			delete oFile;

			int id = gPTable->ExecUpdate(filename);

			machine->WriteRegister(2,id);
			delete[] filename;	
			IncreasePC();
			return;
		}
			case SC_Join:
			{
				//get process id
				int pid = machine->ReadRegister(4);

				//JoinUpdate return exit code, if there is no error, exit code = 0;
				int exitCode = gPTable->JoinUpdate(pid);

				//return exit code
				machine->WriteRegister(2, exitCode);
				//increase program counter
				IncreasePC();

				return;
			}
      
		  case SC_Down:
		  {
		    int virtAddr = machine->ReadRegister(4);
		    
		    char* name = User2System(virtAddr, MaxFileLength + 1);
		    if (name == NULL) {
		      printf("\nSystem khong du bo nho");
		      machine->WriteRegister(2, -1); // failed
		      delete[] name;
  		      IncreasePC();
		      return;
		    }

		    int result = stab->Wait(name);

		    if (result == -1)
		    {
		      printf("\nKhong ton tai semaphore '%s'", name);
		      machine->WriteRegister(2, -1); // failed
		      delete[] name;
			  IncreasePC();
		      return;
		    }
		    
		    delete[] name;
		    machine->WriteRegister(2, result); // success
			IncreasePC();
		    return;
		  }

		  case SC_Up: 
		  {
		    int virtAddr = machine->ReadRegister(4);
		    
		    char* name = User2System(virtAddr, MaxFileLength + 1);

		    if (name == NULL) {
		      printf("\nSystem khong du bo nho");
		      machine->WriteRegister(2, -1); // failed
		      delete[] name;
			  IncreasePC();
		      return;
		    }

		    int result = stab->Signal(name);

		    if (result == -1)
		    {
		      printf("\nKhong ton tai semaphore '%s'", name);
		      machine->WriteRegister(2, -1); // failed
		      delete[] name;
			  IncreasePC();
		      return;
		    }

		    delete[] name;
		    machine->WriteRegister(2, result); // success
			IncreasePC();
		    return;
		  }

			case SC_Exit:
			{
				//Get exit code from join process
				int joinExitCode = machine->ReadRegister(4);
				
				//If any erros => stop process
				if(joinExitCode != 0)
				{
					IncreasePC();
					return;
				
				}			
			
				gPTable->ExitUpdate(joinExitCode);
				//machine->WriteRegister(2, res);

				currentThread->FreeSpace();
				currentThread->Finish();
				IncreasePC();
				return;
			}
			default:
				printf("\nUnexpected user system call %d %d\n", which, type);
				interrupt->Halt();
		};
	default:
		printf("\nUnexpected user mode exception %d %d\n", which, type);
	}
}
