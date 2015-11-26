#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	struct stat sb; // stat buffer

	char *filetype[] = { "unknown","FIFO", "character device", "unkown", "directory",
		"unknown", "block device", "unkown", "file", "unkown", "symlink", "unkown","socket" };
		if (argc != 2) {
			fprintf(stderr, "usage: listefile filename \n");
			exit(1);
		}
		// this time test for errors
	if (stat(argv[1], &sb) < 0) {
		perror(argv[1]);
		exit(2);
	}
	/* print out file type that is encoded in the mode field. shifting 
	by 12 bits mask everything besides last 4 bits. Well get a number between norton 15
	*/
	printf("file type: %s\n", filetype[(sb.st_mode >> 12) & 017]);
	// bulid a string by character
	printf("permissions: %C%C%C%C%C%C%C%C%C\n",
		// each character is r w x or a hypen if permission is off
		(sb.st_mode & S_IRUSR) ? 'r' : '_',
		(sb.st_mode & S_IWUSR) ? 'w' : '_',
		(sb.st_mode & S_IXUSR) ? 'x' : '_',
		(sb.st_mode & S_IRGRP) ? 'r' : '_',
		(sb.st_mode & S_IWGRP) ? 'w' : '_',
		(sb.st_mode & S_IXGRP) ? 'x' : '_',
		(sb.st_mode & S_IROTH) ? 'r' : '_',
		(sb.st_mode & S_IWOTH) ? 'w' : '_',
		(sb.st_mode & S_IXOTH) ? 'x' : '_', );

	printf("last accessed :%s", ctime(&sb.st_atime));
	printf("last modified :%s", ctime(&sb.st_mtime));
	printf("last change :%s", ctime(&sb.st_ctime));
}

