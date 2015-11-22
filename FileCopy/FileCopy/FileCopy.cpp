// trivial file copy program using low-level I/0
#include <fcntl.h>
#include <stdlib.h>
#define BSIZE 16384 // defining buffer size

void main()
{
	int fin, fout; // input and output handles
	char buf[BSIZE];
	int count;
	// open input file for reading
	if ((fin = open("foo", O_RDONLY)) < 0) {
		perror("foo");
		exit(1);
	}
	// opening a file for writing and creating if it doesnt exist
	if ((fout = open("bar", O_WRONLY | , 0644)) < 0)
	{
		perror("bar");
		exit(2);
	}
	//reading BSIZE byptes into buffer to see if it is positive
	while ((count = read(fin, buf, BSIZE)) > 0)
		write(fout, buf, count);

	close(fin);
	close(fout);
}

