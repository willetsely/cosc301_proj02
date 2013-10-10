#include <stdio.h>
#include <stdlib.h>
#include "tokenify.h"

char *tokenify_prompt(const char *str, int switch_value)
{
    switch (switch_value)
    {
	case 0:				//case 0 - tokenifies prompts by separating every semicolon
	    char *sep = ";";
	    break;
	case 1:				//case 1 - tokenifies commands by separating at any white space
	    char *sep = " \n\t";
	    break;
    char *result = (char *)malloc(sizeof(char *) * strlen(str)); 	//malloc's enough space for an array of pointers the size of the string to be parsed
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
