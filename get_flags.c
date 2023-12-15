#include "main.h"
/**
 * get_flags - Determines how many flags are activated.
 * @format: formatted string to be used when printing the arguments
 * @i: heed a parameter.
 *
 * Return: The flags are returned.
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int je, current_idx;
	int flag_s = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_idx = *i + 1; format[current_idx] != '\0';
			current_idx++)
	{
		for (je = 0; FLAGS_CH[je] != '\0'; je++)
			if (format[current_idx] == FLAGS_CH[je])
			{
				flag_s |= FLAGS_ARR[je];
				break;
			}
		if (FLAGS_CH[je] == 0)
			break;
	}
	*i = current_idx - 1;
	return (flag_s);
}
