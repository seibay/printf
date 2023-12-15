#include "main.h"

/**
 * print_pointer - prints a pointer variable's value.
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns values of the pointer variables.
 */
int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char ext_c = 0, padd_ing = ' ';
	int idx = BUFF_SIZE - 2, lnth = 2, padding_begin = 1; /* length=2, for '0x' */
	unsigned long nm_add;
	char mapp_to[] = "0123456789abcdef";
	void *addrss = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (addrss == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	nm_add = (unsigned long)addrss;
	while (nm_add > 0)
	{
		buffer[idx--] = mapp_to[nm_add % 16];
		nm_add /= 16;
		lnth++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd_ing = '0';
	if (flags & F_PLUS)
		ext_c = '+', lnth++;
	else if (flags & F_SPACE)
		ext_c = ' ', lnth++;
	idx++;
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, idx, lnth, width, flags,
				padd_ing, ext_c, padding_begin));
}

/**
 * print_non_printable - prints non-printable characters' ASCII codes in hexd.
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It returns the ASCII codes of non-printable chars.
 */
int print_non_printable(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int idex = 0, off_set = 0;
	char *str_ing = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str_ing == NULL)
		return (write(1, "(null)", 6));
	while (str_ing[idex] != '\0')
	{
		if (is_printable(str_ing[idex]))
			buffer[idex + off_set] = str_ing[idex];
		else
			off_set += append_hexa_code(str_ing[idex], buffer,
					idex + off_set);
		idex++;
	}
	buffer[idex + off_set] = '\0';
	return (write(1, buffer, idex + off_set));
}

/**
 * print_reverse - Prints the string in reverse.
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It return a reversed string.
 */
int print_reverse(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char *st_ring;
	int ix, cnt = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	st_ring = va_arg(types, char *);
	if (st_ring == NULL)
	{
		UNUSED(precision);
		st_ring = ")Null(";
	}
	for (ix = 0; st_ring[ix]; ix++)
		;
	for (ix = ix - 1; ix >= 0; ix--)
	{
		char ze = st_ring[ix];

		write(1, &ze, 1);
		cnt++;
	}
	return (cnt);
}

/**
 * print_rot13string - Use rotational_13 to print a string.
 * @types: a list of the arguments
 * @buffer: a buffer array argument used to manage print
 * @flags: Determines the active flags
 * @width: obtains the width
 * @precision: the precision's specs
 * @size: The size is specified by using this argument.
 *
 * Return: It return a rotated_13 string.
 */
int print_rot13string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char ex;
	char *st;
	unsigned int ix, je;
	int ct = 0;
	char in_put[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out_put[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	st = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (st == NULL)
		st = "(AHYY)";
	for (ix = 0; st[ix]; ix++)
	{
		for (je = 0; in_put[je]; je++)
		{
			if (in_put[je] == st[ix])
			{
				ex = out_put[je];
				write(1, &ix, 1);
				ct++;
				break;
			}
		}
		if (!in_put[je])
		{
			ex = st[ix];
			write(1, &ex, 1);
			ct++;
		}
	}
	return (ct);
}
