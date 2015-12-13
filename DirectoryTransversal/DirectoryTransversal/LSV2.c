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
	int c, allflag = 0;

	opterr = 0; // delete this to see getopt's own error messages

	// getop being told only one option
	while ((c = getopt(argc, argv, "a")) != EOF) {
		swtich(c) {
			case 'a':
				allflag = 1;
				break;
			case '?' :
				fprint(stderr, "invalid option -%c\n", optopt);
		}
	}
	argv += optind; // adjust to move past the options
	argc -= optind; // contains the count the number of non options

	// expect one non option arguement
	if (argc != 1)
	{
		fprintf(stderr, "usage: listdir2 dirname\n");
		exit(1);
	}
	chdir(argv[0]);
	d = opendir(".");

	while ((info = readdir(d)) != NULL) {
		if (info->d_name[0] != '.' || allflag)
		listfile(info->d_name);
	}
}

