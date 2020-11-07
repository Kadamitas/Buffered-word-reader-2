#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


char* gettoken(int fd);
int End_Of_File = 0;
int Buffer_Done = 0;
static char * staticPointer = NULL;

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
           // printf("here");fflush(stdout);
            break; // if this is the last word, it ends the loop
        }
        if(wordcheck != NULL ){
            totalwords++; // if there is a word not consisting of NULL, it counts it
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
    char* buffer = malloc(50 * sizeof(char)); // dynamic buffer for the actual word
    char* unprocessedData = (char*)malloc(100*sizeof(char));
    int Am_I_Done;
    static int k = 0;
    int i = 0;
    i = k;
    
    if(staticPointer == NULL){
        Am_I_Done = read(fd,unprocessedData,100);
        staticPointer = unprocessedData;
        
    }else{
        unprocessedData=staticPointer;
    }
    if(Am_I_Done == 0){
        End_Of_File++;
    }
    int count = 0;
    while(i!=100){
        if(unprocessedData[i] == ' ' || unprocessedData[i] == '\n' || unprocessedData[i] == '\t'){
            while(i<100 && (unprocessedData[i+1] == ' ' || unprocessedData[i+1] == '\n' || unprocessedData[i+1] == '\t')){ // this skips to the end of all the breaks, then restarts the while
                i++;
           }

            //printf("here%i\n",k);fflush(stdout);
            strncat(buffer,unprocessedData+k,i-k); // gets the word between these two place    
            strncat(buffer,"\n",1);
           // printf("here%s\n",buffer);fflush(stdout);
           // printf("here");fflush(stdout);
            k=++i;
            return buffer;
        }
       if(unprocessedData[i] == '\0'){
            i = 100;
            staticPointer = NULL;
            k=i;
           return buffer;
       }
        i++;
    }
    if(i == 100){
        staticPointer = NULL;
        k=0; i= 0;
        return buffer;
    }
    return NULL;
}