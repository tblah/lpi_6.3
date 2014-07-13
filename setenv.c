#include <string.h> // strlen strncpy strcmp strncat
#include "getKey.h" // getKey
#include "unsetenv.h" // unsetenv
#include <stdlib.h> // putenv

extern char **environ;	// defined in the C bootstrap code

int setenv(const char *name, const char *value, int overwrite){
	#define STRING_MAX  100

	if ((strlen(name) > STRING_MAX) || strlen(value) > STRING_MAX)
		return -1;			// we are assuming that the strings wont be longer than STRING_MAX characters.

	// work though environ to see if name already exists
	for (char **ep = environ; *ep != NULL; ep++) {
		char* key = getKey(*ep);

		if (strcmp(key, name) == 0)	{ // are these the droids we are looking for...
			if (overwrite == 0) {	// we are not overwriting so we have nothing to do
				free(key);
				return 0;
			}
			// else we need to get rid of the current version of this key
			if (unsetenv(key) == -1) {
				free(key);
				return -1;
			}
		}
	}

		// add the new env to environ
	static char newString[STRING_MAX + STRING_MAX + 2] = ""; // STRING_MAX for each string plus '=' and '\0'

	strncat(newString, name, STRING_MAX); // copy everything so bad things don't happen if the caller changes the variables
	strncat(newString, "=", 1);
	strncat(newString, value, STRING_MAX);

	if (putenv(newString) != 0)
		return -1;

	return 0;
}