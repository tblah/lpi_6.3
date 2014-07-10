#include <stdlib.h>		// for exit
#include "bool.h"
#include "errExit.h"
#include "unsetenv.h"
#include "setenv.h"
#include <stdio.h> 	// for printf

extern char **environ;

void printEnviron(void) {
	char **ep;

	for (ep = environ; *ep != NULL; ep++)
		printf("%s\n", *ep);
}

int main(int argc, char* argv[])
{
	//printEnviron();

	//printf("\n\nUnsetting SHELL...\n\n");
	unsetenv("SHELL");

	//printEnviron();



	return EXIT_SUCCESS;
}
