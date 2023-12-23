#ifndef STABLE_H
#define STABLE_H
#include "synch.h"
#include "bitmap.h"

#define MAX_LOCK 10

#endif // STABLE_H

class SemList
{
private:
	char name[100];
	Semaphore* sem;
public:
	Sem(char* na, int i)
	{
		strcpy(this->name, na);
		sem = new Semaphore(this->name, i);
	}

	~Sem()
	{
		if(sem)
			delete sem;
	}

	void wait()
	{
		sem->P();
	}

	void signal()
	{
		sem->V();
	}
	
	char* GetName()
	{
		return this->name;
	}
};

class STable
{
private:
	BitMap* bm;
	SemList* semList[MAX_LOCK];
public:
	STable();		

	~STable();

	int Create(char *name, int init);

	int Wait(char *name);

	int Signal(char *name);

	int FindFreeSlot();	
};
