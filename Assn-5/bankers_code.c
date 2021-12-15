#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>



//Main function
int main() {
	//no of processes variable
	int noOfProcesses;
	//variable to keep store no. of resources
	int noOfResources;
	//accept input
	printf("Enter number of processes: \n");
	scanf("%d",&noOfProcesses);
	printf("Enter number of resources: \n");
	scanf("%d",&noOfResources);
	//int (*arr)[M] = malloc(sizeof(int[N][M]));
	//int maxNeeded[noOfProcesses][noOfResources];
	//int allocated[noOfProcesses][noOfResources];
	int maxNeeded[100][100];
	int allocated[100][100];
	int available[noOfResources];
	//to store available resources at the beginning, so that changes can be reverted easily.
	int originalAvailable[noOfResources];
	//int needMatrix[noOfProcesses][noOfResources];
	int needMatrix[100][100];
	//int completed[noOfProcesses];
	int completed[100];
	//int safeSequence[noOfProcesses];
	//to store sequence
	int safeSequence[100];
	//to keep acccount of last index where sequence is stored. 
	int indexOfSafe=0;
	//array to store resources which are requested by a certain process in resource req algo.
	int resourcesRequested[noOfResources];
	//input all the info to generate all necessary matrices.
	for(int i=0;i<noOfProcesses;i++)
	{
		for(int j=0;j<noOfResources;j++)
		{
			int temp;
			printf("Enter (%d,%d) of maxNeeded matrix \n",i,j);
			scanf("%d",&temp);
			maxNeeded[i][j]=temp;
		}
	}
	printf("The maxNeeded matrix is:- \n");
	for(int i=0;i<noOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<noOfResources;j++)
		{
			printf("%d \t",maxNeeded[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<noOfProcesses;i++)
	{
		for(int j=0;j<noOfResources;j++)
		{
			int temp;
			printf("Enter (%d,%d) of allocated matrix \n",i,j);
			scanf("%d",&temp);
			allocated[i][j]=temp;
		}
	}
	printf("The allocated matrix is:- \n");
	for(int i=0;i<noOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<noOfResources;j++)
		{
			printf("%d \t",allocated[i][j]);
		}
		printf("\n");
	}
	
	for(int i=0;i<noOfResources;i++)
	{
		int temp;
		printf("Enter availiblity of resources %d \n",i+1);
		scanf("%d",&temp);
		available[i]=temp;
		
	}
	for(int i=0;i<noOfResources;i++)
	{
		originalAvailable[i]=available[i];
		
	}
	
	printf("The need matrix is:- \n");
	for(int i=0;i<noOfProcesses;i++)
	{
		completed[i]=0;
		for(int j=0;j<noOfResources;j++)
		{
			needMatrix[i][j]=maxNeeded[i][j]-allocated[i][j];
			printf("%d \t",needMatrix[i][j]);
		}
		printf("\n");
	}
	printf("The completed matrix is:- \n");
	for(int i=0;i<noOfProcesses;i++)
	{	
		printf("%d \t",completed[i]);
		printf("\n");
	}
	
	//calculates safe sequence
	int calculate()
	{
		//initialise completed processes to 0 as at the beginning no process is completed.
		for(int i=0;i<noOfProcesses;i++)
		{	
			completed[i]=0;
		}
		//revert to original status of available resources.
		for(int i=0;i<noOfResources;i++)
		{
			available[i]=originalAvailable[i];
		
		}
		//safe sequence index reset
		indexOfSafe=0;
		
		while(1)
		{	
			int allDone=1;
			//if all processes completed, break from the loop
			for(int i=0;i<noOfProcesses;i++)
			{
				//if even one process is incomplete the flag is unset.
				if(completed[i]==0)
				{
					allDone=0;
				}
			}
			if(allDone==1)
			{
				printf("\nAll done! Safe sequence possible!It is :- \n");
				//display safe sequence
				for(int i=0;i<noOfProcesses;i++)
				{
					//to prevent arrow for last item eg. to avoid 2->3->
					if(i==noOfProcesses-1)
					{
						printf("%d ",safeSequence[i]);
						printf("\n");
					}
					else
					{
						printf("%d -> ",safeSequence[i]);
					}
					
				}
				//break;
				
				return 1;
			}
			//flag to store if any changes take place
			int zeroChanges=1;
			for(int i=0;i<noOfProcesses;i++)
			{
				//if process is not completed
				if(completed[i]==0)
				{
					//flag to check if need of all resources is less than available respectively
					int allNeedsLesser=1;
					for(int j=0;j<noOfResources;j++)
					{
						//if even one need is greater,unset flag.
						if(needMatrix[i][j]>available[j])
						{
							allNeedsLesser=0;
						}
					}
					//if all needs are lesser
					if(allNeedsLesser==1)
					{
						//the allocated resources become available now so add them to that array.
						for(int j=0;j<noOfResources;j++)
						{
							available[j]=available[j]+allocated[i][j];
							
						}
						//as we made a change unset zerochanges flag.
						zeroChanges=0;
						//append process in safe seq array
						safeSequence[indexOfSafe]=i+1;
						//increment index of that array
						indexOfSafe++;
						//mark process as completed.
						completed[i]=1;
					}
						
				}
			}
			//if after complete traversal no change takes place,this means nothing can be done.break.
			if(zeroChanges)
			{
				printf("Safe sequence is not Possible \n");
				//break;
				
				return 0;
			}
			printf("\nThe completed matrix after traversal is:- \n");
			//after each traversal output how many processes were marked completed.
			for(int i=0;i<noOfProcesses;i++)
			{	
				printf("%d \t",completed[i]);
				
			}
			printf("\n");
			
		}
	}
	//call safe seq function
	calculate();
	void resourceRequest()
	{
		  int processNo;
		  printf("\nEnter the process number : ");
		  scanf("%d",&processNo);
		  
		  for(int i=0;i<noOfResources;i++)
		  {
		  	printf("\nEnter the units of resource %d requested : ",i+1);
		  	scanf("%d",&resourcesRequested[i]);
		  }
		  
		  for(int j=0;j<noOfResources;j++)
		  {
		    //check if resources requested do no cross max needed for that process
		    if(resourcesRequested[j]<=originalAvailable[j])  
		    {
			//check if resources requested do no cross available resources
			if(resourcesRequested[j]<=needMatrix[processNo][j])
			{
				originalAvailable[j]=originalAvailable[j]-resourcesRequested[j];
				allocated[processNo][j]=allocated[processNo][j]+resourcesRequested[j];
				needMatrix[processNo][j]=needMatrix[processNo][j]-resourcesRequested[j]; 
			 }
			else
			{
			      printf("\nProcess has exceeded its max limit of resources so request cannot be accepted!");
			      //reset to original state before leaving
			       for(int i=0;i<j;i++)
		  		{
			  		originalAvailable[i]=originalAvailable[i]+resourcesRequested[i];
					allocated[processNo][i]=allocated[processNo][i]-resourcesRequested[i];
					needMatrix[processNo][i]=needMatrix[processNo][i]+resourcesRequested[i]; 
				}
			      return;
			}
		    }
		    else
		    {
		      printf("\nProcess has exceeded available resources so request cannot be accepted!");
		        for(int i=0;i<j;i++)
		  		{
			  		originalAvailable[i]=originalAvailable[i]+resourcesRequested[i];
					allocated[processNo][i]=allocated[processNo][i]-resourcesRequested[i];
					needMatrix[processNo][i]=needMatrix[processNo][i]+resourcesRequested[i]; 
				}
			  return;
		    }
		  }
		int status=calculate();
		if(status==1)
		{
			printf("\nRequest accepted!!\n");
		}
		else
		{
			 for(int j=0;j<noOfResources;j++)
		  	{
		  		originalAvailable[j]=originalAvailable[j]+resourcesRequested[j];
				allocated[processNo][j]=allocated[processNo][j]-resourcesRequested[j];
				needMatrix[processNo][j]=needMatrix[processNo][j]+resourcesRequested[j]; 
			}
		  	
			printf("\nRequest is rejected as safe sequence does not exist!\n");
		}


	}

	while(1)
	{
		//menu driven
		printf("Press 1 to enter new request, press 2 to terminate \n");
		int choice;
		scanf("%d",&choice);
		if(choice==1)
		{
			//call resource req. function.	
			resourceRequest();
	
		}
		else
		{
			break;
		}
	}
	printf("Thank you!! \n");
	return 0;
	
}

