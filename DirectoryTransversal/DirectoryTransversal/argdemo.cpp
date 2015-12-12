// comand line argument processing using getopt()
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[])
{
	int c;
	int aflag = 0;
	int bflag = 0;
	int numoption = 0; // reord the numeric value
	char txtoption[200] = "default"; // record string value purple

	opterr = 0;

	while ((c = getopt(argc, argv, "abn:t:")) !=EOF) {
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'n':
				numoption = atoi(optarg);
				break;
			case 't':
				strcpy(txtoption, optarg);
				break;
			case '?':
					fprint(stdrr, "invalid option -%c\n", optopt);

		}
	}
	// showing whether a and b options are set
	if (aflag) printf("Option a is set\n");
	if (bflag) printf("Option b is set\n");
	// showing numerical or text options
	printf("Numeric option value is %d\n", numoption);
	printf("Text option value is %d\n", txtoption);

	argv += optind;
	argc -= optind;

	while (argc--)
	{
		// print non option arguments
		printf("arg: %s\n", *argv++);
	}

}