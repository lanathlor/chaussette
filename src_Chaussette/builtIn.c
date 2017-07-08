#include <stdlib.h>
#include <unistd.h>
#include "libmy.h"
#include "lipsite.h"
#include "Chaussette.h"

static int promptStringFd(char **words, int fd)
{
	int inc;

	inc = 1;
	while (words[parseer.words])
	{
		testNULL(words);
		while (words[parseer.words][inc])
		{
			if (words[parseer.words][inc] == 39)
				return (inc - 1);
			else if (words[parseer.words][inc] == 92 && 
				words[parseer.words][inc + 1] == 'n')
			{
				my_putcharfd('\n', fd);
				inc += 2;
			}
			else
			{
				my_putcharfd(words[parseer.words][inc], fd);
				inc++;
			}
		}
		my_putstrfd(" ", fd);
		parseer.words++;
		inc = 0;
	}
	return (FAILURE);
}

static int promptString(char **words)
{
	int inc;

	inc = 1;
	while (words[parseer.words])
	{
		testNULL(words);
		while (words[parseer.words][inc])
		{
			if (words[parseer.words][inc] == 39)
				return (inc - 1);
			else if (words[parseer.words][inc] == 92 && 
				words[parseer.words][inc + 1] == 'n')
			{
				my_putchar('\n');
				inc += 2;
			}
			else
			{
				my_putchar(words[parseer.words][inc]);
				inc++;
			}
		}
		my_putstr(" ");
		parseer.words++;
		inc = 0;
	}
	return (FAILURE);
}

int asciiChaussetteAt(char **split, char **words)
{
	int prompt;
	int fd;

	prompt = 0;
	parseer.words++;
	testNULL(words);
	fd = getVal(words);
	parseer.words++;
	while (words[parseer.words])
	{
		testNULL(words);
		if (words[parseer.words][0] == 39)
			prompt += promptStringFd(words, fd);
		else
		{
			parseer.words--;
			my_putcharfd(getVal(words), fd);
		}
		parseer.words++;
	}
	parseer.check = SUCCESS;
	return (prompt);
}

int writeChaussetteAt(char **split, char **words)
{
	int prompt;
	int fd;

	prompt = 0;
	parseer.words++;
	testNULL(words);
	fd = getVal(words);
	parseer.words++;
	while (words[parseer.words])
	{
		testNULL(words);
		if (words[parseer.words][0] == 39)
			prompt += promptStringFd(words, fd);
		else
		{
			parseer.words--;
			my_putnbrfd(getVal(words), fd);
		}
		parseer.words++;
	}
	parseer.check = SUCCESS;
	return (prompt);
}

int asciiChaussette(char **split, char **words)
{
	int prompt;

	prompt = 0;
	parseer.words++;
	testNULL(words);
	parseer.words++;
	while (words[parseer.words])
	{
		testNULL(words);
		if (words[parseer.words][0] == 39)
			prompt += promptString(words);
		else
		{
			parseer.words--;
			my_putchar(getVal(words));
		}
		parseer.words++;
	}
	parseer.check = SUCCESS;
	return (prompt);
}

int writeChaussette(char **split, char **words)
{
	int prompt;
	int val;

	prompt = 0;
	parseer.words++;
	testNULL(words);
	parseer.words++;
	while (words[parseer.words])
	{
		testNULL(words);
		if (words[parseer.words][0] == 39)
			prompt += promptString(words);
		else
		{
			parseer.words--;
			val = getVal(words);
			my_putnbr(val);
		}
		parseer.words++;
	}
	parseer.check = SUCCESS;
	return (prompt);
}

int returning(char **split, char **words)
{
	int ret;

	ret = 0;
	parseer.words++;
	testNULL(words);
	if (!words[parseer.words + 1])
		perrorPars(words, EMPTY_STR);
	ret = getVal(words);
	while (split[parseer.line])
		parseer.line++;
	parseer.check = SUCCESS;
	return (ret);
}

int readFrom(char **split, char **words)
{
	char letter;
	int ret;

	parseer.words++;
	ret = read(getVal(words), &letter, ONE);
	parseer.check = SUCCESS;
	if (ret == 0)
		return(0);
	return (letter);
}