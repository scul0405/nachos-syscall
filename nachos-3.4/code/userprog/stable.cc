#include "stable.h"

STable::STable()
{	
	this->bm = new BitMap(MAX_LOCK);
	
	for(int i =0; i < MAX_LOCK; i++)
	{
		this->semList[i] = nullptr;
	}
}

STable::~STable()
{
	if(this->bm)
	{
		delete this->bm;
		this->bm = nullptr;
	}
	for(int i=0; i < MAX_LOCK; i++)
	{
		if(this->semList[i])
		{
			delete this->semList[i];
			this->semList[i] = nullptr;
		}
	}
	
}

int STable::Create(char *name, int init)
{

	// Check if exists semaphore or not?
	for(int i=0; i<MAX_LOCK; i++)
	{
		if(bm->Test(i))
		{
			if(strcmp(name, semList[i]->GetName()) == 0)
			{
				return -1;
			}
		}
		
	}
	// Find free slot
	int id = this->FindFreeSlot();
	
	// Cannot find free slot -> can't create -> return -1
	if(id < 0)
	{
		return -1;
	}

	// Load semaphore to semList[id]
	this->semList[id] = new Sem(name, init);
	return 0;
}

int STable::Wait(char *name)
{
	for(int i =0; i < MAX_LOCK; i++)
	{
		// Check block i is loaded semaphore or not?
		if(bm->Test(i))
		{
			// compare name
			if(strcmp(name, semList[i]->GetName()) == 0)
			{
				// If exists -> turn down semaphore
				semList[i]->wait();
				return 0;
			}
		}
	}
	printf("Semaphore doesn't exist");
	return -1;
}

int STable::Signal(char *name)
{
	for(int i =0; i < MAX_LOCK; i++)
	{
		// Check block i is loaded semaphore or not?
		if(bm->Test(i))
		{
			// compare name
			if(strcmp(name, semList[i]->GetName()) == 0)
			{
				// If exists -> turn up semaphore
				semList[i]->signal();
				return 0;
			}
		}
	}
	printf("Semaphore doesn't exist");
	return -1;
}

int STable::FindFreeSlot()
{
	return this->bm->Find();
}
