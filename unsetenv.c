#include <string.h> // for strcmp
#include <stdlib.h> // free
#include "getKey.h" // getKey

extern char **environ;	// defined in the C bootstrap code

int unsetenv(const char *name) {
	//printf("Using my unsetenv...\n");
	// walk through environ looking for the name we are deleting
	for (char **ep = environ; *ep != NULL; ep++) {	// environ is a null terminated set of adjacent pointers to "KEY=VALUE" strings
		char* key = getKey(*ep);

		if (strcmp(key, name) == 0)	{ // if this is the environment variable we are interested in
			// delete the key: shifting all the others up
			for (ep = ep; *(ep + 1) != NULL; ep++) {
				*ep = *(ep + 1);
			}
			*ep = NULL;
			free(key);
			break;
		}
		
		free(key);
	}

	return 0;
}

