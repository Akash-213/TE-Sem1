#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <stdbool.h>  
#include <limits.h>

// request structure
struct request{
    int request; //disc request number
    bool complete; // if request completed
} requests[20];


//method to sort the requests in ascending order
void sort(int n){
    int i, j; 
    for (i = 0; i < n-1; i++)      
        for (j = 0; j < n-i-1; j++) 
            if (requests[j].request > requests[j+1].request) {
                struct request temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;  
            }             
}

//method to check if all requests are complete
bool reqComplete(int req){
    for(int i=0;i<req;i++){
        //if single request is false then false
        if(requests[i].complete == false){
            return false;
        }
    }
    return true;
}

//method which return head movements for SSTF scheduling
int scheduleSSTF(int req,int initial,int cylinders){

    //Number of head movements
    int hmov = 0;
    //Current reading location
    int curr = initial;

    //Sequence array for sequence of requests
    int sequence[req];
    //K to access sequence array
    int k=0;
    //Store index of current location
    int index;

    //Run till all requests are complete
    while(!reqComplete(req)){
        int dist = INT_MAX;

        //Check the closest request
        for (int i=0;i<req;i++){
            //If request is closes
            if(abs(curr - requests[i].request)<dist && requests[i].complete==false){
                //update distance
                dist = abs(curr - requests[i].request);               
                //update index                 
                index = i;
            }            
        }

        //change current to new location
        curr = requests[index].request;
        //push current to sequence
        sequence[k] = curr;
        k++;
        //complete request
        requests[index].complete = true;
        //add distance to headmove
        hmov += dist;        
    }

    printf("The sequence is:\n");
    printf("Initial: %d --> ",initial);
    for(int i=0;i<req;i++){
        printf("%d ->",sequence[i]);
    }
    printf("\n");
    return hmov;
}

//method which return head movements for SCAN scheduling
int scheduleScan(int req,int initial,int cylinders){

    //Variable for storing head movements
    int hmov = 0;
    //Sort the array 
    sort(req);

    //Current reading location
    int curr = initial;
    //Sequence array for sequence of requests
    int sequence[req];
    int k=0;

    //Store index of current location
    int index = 0;

    //Reach the initial position in the sorted array
    while(curr>requests[index].request){
        index++;
    }

    int i=0;
    //1. From initial position till end of array
    for(i=index;i<req;i++){
        //Add head movements
        hmov += abs(requests[i].request - curr);
        //Mark request as complete
        requests[i].complete = true;
        //Push request into sequence
        sequence[k] = requests[i].request; 
        k++;
        //Change current location
        curr = requests[i].request; 
    }
    
    //2. Reach the end of the cylinder location
    hmov += abs(cylinders-1 - curr);
    curr = cylinders-1;

    //3. Start from below the initial value to scan for lower values
    for(i=index-1;i>=0;i--){
        //Add head movements
        hmov += abs(requests[i].request - curr);
        //Mark request as complete
        requests[i].complete = true;
        //Push request into sequence
        sequence[k] = requests[i].request; 
        k++;
        curr = requests[i].request; 
    }

    printf("The sequence is:\n");
    printf("Initial: %d --> ",initial);
    for(int i=0;i<k;i++){
        printf("%d ->",sequence[i]);
    }
    printf("\n");
    return hmov;
}

//method which return head movements for CLOOk scheduling
int scheduleCLook(int req,int initial,int cylinders){
    //Variable for storing head movements
    int hmov = 0;
    //Sort the array 
    sort(req);
    int curr = initial;

    //Sequence array for sequence of requests
    int sequence[req];
    int k=0;

    //Store index of current location
    int index = 0;

    //Reach the initial position in the sorted array
    while(curr>requests[index].request){
        index++;
    }
    
    //Run till all requests are complete    
    while(!reqComplete(req)){

        //Add all requests
        hmov += abs(requests[index].request - curr); 
        // Mark requests as complete
        requests[index].complete = true;
        //Push request at the end of array
        sequence[k] = requests[index].request; 
        k++;
        curr = requests[index].request;   
        //Circular increment in sorted array     
        index = (index + 1 ) % req;
    }

    printf("The sequence is:\n");
    printf("Initial: %d --> ",initial);
    for(int i=0;i<req;i++){
        printf("%d ->",sequence[i]);
    }
    printf("\n");    
    return hmov;
}


int main(void){

    int req;
    int initial;  
    int ch=1; 
    int hmov=0; 
    int cylinders;

    //Number of requests
    printf("Enter Number of Requests:");
    scanf("%d",&req);

    printf("Enter Number of Cylinders:");
    scanf("%d",&cylinders);

    //Initial position
    printf("Enter Initial Position of Arm:");
    scanf("%d",&initial);

    //Enter Disk Requests
    printf("Enter Disk Requests:");
      for(int i=0;i<req;i++){
        scanf("%d",&requests[i].request);
        requests[i].complete = false;
    }

    while(ch){
        printf("\n------------------------------\n");
        printf("1. SSTF.\n");
        printf("2. Scan.\n");
        printf("3. C-Look.\n");
        printf("Enter : ");
        scanf("%d",&ch);
        printf("------------------------------\n");
        switch (ch)
        {
        case 1:
            //SSTF
            hmov = scheduleSSTF(req,initial,cylinders);
            printf("Number of head movements: %d",hmov);

            break;
        case 2:
            //Scan
            hmov = scheduleScan(req,initial,cylinders);
            printf("Number of head movements: %d",hmov);
            break;
        case 3:
            //Clook
            hmov = scheduleCLook(req,initial,cylinders);
            printf("Number of head movements: %d",hmov);
            break;
        default:
            break;
        }
    }

    return 0;
}