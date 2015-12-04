#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>


void main()
{
	DIR *d;
	struct dirent * info; // a directory entry
	struct stat sb; // stat buffer
	long total = 0; // accumulate the total of file size

	d = opendir("."); // opening current directory

	// reading directories to get stat on each file
	while ((info = readdir(d)) != NULL) {
		stat(info->d_name, &sb); // return stats in sb
		total += sb.st_size; //adding size into running total
	}
	closedir(d); // close directory

	printf("total size =%ld\n", total)
}

