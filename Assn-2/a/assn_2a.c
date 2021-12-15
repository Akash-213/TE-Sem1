#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void quickSort(int [],int ,int );
int partition(int [],int ,int );

void mergeSort(int [],int ,int );
void merge(int [],int ,int ,int ,int );
void main_sort();
void imple_zombie();
void imple_orphan();

int main() {


 int ch;
 printf(" 1)Sorting using wait \n 2)Zombie demonstration \n 3)Orphan demonstration");
 printf("\nEnter your choice : ");
 scanf("%d",&ch);

 switch(ch) {
 
  case 1: main_sort();//using wait
  	  break;
  case 2: imple_zombie();
  	  break;
  case 3: imple_orphan();
  	  break;
  default : printf("Invalid choice");
  }
}


void main_sort(){

 int i,n;
 char buffer[25];
 
 printf("\nEnter the number of elements:");
 scanf("%d",&n);
 int arr[n];

 for(i=0;i<n;i++) {
  scanf("%d",&arr[i]);
 }
 int pid=fork();
 printf("PID after forking : %d",pid);
 // creates 2 process -> parent and child
 // 0 -> create child
 // +ve -> parent process ->id -> pid of child
 // -ve  -> child process unsuccessful 
 
 if(pid==0) {
 
	printf("\n\t This is child process. ");
	printf("\n\t My process id is : %d", getpid());
	printf("\n\t My Parent process id is : %d", getppid());

	// sorting by quick sort
	quickSort(arr,0,n-1);

	//search using grep, ps is used to display pid and process status
	snprintf(buffer,25,"ps -elf | grep %d",getpid());
	system(buffer);
	printf("\nChild execution completed successfully\n");

	printf("\nSorted by Quicksort : -");  
	for(i=0;i<n;i++){
		printf("%d",arr[i]);
	}
	printf("\n\n");
  
 }
 
 else if(pid < 0){
 	// child process unsuccessful
 }
 
 else {
 
	printf("\n\t I am parent, My process id is : %d", getpid());

	// sorting by merge sort
	mergeSort(arr,0,n-1);
	printf("\nSorted by Mergesort : -");
	for(i=0;i<n;i++) {
		printf("%d",arr[i]);
	}
	printf("\n\n");
	wait(NULL);
	printf("\n Child completed its execution, I(parent) can exit\n");
  
 }

}

void quickSort(int arr[],int low,int high) {

 int j;
 if(low<high) {
 
  j=partition(arr,low,high);
  quickSort(arr,low,j-1);
  quickSort(arr,j+1,high);  
 }
}

int partition(int arr[],int low,int high) {

 int i,j,temp,pivot;
 pivot=arr[low];
 i=low;
 j=high+1;
 
 do {
 
  do
   i++;
  while(arr[i]<pivot && i<=high);
  do
   j--;
  while(arr[j]>pivot);

  if(i<j) {
   temp=arr[i];
   arr[i]=arr[j];
   arr[j]=temp;  
  }
 }
 while(i<j);
 
 arr[low]=arr[j];
 arr[j]=pivot;
 
 return(j);
}

void mergeSort(int arr[],int low,int high) {

 int mid;
 if(low<high) {
 
  mid=(low+high)/2;
  mergeSort(arr,low,mid);
  mergeSort(arr,mid+1,high);
  merge(arr,low,mid,mid+1,high);
 }
 
}

void merge(int arr[],int i1,int j1,int i2,int j2) {

 int temp[50];
 int i,j,k;
 i=i1;
 j=i2;
 k=0;

 while(i<=j1 && j<=j2)
 {
  if(arr[i]<arr[j])
   temp[k++]=arr[i++];
  else
   temp[k++]=arr[j++];
 } 
 while(i<=j1)
  temp[k++]=arr[i++];
 while(j<=j2)
  temp[k++]=arr[j++];
 
 for(i=i1,j=0;i<=j2;i++,j++)
  arr[i]=temp[j];
}

void imple_zombie(){

	int i,n;
	char buffer[25];

	printf("\nEnter the number of elements:");
	scanf("%d",&n);
	int arr[n];

	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	int pid=fork();
	printf("PID after forking : %d",pid);

	if(pid==0){
	
		printf("\n\nChild process!");
		printf("\nMy id is %d", getpid());	
			
		printf("\nSorted Array using quick sort:- ");
		quickSort(arr,0,n-1);
		for(i=0;i<n;i++)
		{
            printf("%d",arr[i]);
        }
                
		//search using grep, ps is used to display pid and process status
		snprintf(buffer,25,"ps -elf | grep %d",getpid());
		system(buffer);
		printf("\nChild executed successfully");
		printf("\nChild is now in zombie state\n\n");
		exit(0);
				
	}
	else {
	
		sleep(10);
		printf("\n\nParent process!");
		printf("\nMy id is %d", getpid());
		printf("\nSorted Array using merge sort:- ");
		mergeSort(arr,0,n-1);
		for(i=0;i<n;i++)
		{
            printf("%d",arr[i]);
        }
		//search using grep, ps is used to display pid and process status
		snprintf(buffer,25,"ps -elf | grep %d",getpid());
		system(buffer);
		printf("\n\nParent executed successfully\n");
		system("ps -l");
				
	}
}

void imple_orphan(){

 int i,n;
 char buffer[25];

 printf("\nEnter the number of elements:");
 scanf("%d",&n);
 int arr[n];

 for(i=0;i<n;i++){
  scanf("%d",&arr[i]);
 }
	int pid=fork();
	if(pid==0) {
				
		printf("\n\nChild process!");
		printf("\nMy id is %d", getpid());
		printf("\nMy parent before sleep() is %d", getppid());
		printf("\nSorted Array using quick sort:- ");
		quickSort(arr,0,n-1);
		for(i=0;i<n;i++)
		{
	       printf("%d",arr[i]);
        }
		sleep(10);
		printf("\nMy parent after sleep() is %d", getppid());	
		
		//search using grep, ps is used to display pid and process status
		snprintf(buffer,25,"ps -elf | grep %d",getpid());
		system(buffer);
		printf("\nChild executed successfully");
	}
	
	else {
	
		printf("\n\nParent process!");
		printf("\nMy id is %d", getpid());
		printf("\nSorted Array using merge sort:-  ");
		mergeSort(arr,0,n-1);
		for(i=0;i<n;i++)
		{
			printf("%d",arr[i]);
        	}
		printf("\n\n");
		printf("\nParent executed successfully");
		printf("\nParent died, child is now orphan \n");			
		exit(0);
	}
	
}
