/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


char* gettoken(int fd);
int EndOfFile = 0;



int main(int argv, char** argc) {
    // declarations + user error
    int opened,totalwords;

    if(argv != 2){
        goto arg_error; // says error if too/little many arg
    }
    opened = open(argc[1],O_RDONLY); //reads first given statement
    if(opened == -1){
        goto no_file_error; //if call fails, you didn't give a valid file
    }


    // meat of program
    totalwords = 0; //word count
    while(1){
        char * wordcheck = gettoken(opened); // this is so I can interpret the given word
        if(wordcheck == NULL){ 
            break; // if this is the last word, it ends the loop
        }
        if(wordcheck != NULL ){
            totalwords++; // if there is a word not consisting of NULL, it counts it
        }
        if(EndOfFile == 1){ // did we reach the end
            break;
        }
        printf("%s",wordcheck);
       
    }
    printf("Words on file: %i \n", totalwords); // prints total words





    // program exits
    return 0;

    arg_error:
    printf("Too many/little arguments given\n");
    return 1;

    no_file_error:
    printf("Given file could not be found\n");
    return 1;

}











char* gettoken(int fd){
    int max =50; // size of buffer you said to use
    char* buffer = (char *)malloc(max*sizeof(char)); // dynamic buffer for read
    char* buffer2 = (char *)malloc(max*sizeof(char)); // dynamic buffer for the actual word
    int count = 0;int maxed;
    while(1){ // runs till return/break
        start:
        maxed = read(fd,buffer,1); // if I read only one char, thisll never need to be resized
       // printf("%c", buffer[0]);fflush(stdout); // error testing
        if(maxed == -1){ // if somehow got a word too big to put in buffer, won't happen 1 at a time
            max+=10;
           buffer = (char*) realloc(buffer,max*sizeof(char));
        }
        if(buffer[0] == ' ' || buffer[0] == '\n' || buffer[0] == '\t'){ // if I see a break, I count a word
            if (count == 0){ // if the first char read is a space, we skip it, so we dont read multiple spaces as words
                while(buffer[count] == ' ' || buffer[count] == '\n' || buffer[count] == '\t'){
                    count++;
                }
                goto start;
            }
            return strncat(buffer2,"\n",1);
        }
        if(maxed == 0){ // this is to make sure that the last word is counted too
            EndOfFile=1;
            return buffer; 
            
        }
        buffer2 = strncat(buffer2, buffer, 1); // library function that dynamically allocates for me
        count++;
    }
    return NULL;
}
*/