#include <unistd.h>
#include <fcntl.h>

struct record {
	int id;
	char name;
};

void main()
{
	int fd, size = sizeof(struct record); // set the number of bytes in a record
	struct record info;

	fd = open("datafile", O_RDWR); // open file for reading a writing

	lseek(fd, size, SEEK_SET); // Skip one record
	read(fd, &info, size); // read second record

	info.id = 99; // modify record
	lseek(fd, -size, SEEK_CUR); // Backspace over record that was just read
	write(fd, &info, size); // write a modify record into orginial position

	close(fd);
}

