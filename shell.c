#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_LENGTH_COMMAND 255
#define QTD_COMMAND 20
#define MAX_DIR_NAME 255 
#define SPACE " "

char *current_dir = NULL;


int (*shell_func[]) (char **) = 
{
	&cd_cmd  
};


int cd_cmd(char **args){

	 if(args[1] == NULL){
	 	 printf("expected arguments in cd command");
	 }else{
	 	if(chdir(args[1]) != 0)
	 		printf("Erro in cd\n");
	 }

	 return 1; 
}

int run_process(char **args){ 
    

     int pid = fork();
     int p_status = 0; 
     int wait_pid = 0;
     



     if(pid == 0){
     	
     	 if(execvp(args[0], args) == -1) 
     	 {
     	 	 printf("Error open process\n");  
     	 }

     	exit(EXIT_FAILURE);
     
     }else if(pid < 0){
     	printf("Error in forking"); 
     }else{

            do{
              wait_pid = waitpid(pid , &p_status,  WUNTRACED);    
     	    }while(!WIFEXITED(p_status) && !WIFSIGNALED(p_status));
 	 	
     	 
     }

    return 1; 
}


char ** split_line(char *line){
  
  char **result =  malloc(QTD_COMMAND * sizeof(char *)); 
  char *token   = NULL; 
  int  index    = 0; 
  
  result[index] = strtok(line , SPACE);
  while(1){
   
      if(result[index] == NULL){
      
         result[index++] = NULL;
      	 break;
      }
   
      index++;
      result[index] =  strtok(NULL, SPACE);
      
    

  }
  
  return  result;


}


char *get_line(){


    char *line = malloc(MAX_LENGTH_COMMAND); 
    int index = 0; 

    while(1){
    	 char c = getchar(); 
         
    	 if(c == '\n' || c == EOF)
    	 {
    	 	line[index++] = '\0'; 
      	 	return line; 
  
    	 }

    	 line[index++] = c; 
    }

 
  
}


void shell_loop(){
 
    char *command; 
    char *line = NULL;
    char **spli_line = NULL; 
    command = (char *) malloc(MAX_LENGTH_COMMAND);     
    current_dir =  malloc(MAX_DIR_NAME);
     
	while(1){

	    printf("\033[1;34m");
	    getcwd(current_dir , MAX_DIR_NAME);
	    
	    printf("%s>" , current_dir);
	    printf("\033[0m");

	    line        = get_line();
	    spli_line  =  split_line(line);

            if(strcmp(spli_line[0] , "cd") == 0)
            {
     	        shell_func[0](spli_line);
     	        continue;
            }


          run_process(spli_line);
          free(line); 
          free(spli_line);     
        

    } 
}


int main(int argc , char **argv){
	
	shell_loop();
  


}
