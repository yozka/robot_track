#include "resource.h"

#ifdef NEW
	void * operator new(size_t size)
	{
		return malloc(size);
	}

	void operator delete(void * ptr)
	{
		free(ptr);
	}
#endif



void zeroMemory(BYTE * data, const int length)
{
	for(int i = 0; i < length; i++)
	{
		*data = 0;
		data++;
	}
}