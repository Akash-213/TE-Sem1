#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAXSIZE 10

//binary search
void binary_search(int intArray[MAXSIZE], int sizeOfArray, int searchForValue) {
	int first, last, mid;
	
	first = 0;
  	last = sizeOfArray - 1;
  	mid = (first+last)/2;
  	
  	//do till the pointers cross indicating that all values are considered
  	while (first <= last) {
  		//if value is less update the beginning index to mid+1 ,so first half eliminated
    		if (intArray[mid] < searchForValue)
      			first = mid + 1;
      		//if value matches,element is found
    		else if (intArray[mid] == searchForValue) {
      			printf("%d found at location %d.\n", searchForValue, mid+1);
      			break;
    		}
    		//if value is greater,update the ending index to mid-1 ,so latter half eliminated
    		else
      			last = mid - 1;

    		mid = (first + last)/2;
  	}
  	
  	if (first > last)
    		printf("%d not found in the list.\n", searchForValue);
}


// function to print the array
void printArray(int intArray[MAXSIZE], int n) {
	printf("\nSorted Array is:");
	
	for (int i=0; i<n; i++) 
		printf(" %d ", intArray[i]);
		
}

//main

/*argc (ARGument Count) is int and stores number of command-line arguments passed by the user including the name of the program. So if we pass a value to a program, value of argc would be 2 (one for argument and one for program name)
The value of argc should be non negative.*/

//argv(ARGument Vector) is array of character pointers listing all the arguments.

void main(int argc, char* argv[]) {
	
	int intArray[argc-1], searchForValue;
	//to convert from string to integer
	for (int i = 1; i<argc; i++)
		intArray[i-1] = atoi(argv[i]); // The atoi function skips all white-space characters at the beginning of the string, converts the subsequent characters as part of the number, and then stops when it encounters the first character that isn't a number.
		
	printArray(intArray,argc-1);
	
	printf("\nEnter the value to be searched:");
	scanf("%d", &searchForValue);
	
	//to search for inputted value
	binary_search(intArray, argc-1, searchForValue); 
}


