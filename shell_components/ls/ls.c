#include <dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
	DIR               *dp;
	struct dirent     *dirp;

	if (argc != 2){
		printf("%s\n","usage: ls directory_name");
		exit(1);
	}

	
	/*
          opendir() - http://man7.org/linux/man-pages/man3/opendir.3.html
	*/
	if ((dp = opendir(argv[1])) == NULL){
		printf("can't open %s", argv[1]);
		exit(1);
	}
	

	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	
	exit(0);

}
