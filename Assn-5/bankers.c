#include <stdio.h>

int main()
{
	
	int pro, res;		// Number of processes and resources

	printf("\n\t\tBANKER'S ALGORITHM\n");

	printf("\n\tEnter the number of processes :");	// Input number of processes
	scanf("%d", &pro);
	printf("\n\tEnter the number of resources :");	// Input number of resources
	scanf("%d", &res);

	
	int alloc[pro][res];		// Allocation Matrix
	int max[pro][res];		// Maximum allocation matrix
	int avail[res];		// Available reources
	int work[res];			// Total resources consumed
	int needMat[pro][res];		// Matrix of total needed resources
	
//============================================== Method generating the safe sequence =======================================//
// THE SAFE ALGORITHM
	
	void safeSequence(int alloc[pro][res], int max[pro][res], int avail[res], int needMat[pro][res])
	{
		
		int include[pro];	// Array to check if the process no. is included in the safe sequence
		int safe[pro];		// Safe Sequence of processes

		for(int i = 0; i < pro; i++)
		{
			include[i] = 0;	// Initialize include array with 0
			safe[i] = 0;		// Initialize safe array with 0
		}
		
		for(int i = 0; i < res; i++)
		{	
			work[i] = avail[i];
		}

		int safeNum = 0;	// Index number of safe sequence array
		int k, i, flag, j, m;

		for(k = 0; k < 3; k++)	// For loop till all the processes are included in the safe sequence
		{
			for(i = 0; i < pro; i++)	// Checking all processes
			{
				if(include[i] == 0)	// If process no. "i" is not included
				{
					flag = 0;	// flag variable for the checking valid needy process
					
					for(j = 0; j < res; j++)	// Checking all resources of all processes
					{
						if(needMat[i][j] > work[j])	// If any needed resource is greater than available resource of that type then cannot included the process
						{
							flag = 1;
							break;
						}
					}
					
					if(flag == 0)	// If the process is a valid needy process
					{
						safe[safeNum] = i;	// Add value of process no. to the safe sequence
						safeNum += 1;		// Increment index of safe sequence
						
						for(m = 0; m < res; m++)
						{
							work[m] += alloc[i][m];	// Increment all available resources with the allocated resources of process no. "i" as that process is already 												included
						}
						
						include[i] = 1;	// Change status of the process no. "i" to included i.e. 1.
					}
				}
			} 
		}

		// Printing All Matrix

		printf("\n\t=================================\n");

		printf("\n\tAllocation Matrix\n\t");

		for(int i = 0; i < pro; i++)
		{
			for(int j = 0; j < res; j++)
			{
				printf("%d\t", alloc[i][j]);

			}
			
			printf("\n\t");
		}

		printf("\n\t=================================\n");
		
		printf("\n\tMAX Matrix\n\t");

		for(int i = 0; i < pro; i++)
		{
			for(int j = 0; j < res; j++)
			{
				printf("%d\t", max[i][j]);

			}
			
			printf("\n\t");
		}
		
		printf("\n\t=================================\n");
		
		printf("\n\tNeed Matrix\n\t");

		for(int i = 0; i < pro; i++)
		{
			for(int j = 0; j < res; j++)
			{
				printf("%d\t", needMat[i][j]);

			}
			
			printf("\n\t");
		}
		
		printf("\n\t=================================\n");
		
		printf("\n\tAvailable Resources\n\t");

		for(int i = 0; i < res; i++)
		{
			printf("%d\t", avail[i]);
		}
		

		// Printing the safe sequence

		printf("\n\n\t=================================\n");
		printf("\n\n\tFollowing is the SAFE Sequence\n\t");
		int x;
		for (x = 0; x < pro - 1; x++)
		{
		 	printf(" P%d ->", safe[x]);   
		}
		printf(" P%d ", safe[x]);
		printf("\n\n\t=================================\n");
		printf("\n");	
		
	}
	
// Method for taking a new allocation and regenerating the safe sequence 

	void newAlloc()
	{
		int num;
		printf("\n\tEnter the process no. :");	// Input a process number for previous processes for new allocation
		scanf("%d", &num);
		
		int request[res];
		printf("\n\tEnter the Allocation Resources for process no. %d", num);	// Input the resources to be newly allocated
		
		for(int i = 0; i < res; i++)
		{
			printf("\n\tEnter resource no. %d :", (i+1));	
			scanf("%d", &request[i]);
		}
		
		
		// Checking conditions for the receiver algorithm
		int flag = 0;
		
		// Is Request(i) < Need(i)
		for(int i = 0; i < res; i++)
		{
			if(needMat[num][i] >= request[i])
				flag = 1;
			else
			{
				flag = 0;
				break;
			}
		}
		
		// Is Request(i) < Available
		if(flag == 1)
		{
			for(int i = 0; i < res; i++)
			{
				if(avail[i] >= request[i])
					flag = 1;
				else
				{
					flag = 0;
					break;
				}
					
			}
		}
		
		// If both the above mentioned conditions are true then -
		if(flag == 1)
		{
			printf("\n\tThe requested resources by process no. %d can be allocated instantly", num);
			printf("\n\tThe safe sequence is changed accordingly\n\n");
			
			// The requested resources are allocated and matrices are changed
			for(int i = 0; i < res; i++)
			{
				avail[i] -= request[i];
				alloc[num][i] += request[i];
				needMat[num][i] -= request[i];
			}
			
			safeSequence(alloc, max, avail, needMat);	// Regenerate the safe sequenceusing new data
		}
		
		if(flag == 0)
		{
			printf("\n\tThe requested resources cannot be allocated to process no. %d\n", num);
		}
		
	}
	
//=======================================================================================================================================//
	
// Input Data

	printf("\n\tEnter values of Allocation Matrix :");

	for(int i = 0; i < pro; i++)
	{
		printf("\n\tEnter the resources for process no. %d : ", (i+1));
		
		for(int j = 0; j < res; j++)
		{
			printf("\n\tEnter the resource no. %d :", (j+1));
			scanf("%d", &alloc[i][j]);
		}
	}
	
	printf("\n\tEnter values of MAX Matrix :");

	for(int i = 0; i < pro; i++)
	{
		printf("\n\tEnter the resources for process no. %d : ", (i+1));
		
		for(int j = 0; j < res; j++)
		{
			printf("\n\tEnter the resource no. %d :", (j+1));
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("\n\tEnter the Initial %d Available Resources :", res);

	for(int i = 0; i < res; i++)
	{
		printf("\n\tEnter value no. %d :", (i+1));
		scanf("%d", &avail[i]);
	}
	
	for(int i = 0; i < pro; i++)
	{
		for(int j = 0; j < res; j++)
			needMat[i][j] = max[i][j] - alloc[i][j];
	}
	
	
	//-----------------------------------------
	
	safeSequence(alloc, max, avail, needMat);
	
	//-----------------------------------------
	
	printf("\n\n\tDo you want to change the allocated resources of an existing process?\n\t1. Yes \n\t2. No \n\tOption = ");
	int option;
	scanf("%d", &option);
	
	if (option == 1)
		newAlloc();
	else
		return 0;
	
	//-----------------------------------------
}


