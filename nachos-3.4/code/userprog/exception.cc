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

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
	
	switch(which){
		case NoException:
			return;
		case PageFaultException:
			DEBUG('a', "Page Fault Error.\n");
			printf("Page Fault Error.\n\n");
			interrupt->Halt();
			break;
		case ReadOnlyException:
			DEBUG('a', "Read Only Error.\n");
			printf("Read Only Error.\n\n");
			interrupt->Halt();
			break;
		case BusErrorException:
			DEBUG('a', "Bus Error.\n");
			printf("Bus Error.\n\n");
			interrupt->Halt();
			break;
		case AddressErrorException:
			DEBUG('a', "Address Error.\n");
			printf("Address Error.\n\n");
			interrupt->Halt();
			break;
		case OverflowException:
			DEBUG('a', "Overflow Error.\n");
			printf("Overflow Error.\n\n");
			interrupt->Halt();
			break;
		case IllegalInstrException:
			DEBUG('a', "Illegal Instruction Error.\n");
			printf("Illegal Instruction Error.\n\n");
			interrupt->Halt();
			break;

		case SyscallException:
			switch(type){
				case SC_Halt:
					DEBUG('a', "Shutdown, initiated by user program.\n");
					printf ("Shutdown, initiated by user program.\n\n");
					interrupt->Halt();
					break;
				case SC_Exit:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Exec:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Join:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Create:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Open:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Open:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Read:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Write:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Close:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Fork:
					// Handle here
					
					IncreasePC();
					break;
				case SC_Yield:
					// Handle here
					
					IncreasePC();
					break;
					

				default:
					printf("Unexpected user mode exception %d %d\n", which, type);
					interrupt->Halt();	
			}

		default:
			printf("Unexpected user mode exception %d %d\n", which, type);
			// ASSERT(FALSE); chua hieu day la cai gi ???
	}
}

void IncreasePC(){
	int pcAfter = machine->registers[NextPCReg] + 4 // tang next PC len 4 (vi int 4 byte)

	machine->registers[PrevPCReg] = machine->registers[PCReg]; // gan previous PC register = current PC register
    machine->registers[PCReg] = machine->registers[NextPCReg]; // gan current PC register = next PC register
    machine->registers[NextPCReg] = pcAfter; // gan next PC register = pcAfter vua tinh o phia tren
}
