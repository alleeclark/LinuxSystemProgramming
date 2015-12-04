#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>


void listfile(char *name) // file name as an argument
{
	struct stat sb;
	char *modtime;

	// array of file name times
	char *filetype[] = { "?","p", "c", "?", "d", "?", "b", "?", "-", "l", "?", "s" };

	// stat file and test for errors
	if (stat(name, &sb) < 0) {
		perror(name);
		exit(2);
	}

	printf("%s", filetype[(sb.st_atime_mode >> 12) & 017]);

	printf("%C%C%C%C%C%C%C%C%C\n",
		// each character is r w x or a hypen if permission is off
		(sb.st_mode & S_IRUSR) ? 'r' : '_',
		(sb.st_mode & S_IWUSR) ? 'w' : '_',
		(sb.st_mode & S_IXUSR) ? 'x' : '_',
		(sb.st_mode & S_IRGRP) ? 'r' : '_',
		(sb.st_mode & S_IWGRP) ? 'w' : '_',
		(sb.st_mode & S_IXGRP) ? 'x' : '_',
		(sb.st_mode & S_IROTH) ? 'r' : '_',
		(sb.st_mode & S_IWOTH) ? 'w' : '_',
		(sb.st_mode & S_IXOTH) ? 'x' : '_');

	printf("%8ld", sb.st_size);

	modtime = ctime(&sb.st_mtime); // convert mod time to a string
	modtime[strlen(modtime) - 1] = '\0'; //geting rid of the endl it creats when you return
	printf("% s ", modtime);
	printf("s\n", name);

}


int main(int argc, char * argv[])
{
	DIR *d;
	struct dirent * info; // a directory entry

	if (argc != 2)
	{
		fprintf(stderr, "usage: listdir dirname\n");
			exit(1);
	}
	chdir(argv[1]);
	d = opendir(".");

	while((info = readdir(d)) != NULL) {
		listfile(info->d_name);
	}
}

