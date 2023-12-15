#include "main.h"
/**
 * get_size - Determines the dimension of the argument to be cast.
 * @format: A formatted text to be used when printing the arguments.
 * @i: Arguments listed for printing.
 * Return: The argument's size is returned.
 */
int get_size(const char *format, int *i)
{
	int crnt_idx = *i + 1;
	int size_of = 0;

	if (format[crnt_idx] == 'l')
		size_of = S_LONG;
	else if (format[crnt_idx] == 'h')
		size_of = S_SHORT;
	if (size_of == 0)
		*i = crnt_idx - 1;
	else
		*i = crnt_idx;
	return (size_of);
}
