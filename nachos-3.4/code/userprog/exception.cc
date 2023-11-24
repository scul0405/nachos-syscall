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
 			case SC_ReadString:
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
				break;
 			case SC_PrintString:
			{
				int virtAddr_PR;
				char* buffer_PR;
				virtAddr_PR = machine->ReadRegister(4); // get buffer position
				buffer_PR = User2System(virtAddr_PR, 255); // get buffer
				int len_PR = 1;
				while(buffer_PR[len_PR] != 0 && len_PR < 255) // get buffer length and max len is 255
				{
					len_PR++;
				}
				gSynchConsole->Write(buffer_PR, len_PR); // write buffer
				delete buffer_PR;
				IncreasePC();
				break;
			}
			default:
				printf("\nUnexpected user mode exception %d %d\n", which, type);
				interrupt->Halt();
				break;
		}
		break;
	default:
		printf("\nUnexpected user mode exception %d %d\n", which, type);
	}
}
