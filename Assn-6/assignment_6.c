#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>  

//method to check if page is present in the frame
bool page_present(int frame[],int fsize, int page){
    for(int i=0;i<fsize;i++){
        //if page is present return true
        if(page==frame[i]){
            return true;
        }
    }
    //else return false
    return false;
}

//method to implement fcfs technique
double FCFS(int page_seq[],int n, int fsize){

    //initialize frame to zero
    int frame[fsize];    
    memset( frame, 0, sizeof(frame) );
    
    //variable to keep track of page numbers
    int i = 0;
    //variable to insert page inside the frame
    int last = 0;

    //number of page faults 
    double pfaults = 0;

    //while page numbers still present
    while(i<n){
        //By default page fault is false 
        bool fault = false;
        printf("Page: %d",page_seq[i]);
        //if page is not present in frame then page fault
        if(!page_present(frame,fsize,page_seq[i])){
            fault = true;
            pfaults++;
            //insert page at the next location in frame 
            frame[last] = page_seq[i];
            last = (last + 1) % fsize;
        }
        i++;        
        printf("\tFrame: ");
        for(int j=0;j<fsize;j++){
            printf("%d ",frame[j]);
        }
        printf("\tPage Fault: ");
        if(fault==true){
            printf("FAULT \n");
        }
        else{
            printf("HIT \n");
        }
        printf("\n");
        printf("-----------------------------------------------------\n");
    }
    return pfaults;
}

// method to predict the optimal insertion point in frame 
int predictOptimal(int page_seq[],int n,int frame[],int fsize, int index){

    //set farthest to index after current index
    int farthest = index;

    //initally result is -1
    int res = -1;

    //for each page in the frame check its occurence in future
    for(int i=0;i<fsize;i++){
        
        int j;
        //check if the page in frame occurs in the page sequence 
        for(j=index;j<n;j++){

            //if page is found in page sequence
            if(frame[i] == page_seq[j])
            {
                //if the page is the farthest then update
                if (j > farthest){
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        //if page not present then return the page 
        if (j == n)
            return i;
    }
    //return the farthest page in the page sequence
    return (res == -1) ? 0 : res;

}

//method to calculate page faults in optimal method
double Optimal(int page_seq[],int n, int fsize){

    //intialize frame size to zero
    int frame[fsize];
    memset( frame, 0, sizeof(frame) );
    int i = 0;

    //set page faults to zero initially
    double pfaults = 0;
    while(i<n){

        //default no page fault
        bool fault = false;
        printf("Page: %d",page_seq[i]);

        //if page is not present then page fault 
        if(!page_present(frame,fsize,page_seq[i])){
            fault = true;
            pfaults++;

            //insert page at the optimal choice
            int j = predictOptimal(page_seq,n,frame,fsize,i+1);            
            frame[j] = page_seq[i];            
        }
        i++;        
        printf("\tFrame: ");
        for(int x=0;x<fsize;x++){
            printf("%d ",frame[x]);
        }
        printf("\tPage Fault: ");
        if(fault==true){
            printf("FAULT \n");
        }
        else{
            printf("HIT \n");
        }
        printf("\n");
        printf("-----------------------------------------------------\n");
    }
    printf("\n");
    return pfaults;
}

//method to predict the Least recently used page
int predictLRU(int page_seq[],int n,int frame[],int fsize, int index){

    //initialize farthest as index
    int farthest = index;
    int res = -1;

    //for each page in the frame check its occurence before
    for(int i=0;i<fsize;i++){

        int j;
        //check if the page in frame occurs in the page sequence 
        for(j=index;j>=0;j--){
            //if page is found in page sequence
            if(frame[i] == page_seq[j])
            {             
                //if the page is the farthest then update
                if (j < farthest){
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        //if page not present then return the page 
        if (j == -1)
            return i;
    }
    //return the farthest page in the page sequence
    return (res == -1) ? 0 : res;
}

//method to calculate page faults in LRU method
double LRU(int page_seq[],int n, int fsize){

    //initialize the frame to zero 
    int frame[fsize];
    memset( frame, 0, sizeof(frame) );
    int i = 0;

    //initialize the page faults to zero 
    double pfaults = 0;
    while(i<n){
        //default no page fault
        bool fault = false;
        printf("Page: %d",page_seq[i]);
         //if page is not present then page fault 
        if(!page_present(frame,fsize,page_seq[i])){
            fault = true;
            pfaults++;
            //insert page at the LRU choice
            int j = predictLRU(page_seq,n,frame,fsize,i-1);            
            frame[j] = page_seq[i];            
        }
        i++;        
        printf("\tFrame: ");
        for(int x=0;x<fsize;x++){
            printf("%d ",frame[x]);
        }
        printf("\tPage Fault: ");
        if(fault==true){
            printf("FAULT \n");
        }
        else{
            printf("HIT \n");
        }
        printf("\n");
        printf("-----------------------------------------------------\n");
    }
    printf("\n");
    return pfaults;
}

int main(){
    int fsize,n;

    //take frame size as input
    printf("Enter Frame size:");
    scanf("%d",&fsize);

    
    int ch=1;

    //take no of pages as input
    printf("Enter no of pages:");
    scanf("%d",&n);

    //page sequence
    int page_seq[n];
    double page_fault;

    printf("Enter page sequence:");
    for(int i=0;i<n;i++){
        scanf("%d",&page_seq[i]);
    }


    while(ch){
        double page_fault = 0;
        printf("\n------------------------------\n");
        printf("1. FCFS.\n");
        printf("2. LRU.\n");
        printf("3. Optimal.\n");
        printf("Enter:");
        scanf("%d",&ch);
        printf("------------------------------\n");
        switch (ch)
        {
        case 1:
            //Case 1 FCFS
            page_fault = FCFS(page_seq,n,fsize);
            printf("\n");
            printf("Page Faults: %.3f\n",page_fault);
            printf("Total: %d\n",n);
            printf("PFR: %.3f\n", page_fault/n);       
            printf("\n"); 
            break;
        case 2:
            // Case 2 LRU
            page_fault = LRU(page_seq,n,fsize);
            printf("Page Faults: %.3f\n",page_fault);
            printf("Total: %d\n",n);
            printf("PFR: %.3f\n", page_fault/n);
            break;
        case 3:

            // Case 3 Optimal
            page_fault = Optimal(page_seq,n,fsize);
            printf("Page Faults: %.3f\n",page_fault);
            printf("Total: %d\n",n);
            printf("PFR: %.3f\n", page_fault/n);
            break;
        default:
            break;
        }
    }
}