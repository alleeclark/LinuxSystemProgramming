#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	int fd;
	fd = open("foo", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("error nummber %d\n", errno);
		perror("foo");
		exit(1);
	}
	// this line would fail without error checking because of permissions
	write(fd, "hello world", 11);
	close(fd);
}

