#include "main.h"

/**
 * get_precision - Determines the precision to be printed.
 * @format: formatted string to be used when printing the arguments
 * @i: heed a parameter.
 * @list: A list that contains the arguments.
 * Return: It returns the printed precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int crnt_ix = *i + 1;
	int preci_sion = -1;

	if (format[crnt_ix] != '.')
		return (preci_sion);
	preci_sion = 0;
	for (crnt_ix += 1; format[crnt_ix] != '\0'; crnt_ix++)
	{
		if (is_digit(format[crnt_ix]))
		{
			preci_sion *= 10;
			preci_sion += format[crnt_ix] - '0';
		}
		else if (format[crnt_ix] == '*')
		{
			crnt_ix++;
			preci_sion = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = crnt_ix - 1;
	return (preci_sion);
}
