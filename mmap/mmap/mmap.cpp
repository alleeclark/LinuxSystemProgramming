// revisiting random access using mmap
//errors  that  need to be fixed
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

struct record {
	int id;
	char name[80];
};
void main()
{
	int fd;
	size_t size;
	struct record *records;

	fd = open("foo", O_RDWR);
	size = lseek(fd, 0, SEEK_END); // get size of file

	records = (struct record *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0); // mapping entire file into memory map points to an array of record structures

	records[1].id = 99; // updating records 

	msync(records, size, MS_SYNC); // syncing the mapping back into the file
}

