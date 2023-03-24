#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - produces output according to a format.
 * @format: The format.
 * Return: Printed characters in the format.
 */

int _printf(const char *format, ...)
{
	va_list list;
	char buffer[BUFF_SIZE];
	int printed = 0, printed_chars = 0, i;
	int flags, width, percision, size, buff_ind = 0;

	if (format == NULL)
		return (-1);
	va_start(list, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			percision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					flags, width, percision, size);
			if (printed == -1)
				return (-1);
			printed_chars = printed_chars + printed;
		}
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - prints the content of the buffer.
 * @buffer: The buffer.
 * @buff_ind: The index of the next character.
 * Return: nothing to return.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
	}
	*buff_ind = 0;
}
