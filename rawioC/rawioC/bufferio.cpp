// using fopen and fwrite instead to see difference in kernel and user space

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv)
{
	char *buffer;
	int fd, size, count, i;

	if (argc != 3) {
		printf("usage: %s blocksize blockcount\n", argv[0]);
		exit(1);
	}

	fd = fopen("rawio.out", O_WRONLY | O_CREAT | O_TEMPORARY, 0600);

	size = atio(argv[1]); //size of blocks
	count - atoi(argv[2]); // number of blocks

	buffer = malloc(size);

	// printing out appropiate blocks with correct size
	for (i = 0; i < count; i++)
	{
		fwrite(fd, buffer, size);
	}
	close(fd);
}