#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{

	//  Как работает Форк
	printf("Fork-Test1\n");
		pid_t pid;
	if ((pid = fork()) < 0)
		printf("Ошибка форк");	
	else if (pid == 0)
		printf("Fork-Test2 %d\n", (int)pid);
	else
		printf("Родительский\n");


		
	return EXIT_SUCCESS;
}