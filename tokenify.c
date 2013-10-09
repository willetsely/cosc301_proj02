#include <stdio.h>
#include <stdlib.h>
#include "tokenify.h"

char *tokenify(const char *str, int size, int switch_value)
{
    switch (switch_value)
    {
	case 0:
	    const char *sep = ";"; //switch_value == 0, tokenify separates command line by ';'
	    break;
	case 1:
	    const char *sep = " \n\t"; //switch_value == 1, tokenify breaks up commands by spaces
	    break;
    }
    char *result = (char *)malloc(sizeof(char *) * size); 
    char *s = strdup(str);
    char *word, *temp;
    int i = 0;
    for (word = strtok_r(s, sep, &temp); word != NULL; word = strtok_r(NULL, sep, &temp))
    {
	if (word[0] == '#')
	{
	    result[i] = NULL;
	    return result;
	}
	result[i] = word;
	i++;
    }
    result[i] = NULL;
    free(s);
    return result;
}
