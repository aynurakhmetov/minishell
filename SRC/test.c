#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{

	// 1 вариант
	int fd[0];
	char *s, *h;
	size_t size;

	s = malloc(200);
	h = malloc(200);
	s = "h";
	pipe(fd);

	printf("%d %d\n", fd[0], fd[1]);

	size = write(fd[1], s, 3);
	printf("%d\n", (int)size);
	size = read(fd[0], h, 3);
	printf("%d\n", (int)size);

	// 2 вариант
	


	return (0);
}