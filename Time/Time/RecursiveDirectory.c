// build histogram of modification hour of files

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

// hour by hour histogram of modification time
int modtimehist[24];
int rflag = 0, aflag = 0;

void processfile(char *name)
{
	struct stat sb;
	struct tm* bdtime;

	printf("processing file %s\n", name);
	if (stat(name, &sb) < 0) {
		perror(name);
		exit(2);
	}
	bdtime = localtime(&sb.st_mtime); 
	// build histogram on times last mod by the hour
	modtimehist[bdtime->tm_hour]++;
}

void processdir(char *dirname)
{
	DIR *d;
	struct dirent *info;
	char fullfilename[_MAX_PATH];
	struct stat sb;

	printf("processing directory %s\n", dirname);
	d = opendir(dirname);
	if (d == NULL) {
		perror(dirname);
		exit(1);
	}

	while ((info = readdir(d)) != NULL) {
		if (info->d_name(0) == '.' !aflag) continue;
		strcpy(fullfilename, dirname);
		strcat(fullfilename, "/");
		strcat(fullfilename, info->d_name);
		// recursive call 
		stat(fullfilename, &sb);
		if(strcmp(info->d_name, ".")
			&& strcmp(info->d_name, "..")
			&& rflag
			&& S_ISDIR(sb.st_mode))
	}
	closedir(d);
}

int main(int argc, char *argv[]) {
	int i, c;
	char dirname[_MAX_PATH];

	for (i = 0; i < 24; i++) modtimehist[i] = 0;

	opterr = 0;

	while ((c = getopt(argc, argv, "ar")) != EOF) {
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case '?':
			fprintf(stderr, "invlaid option: -c%\n, optopt");
		}
	}
	argv += optind;
	argc -= optind;

	if (argc != 1) {
		fprintf(stderr, "usage: modtimehist [-a] [r] dirname\n");
		exit(1);
	}

	// if nott add absolute path
	if (argv[0][0] == '/')
		strcpy(dirname, argv[0], MAX_PATH);
	else {
		strcat(dirname, "/");
		strcat(dirname, argv[0]);
	}
	processdir(dirname);

	// display historgram
	for (i = 0; i < 24; i++)
		printf("hour %2d: count = %6d\n", i, modtimehist[i]);
}