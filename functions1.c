#include "main.h"

/**
 * print_unsigned - It is printing an unsigned number.
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: Number of unsigned numbers is being printed.
 */
int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int numb0 = va_arg(types, unsigned long int);

	numb0 = convert_size_unsgnd(numb0, size);
	if (numb0 == 0)
		buffer[idx--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb0 > 0)
	{
		buffer[idx--] = (numb0 % 10) + '0';
		numb0 /= 10;
	}
	idx++;
	return (write_unsgnd(0, idx, buffer, flags, width, precision, size));
}

/**
 * print_octal - It is printing an unsigned number but in octal notation
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: Number of unsigned numbers in octal notation is being printed.
 */
int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int numb0 = va_arg(types, unsigned long int);
	unsigned long int initial_nm = numb0;

	UNUSED(width);
	numb0 = convert_size_unsgnd(numb0, size);
	if (numb0 == 0)
		buffer[idx--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb0 > 0)
	{
		buffer[idx--] = (numb0 % 8) + '0';
		numb0 /= 8;
	}
	if (flags & F_HASH && initial_nm != 0)
		buffer[idx--] = '0';
	idx++;
	return (write_unsgnd(0, idx, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - It is printing an unsigned number
 *			in lower hexdecimal notation
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: Number of unsigned numbers in the hex notation is being printed.
 */
int print_hexadecimal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer, flags,
				'x', width, precision, size));
}

/**
 * print_hexa_upper - It is printing an unsigned number
 *			in upper hexadecimal notation
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: Number of unsigned numbers in upper hex notation is being printed.
 */
int print_hexa_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, flags,
				'X', width, precision, size));
}

/**
 * print_hexa - It is printing an unsigned number in lower or upper
 * @types: a list of the arguments
 * @map_to: Array of values to map the number to
 * @buffer: a buffer array argument used to manage print
 * @flags:  Determines the active flags
 * @flag_ch: determines the active flags.
 * @width: Obtains the width.
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 * @size: Size specification.
 *
 * Return: Number of unsigned numbers in lower or upper is being printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int numb0 = va_arg(types, unsigned long int);
	unsigned long int initial_nm = numb0;

	UNUSED(width);
	numb0 = convert_size_unsgnd(numb0, size);
	if (numb0 == 0)
		buffer[idx--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (numb0 > 0)
	{
		buffer[idx--] = map_to[numb0 % 16];
		numb0 /= 16;
	}
	if (flags & F_HASH && initial_nm != 0)
	{
		buffer[idx--] = flag_ch;
		buffer[idx--] = '0';
	}
	idx++;
	return (write_unsgnd(0, idx, buffer, flags, width, precision, size));
}
