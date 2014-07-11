#include <string.h> // for strchr
#include <stdlib.h> // malloc

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