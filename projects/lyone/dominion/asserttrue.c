#include <stdio.h>
#include <stdarg.h>
#include "asserttrue.h"

int asserttrue(int exp1, int exp2, char op, int flag, const char *fmt, ...)
{
	int result;
	switch(op)
	{
		case '<':
			result = ((exp1) < (exp2));
			break;
		case '>':
			result = ((exp1) > (exp2));
			break;
		case '=':
			result = ((exp1) == (exp2));
			break;
		default:
			result = 0;
			break;
	}

	//Print message if required
	if(flag)
	{
		va_list args;
		va_start(args, fmt);

		if(result)
			printf("- Passed. ");
		else
			printf("x Failed. ");

		vprintf(fmt, args);
		va_end(args);
	}

	return result;
}
