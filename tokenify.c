#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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
    char *result = 
    char *s = strdup(str);
    char *word, *temp;
    for (word = strtok_r(s, sep, &temp); word != NULL; word = strtok_r(NULL, sep, &temp))
    {
	if (word == '#')
	    return;
	int integer = 1;
	int i = 0;
	int number;
	int number_check = 0;
	while (integer)
	{
	    if ( i == 0 && word[i] == '-')
		i++;
	    if (isdigit(word[i]) == 0)
	        integer = 0;
	    else
	    {
	        i++;
		if (word[i] = '\0')
		{
		    number = atoi(word);
		    number_check = 1;
		    integer = 0;
		}
	    }
	}
	if (number_check == 1) 
	    sorted_insert(number, *head);
    }
    free(s);
    return;
}
