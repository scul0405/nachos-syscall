#include "ptable.h"
#include "system.h"
#include "openfile.h"

PTable::PTable(int size)
{

    if (size < 0)
        return;

    psize = size;
    bm = new BitMap(size);
    bmsem = new Semaphore("bmsem",1);

    for(int i = 0; i < 10; i++)
    {
		pcb[i] = 0;
    }

	bm->Mark(0);

	pcb[0] = new PCB(0);
	pcb[0]->SetFileName("");
	pcb[0]->parentID = -1;
}

PTable::~PTable()
{
    if( bm != 0 )
	delete bm;
    
    for(int i = 0; i < psize; i++)
    {
	if(pcb[i] != 0)
		delete pcb[i];
    }
		
	if( bmsem != 0)
		delete bmsem;
}

int PTable::ExecUpdate(char* name)
{

	bmsem->P();

	if(name == NULL)
	{
		printf("\nCan't not execute.");
		bmsem->V();
		return -1;
	}

	if( strcmp(name,"") == 0 || strcmp(name,currentThread->getName()) == 0 )
	{
		printf("\nCan't not execute.");		
		bmsem->V();
		return -1;
	}

	int index = this->GetFreeSlot();

	if(index < 0)
	{
		printf("\nThere is no empty slot.");
		bmsem->V();
		return -1;
	}

	pcb[index] = new PCB(index);
	pcb[index]->SetFileName(name);
    	pcb[index]->parentID = currentThread->processID;
	int pid = pcb[index]->Exec(name,index);
	bmsem->V();
	return pid;
}

int PTable::JoinUpdate(int id)
{
	return 0;
}
int PTable::ExitUpdate(int exitcode)
{              
	return 0;
}

int PTable::GetFreeSlot()
{
	return bm->Find();
}

bool PTable::IsExist(int pid)
{
	return bm->Test(pid);
}

void PTable::Remove(int pid)
{
	bm->Clear(pid);
	if(pcb[pid] != 0)
		delete pcb[pid];
}

char* PTable::GetFileName(int id)
{
	return (pcb[id]->GetFileName());
}
