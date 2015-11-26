// learning about time stamps in the file system structure
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

void main()
{
	struct stat sb; // stat buffer

	stat("foo", &sb);

	// ctime returns a printable string
	printf("last accessed: %s", ctime(&sb.st_atime));
	printf("last modified: %s", ctime(&sb.st_mtime));
	printf("last change: %s", ctime(&sb.st_ctime));
}

