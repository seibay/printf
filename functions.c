#include "main.h"

/**
 * print_char - a character is printed
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns hom many characters are being printed
 */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}

/**
 * print_string - a string is printed
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns hom many characters are being printed
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int length_of = 0, ind;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length_of] != '\0')
		length_of++;
	if (precision >= 0 && precision < length_of)
	length_of = precision;
	if (width > length_of)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length_of);
			for (ind = width - length_of; ind > 0; ind--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (ind = width - length_of; ind > 0; ind--)
				write(1, " ", 1);
			write(1, &str[0], length_of);
			return (width);
		}
	}
	return (write(1, str, length_of));
}

/**
 * print_percent - a percent sign is printed
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns hom many characters are being printed
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - an integer is printed
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns hom many characters are being printed
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int ind = BUFF_SIZE - 2;
	int is_neg = 0;
	long int num = va_arg(types, long int);
	unsigned long int number;

	num = convert_size_number(num, size);
	if (num == 0)
		buffer[ind--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	number = (unsigned long int)num;
	if (num < 0)
	{
		number = (unsigned long int)((-1) * num);
		is_neg = 1;
	}
	while (number > 0)
	{
		buffer[ind--] = (number % 10) + '0';
		number /= 10;
	}
	ind++;
	return (write_number(is_neg, ind, buffer, flags, width, precision, size));
}

/**
 * print_binary - an unsigned number is printed
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns hom many characters are being printed
 */
int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, ind, res;
	unsigned int array[32];
	int counter;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	array[0] = n / m;
	for (ind = 1; ind < 32; ind++)
	{
		m /= 2;
		array[ind] = (n / m) % 2;
	}
	for (ind = 0, res = 0, counter = 0; ind < 32; ind++)
	{
		res += array[ind];
		if (res || ind == 31)
		{
			char z = '0' + array[ind];

			write(1, &z, 1);
			counter++;
		}
	}
	return (counter);
}
