#include <stdio.h>
extern char **environ;

void main(int argc, char *argv[])
{
	char **p; 
	// loop over an array until it is pointing to a null
	for (p = environ; *p != NULL; p++)
		printf("%s\n", *p);

}