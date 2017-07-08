#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "Chaussette.h"

int plus(int var_left, int var_right)
{
	return (var_left + var_right);
}

int moins(int var_left, int var_right)
{
	return (var_left - var_right);
}

int fois(int var_left, int var_right)
{
	return (var_left * var_right);
}

int divi(int var_left, int var_right)
{
	return (var_left / var_right);
}

int modulo(int var_left, int var_right)
{
	return (var_left % var_right);
}

int minus(int var_left, int var_right)
{
	return (var_left < var_right);
}

int minusequ(int var_left, int var_right)
{
	return (var_left <= var_right);
}

int maxu(int var_left, int var_right)
{
	return (var_left > var_right);
}

int maxuequ(int var_left, int var_right)
{
	return (var_left >= var_right);
}

int equ(int var_left, int var_right)
{
	return (var_left == var_right);
}

int et(int var_left, int var_right)
{
	return (var_left && var_right);
}

int ou(int var_left, int var_right)
{
	return (var_left || var_right);
}

int invert(int var)
{
	return (!var);
}