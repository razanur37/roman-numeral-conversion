/* Copyright (C) 2013 by Casey English */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
  /* Make sure there's an input */
  if (!argv[1])
    {
      printf("Error: Enter an operand\n");
      exit(EXIT_FAILURE);
    }

  char *input = argv[1];
  int i;
  for (i=0; i<strlen(input); i++)
    input[i] = toupper(input[i]);

  /* Make sure there's only 1 input */
  if (argv[2])
    {
      printf("Error: Enter only 1 operand\n");
      exit(EXIT_FAILURE);
    }

  char nums[] = {'M',  'D', 'C', 'L', 'X', 'V', 'I'};
  int ints[] =   {1000,  500, 100, 50,  10,  5,   1};

  /* Make sure the input is a valid roman numeral */
  int c;
  for (c=0; c<strlen(input); c++)
    {
      for (i=0; i<7; i++)
	{
	  
	  if (input[c] == nums[i])
	    break;
	  if (i == 6)
	    {
	      printf("Error: Enter a valid roman numeral\n");
	      exit(EXIT_FAILURE);
	    }
	}
    }

  for (c=0; c<strlen(input); i++)
    {
      for

  return 0;

}
