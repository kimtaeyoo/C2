#include <stdarg.h>
#include <stdio.h>

//minprintf: minimal printf with variable argument list
void minprintf(char *fmt, ...)
{
	va_list ap; // points to each unnamed arg in turn
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt); // make ap point to 1st unnamed arg
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd': //print type int
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f': //print type double 
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's': //print type char
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap); // clean up when done
}

int main(void)
{
	minprintf("int: %d, double: %f, string: %s\n", 1, 2.2, "Hello");
	
	return 0;
}
