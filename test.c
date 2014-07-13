#include <stdlib.h>		// for exit and free
#include "bool.h"
#include "errExit.h"
#include "unsetenv.h"
#include "setenv.h"
#include <stdio.h> 	// for printf
#include <string.h> // strcmp
#include "getKey.h" // getkey

extern char **environ;

void printEnviron(void) {
	char **ep;

	for (ep = environ; *ep != NULL; ep++)
		printf("%s\n", *ep);
}

bool keyExists(char* key) { // linear search
	for (char **ep = environ; *ep != NULL; ep++) {
		char *keyRead = getKey(*ep);
		if (keyRead == NULL)
			errExit("keyExists: getkey");

		if (strcmp(keyRead, key) == 0) {
			free(keyRead);
			return true;
		}

		free(keyRead);
	}

	return false;
}

bool test1(void) {
	// does setenv add something when it does not already exist?
	if (keyExists("foobar") == true) {
		printf("Error in test 1: key 'foobar' already exists\n");
		return false;
	}

	if (setenv("foobar", "blah", 0) == -1) {
		printf("Error in test 1: death of setenv\n");
		return false;
	}

	if (keyExists("foobar") == false) {
		printf("Error in test 1: key 'foobar' was not added\n");
		return false;
	}

	printf("Test 1 \t\t PASS\n");
	return true;
}

int main(int argc, char* argv[])
{
	/*printf("Environ is:\n");
	printEnviron();
	printf("\n\n");*/

	if (test1() == false) {
		printf("Some tests failed");
		return EXIT_FAILURE;
	}
	// else
	printf("All tests passed :-)\n");

	return EXIT_SUCCESS;
}
