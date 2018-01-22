#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>



void send_prompt(){

	static int first_time = 1;
	if ( first_time) {
		const char* CLS_ANSI = " \e[1;1H\e[2J";
		write(STDOUT_FILENO, CLS_ANSI,12);
		first_time=0;
	}

	printf("jshell#");
}	

void read_cmd( char cmd[], char *par[]){
	
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;

	for( ;; ){
		int c = fgetc( stdin );
		line[count++]= (char) c;
		if( c == '\n') break;
	}

	if ( count == 1) return;
	pch = strtok(line, " \n");

	while(pch != NULL ){
		array[i++] = strdup( pch );
		pch= strtok(NULL, " \n");
	}

	strcpy( cmd, array[0] );

	for( int j=0; j < i ; j++)
		par[j] = array[j];

	par[i] = NULL;

}

int check_builtins( char cmd[] ){

if(strcmp(cmd," ls")){
	printf("we are here");
	return 1;
}

return 0;

}

int main(){

	char cmd[100], command[100], *parameters[20];

	char *envp[] = { (char *) "PATH=/bin",0};

	while(1){
		send_prompt();
		read_cmd( command, parameters );
	
		if(check_builtins(command))
			continue;		
	
		if( fork() != 0 ){
			wait( NULL );
		}
		else{
			strcpy( cmd,"/bin/");
			strcat( cmd, command);
			execve(cmd, parameters,envp);
		}
	
		if ( strcmp( command, "exit") == 0)
			break;
	}

	return 0;
		

}
