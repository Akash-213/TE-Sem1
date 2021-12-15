#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h> 
#define MAX_BUF 1024

int main(){
	//variables for read,write pipe
    int rd,wd,c=0;
	//variable for receiving data over pipe
    char data[MAX_BUF];

	//variable for sending data over pipe
	char countdata[MAX_BUF];

	//Fifo pipeline for receiving data	
    char *fifo1 = "fifo1";

	//Fifo pipeline for sending data
	char *fifo2 = "fifo2";

	//variable to manage count of data
    int lines=0,chars=0,space=0,words=0;

    // creating a fifo pipeline for receiving data
    mkfifo(fifo1, 0666);
    
    // opening the receiving pipeline in Read mode
    rd=open(fifo1,O_RDONLY);

	//Read data from receiving pipeline
    read(rd,data,sizeof(data));

	//Print data from pipeline
    printf("\nThe data in the file from Pipe 1 is:\n%s",data);
    int i=0;

	//Count the data in file
	while(data[i]!='\0') {
	
		if(data[i]=='\n'){
		 	words++;
            lines++;
		}
		if(data[i] == ' '){
			space++;
		}
		else {
		 	chars++;
		}
		i++;
	}

	//Close receiving pipeline
    close(rd);

	//Open Text File for writing data
	FILE* filewrite = fopen("data.txt", "w+");

	//Write count data to file
    fprintf(filewrite, "Number of Characters : %d\n", chars);
    fprintf(filewrite, "Number of Spaces : %d\n", space);
    fprintf(filewrite, "Number of Words : %d\n", words);
    fprintf(filewrite, "Number of Lines : %d\n", lines);

	//Close Text File
	fclose(filewrite);

	//Open Text File in Read mode
	FILE *fileread = fopen("data.txt", "r");

	//Variable to manage count
    int j = 0;
	char ch=0;
	//Read data from Text File till end of file
    while((ch=fgetc(fileread))!= EOF)
    {
		//Append data in count data variable
        countdata[j] = ch;
        j++;
    }
	//Add null to count data
    countdata[j] = '\0';

	//Close Text File in read mode
    fclose(fileread);

	//Create fifo pipeline for sending data
	mkfifo(fifo2, 0666);

	//Open fifo pipeline in write mode
	wd = open(fifo2,O_WRONLY);

	//Write data from count data in pipe
	write(wd,countdata,sizeof(countdata));

	//Close write pipeline
	close(wd);

	//Unlink Pipe
    unlink(fifo2);

}
