#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define NUM_THREADS 2		// Num Threads is 2

#define BSIZE 10		// Buffer size is 10
#define NUM_ITEMS 10		// Num Items to produce or consume

int buf[BSIZE];
int NextIn=0, NextOut=0;


void * producer(void *);	// function for producer thread
void * consumer(void *);	// function for consumer thread

pthread_t tid[NUM_THREADS];      // array of thread IDs
int seed = 1000;


int main( int argc, char *argv[] ) 
{
	int temp = pthread_self();
	srand(time(NULL) % temp);


	cout << "      " << "Main Program Creating Threads" << endl;
	cout << "-------------------------------------------------------" << endl;
	
	// Create threads
	pthread_create(&tid[0], NULL, producer, NULL);
	pthread_create(&tid[1], NULL, consumer, NULL);
	
	//join threads
	pthread_join(tid[0], NULL);
	sleep(3);
	pthread_join(tid[1], NULL);

	
		

	cout << "---------------main end------------------" << endl;
	return 0; 

}  /* end main */

  

void * producer(void * parm)
{
	int num;

	cout << "+++++++ Produced Started ++++++" << endl;

	for (int i=0; i<NUM_ITEMS; i++) 
	{	

		num = rand() % 1000;
		// produce item 
		buf[i] = num;

		// place item in the buffer

		cout << "produced item:" << " " << buf[i] << endl;
	}
	
	cout << "++++ Producer Exiting ++++" << endl;
	pthread_exit(0);
}    

void * consumer(void * parm)
{
	int num;
	int min = 1000;
	int max = -1;
	int average;
	int sum;

	cout << "---- Consumer Started -----" << endl;
	sleep(2);
        for (int i=0; i<NUM_ITEMS; i++)
        {
                // fetch an item from the buffer
	
		num = buf[i];
		
		cout << "consuming item:" << " " <<  num << endl;
		
		sum += num;
		if(num < min)
		{
			min = num;
		}
		if(num > max)
		{
			max = num;
		}

	}
	average = sum/NUM_ITEMS;
	
	
	cout << "---- Consumer exiting ----" << endl;
	cout << "MIN NUMBER:" << " " << min << endl;
	cout << "MAX NUMBER:" << " " << max << endl;
	cout << "AVERAGE:" << " " << average << endl;
	pthread_exit(0);
}
