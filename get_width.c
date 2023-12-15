#include "main.h"
/**
 * get_width - It determines the width to be printed.
 * @format: A formatted text to be used when printing the arguments.
 * @i: Arguments listed for printing.
 * @list: A list which contains the arguments in it.
 *
 * Return: The argument's width is returned.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (width);
}
