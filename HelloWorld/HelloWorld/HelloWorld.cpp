#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void main()
{
	int fd;
	//system call    file write only | create file if doesnt exist, specifies access (rw-r--r--)
	fd = open("foo", O_WRONLY | O_CREAT, 0644);
	write(fd, "hello world", 11);
	if (fd < 0)
	{
		// ernno is only set if an error has occured
		printf("error number &d\n", errno); 
		perror("foo");
		exit(1);
	}
	close(fd);
}

