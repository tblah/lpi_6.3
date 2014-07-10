#include <string.h> // for strchr, strcmp
#include <stdlib.h> // malloc

extern char **environ;	// defined in the C bootstrap code

char *getKey(char* pair) { // gets the key out of a "KEY=VALUE" pair
	char* equalsAddress = strchr(pair, '=');
	if (equalsAddress == NULL)					// make sure that an equals was found
		return NULL;

	unsigned int numCharichters = (equalsAddress - pair) + 1; // this should be the number of characters (inc NULL) that are needed

	char* newString = (char *)malloc(numCharichters);
	if (newString == NULL)
		return NULL;

	for (unsigned int i = 0; i < numCharichters - 1; i++) {
		newString[i] = pair[i];
	}


	newString[numCharichters - 1] = '\0';

	return newString;
}

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

