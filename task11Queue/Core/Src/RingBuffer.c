#include <stdint.h>
#include <stdlib.h>


#define SIZE_OF_RING 20
static uint8_t RingBuffer[SIZE_OF_RING]= {0};
static uint8_t  tail;
static uint8_t  head;

void RingBuffer_Init()
{

  tail = 0;
  head= 0;
  RingBuffer[tail] = 0;
} 


int RingBuffer_IsEmpty()
{
  if(tail == head)
  {
	  return 1;
  }
  return 0;
}

int RingBuffer_IsFull()
{
   if((tail +1) == head )
	 {
	  return 1;
	 }
	  return 0;
}

int RingBuffer_FreeSpace()
{
	uint8_t free;
	if (tail > head)
	{
		free=tail-head;
	}

	else if (tail < head)
	{
	  free= head-tail;
	}

	else if (tail == head)
	{
	  free = SIZE_OF_RING;
	}

	return free;
}


int RingBuffer_Write(uint8_t *data, size_t dataSize)
{
	if (RingBuffer_FreeSpace() >= dataSize)
	{
		int i=0;
		while( i <= dataSize  )
		{
		RingBuffer[tail] = data[i];
		tail +=1 ;
		i +=1 ;
		}
	}

	else if (RingBuffer_FreeSpace()<dataSize)
	{
		return 0;
	}

	return 1;

}

int RingBuffer_Read(uint8_t *data, size_t dataSize)
{
	int full= SIZE_OF_RING- RingBuffer_FreeSpace();
	int i=0;
	while( (i <= dataSize) & (i <=full )  )
	{
		data[i]=RingBuffer[head];
		head +=1 ;
		i +=1 ;
	}
	return 1;

}


