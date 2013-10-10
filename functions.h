#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/* your list data structure declarations */

/* your function declarations associated with the list */
int sequential(char *cmd, int mode);


int parallel(char *cmd, int mode);


char *tokenify(const char *str, int switch_value);


int mode_func(const char *command, int mode_type);

#endif // __FUNCTIONS_H__
