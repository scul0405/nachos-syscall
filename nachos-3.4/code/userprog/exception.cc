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
			case SC_Exit:
				int exitCode;
				exitCode = machine->ReadRegister(4);
				printf("\nProgram closed with exit code: %d", exitCode);
				IncreasePC();
				break;
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
			default:
				printf("\nUnexpected user system call %d %d\n", which, type);
				interrupt->Halt();
		};
	default:
		printf("\nUnexpected user mode exception %d %d\n", which, type);
	}
}
