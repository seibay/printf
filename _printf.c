#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - The printf function
 * @format: a format of type cst pointer to char
 * Return: It returns printed characters
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFF_SIZE)
				print_buffer(buffer, &buffer_index);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
			flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	print_buffer(buffer, &buffer_index);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - if the buffer exists, prints its contents.
 * @buffer: An array of charaters.
 * @buff_ind: The length of the index indicates where to add next character.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}
