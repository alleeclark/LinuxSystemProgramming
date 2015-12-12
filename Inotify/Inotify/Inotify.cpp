#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/inotify.h>
#include <sys/types.h>

#define BUFSIZE (100* (sizeof(struct inotify_event) + NAME_MAX +1))

void main()
{
	FILE *fconfig; // config file
	FILE *fout;   // outputfile
	char watchname[_MAX_PATH]; // buffer to hold file names
	struct stat_sb; // stat structure
	int notifyfd, watchfd;
	char eventbuf[BUFSIZE]; // buffer to read out events
	int n;

	// hold names of watched files, indexed by the decscriptor
	char watchednames[100][NAME_MAX + 1]; // an array of path names

	notifyfd = inotify_init(); 

	//open config file for reading
	if ((fconfig = fopen("monitor.conf", "r")) == NULL) {
		printf("file does not exist or cannot open\n");
		exit(1);
	}
	// read all watched file names from conifg
	while (fgets(watchname, _MAX_PATH, fconfig) != NULL)
	{
		// get rid of new file
		watchname[strlen(watchname) - 1] = '\0';

		if (stat(watchname, &sb) < 0) {
			printf("file does not exist", watchname);
			continue;
		}
		// test to see if it a rgular file
		if (S_ISREG(sb.st_mode)) { 
			if ((watchfd = inotify_add_watch(notifyfd, watchname, IN_MODIFY | IN_DELETE_SELF)) < 0) {
				printf("error adding watch for  %s\n", watchname);
			}
			else {
				printf("added %s to watch on descriptor %d\n", watchname, watchfd);
				strcpy(watchednames[watchfd], watchname);
			}
		}
		else {
			//probably a directory
			printf("%s is not a regular file, ignored\n", watchname);
		}

	}
	while (1) {
		// read from inotify instance
		n = read(notifyfd, eventbuf, BUFSIZE);

		for (p = eventbuf; p < eventbuf + n;) {
			// cast p to be an inotify event structure
			event = (struct inotify_event *) p;
			p += sizeof(struct inotify_event *) + event->len;
			// display event
			if (event->mask & IN_MODIFY) fprint(fout, "%s was modified\n", watchednames[event->wd]);
			if (event->mask & IN_DELETE_SELF) fprint(fout, "#%s was deleted\n", watchednames[event->wd]);
			fflush(fout);

		}
	}
}

