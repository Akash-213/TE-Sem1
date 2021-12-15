#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_BUF 1024

int main(){
    //variables for read,write pipe
    int rd,wd,c=0;

    //Data to be sent over first pipe
    char data[MAX_BUF];

    //Data to be received over second pipe
    char countdata[MAX_BUF];

    //Fifo pipeline for sending data
    char *fifo1 = "fifo1";
    //Fifo pipeline for receiving data
    char *fifo2 = "fifo2";

    // creating a fifo pipeline
    // 0666 is the permission status
    mkfifo(fifo1, 0666);
    
    // opening the pipeline in Write mode
    wd=open(fifo1,O_WRONLY);

    //Variable to iterate over standard input
    char str;
    printf("Enter a paragraph and press # to end :\n");

    //While standard input is not #
    while ((str=getchar())!= '#' ) {
        //Append characters to data
	    data[c++]=str;  
	}
    data[c]='\0';
    
    // writing data to the pipeline
    write(wd,data,sizeof(data));

    // close the buffer and unlink the pipe
    close(wd);
    unlink(fifo1);

    //Create a fifo pipe for receiving
    mkfifo(fifo2, 0666);

    //Open receiving Pipeline in Read Mode
    rd=open(fifo2,O_RDONLY);

    //Read data from receiving pipeline
    read(rd,countdata,sizeof(countdata));

    //Write contents of the file on standard output
    printf("\n\nThe content of the file from Pipe 2 contains:\n");
    printf("%s",countdata);

    //Close receiving pipeline
    close(rd);

}
