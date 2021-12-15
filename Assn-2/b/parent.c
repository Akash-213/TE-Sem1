#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAXSIZE 10

// function to print the intArrayay
void printArray(int intArray[MAXSIZE], int actualSizeOfArray) {
	printf("\n Array is ");
	for (int i=0; i<actualSizeOfArray; i++) 
		printf(" %d ", intArray[i]);
		
}


//quick sort
void quicksort(int intArray[MAXSIZE],int first,int last)
{
    int temp;
    if (first < last) {
    	int pivot = first;
    	int i = first;
    	int j = last;
    	
    	//partioning array into two sides having smaller and greater values than that of pivot
    	while (i < j) {
    		while (intArray[i] <= intArray[pivot] && i < last) 
    			i++;
    		while (intArray[j] > intArray[pivot])
    			j--;
    		
    		if (i < j) {
    			temp = intArray[i];
    			intArray[i] = intArray[j];
    			intArray[j] = temp;
    		}
    	}
    	
    	//positioning pivot in the right position
    	temp = intArray[pivot];
    	intArray[pivot] = intArray[j];
    	intArray[j] = temp;
    	
    	//recursive call for first part
    	quicksort(intArray,first,j-1);
    	//recursive call for second part
    	quicksort(intArray,j+1,last);
    }
}

//main
void main() {
	int intArray[MAXSIZE], actualSizeOfArray;
	pid_t newpid;
	
	printf("\nMain Process is starting...\n ");
	printf("\nProcess ID: %d",getpid());
	printf("\nParent ID: %d",getppid());
	
	printf("\nEnter the size of Array:");
	scanf("%d", &actualSizeOfArray);
	printf("\nEnter the elements:");
	
	//inputting our array from user input
	for (int i = 0; i<actualSizeOfArray; i++) {
		printf("\nElement %d is:", i+1);
		scanf("%d", &intArray[i]);
	}
	
	printArray(intArray, actualSizeOfArray);
	
	printf("\nSorting the array using quick sort... ");
	
	//sorting the array
	quicksort(intArray, 0, actualSizeOfArray-1);
	
	printArray(intArray, actualSizeOfArray);
	
	printf("\nForking the current Process...");
	//forking our process
	newpid = fork();
	
	if (newpid == -1)
		printf("Child was not created");
	//for child
	else if (newpid == 0) {
		printf("\n\n\nI am the child process!");
		printf("\nMy PID is %d", getpid());
		
		int i;
		//buffer to pass to child process
		char *arrayBuffer[actualSizeOfArray+1];//+2 
		arrayBuffer[0] = "./childProcess";
		
		for (i=1; i<actualSizeOfArray+1; i++) {
			arrayBuffer[i] = malloc(7);
			//The snprintf() function formats and stores a series of characters and values in the intArrayay buffer. The snprintf() function with the addition of the n argument, which indicates the maximum number of characters (including at the end of null character) to be written to buffer.
			
			/*int snprintf(char *str, size_t size, const char *format, ...);
				*str : is a buffer.
				size : is the maximum number of bytes
				(characters) that will be written to the buffer.
				format : C string that contains a format
				string that follows the same specifications as format in printf*/

			snprintf(arrayBuffer[i], 7, "%d", intArray[i-1]);
		}
		
		//sizeOfArray+1
		arrayBuffer[i] = NULL;	
		
		//calls the child process
		execv("./childProcess", arrayBuffer);
		
		//never executed because after execv call rewritten and control doesn't come back to parent
		printf("\n\n[MSG] Child process executed sucessfully! \n\n\n");
	}
	//for parent
	else {	
		printf("\nI am the parent process!");
		printf("\n My PID is: %d", getpid());
		printf("\n My Child's PID is: %d", newpid);
		printf("\n------------------Parent is waiting for child to complete------------------");
		//wait(NULL) will block parent process until any of its children has finished. 
		wait(NULL);
		printf("\n\n[MSG] Parent process has executed sucessfully! \n\n\n");
	}	
}
