/* Copyright (C) 2013 by Casey English */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  /* Make sure an operand was entered */
  if (!argv[1])
    {
      printf("Error: Enter an operand\n");
      exit(EXIT_FAILURE);
    }

  char *input = argv[1];

  /* Make sure only one operand was entered */
  if (argv[2])
    {
      printf("Error: Use only one operand\n");
      exit(EXIT_FAILURE);
    }
  
  /* Make sure the input is an integer */
  int i;
  for (i=0; i < strlen(input); i++)
    {
      if (!isdigit(input[i]))
	{
	  printf("Error: Enter a whole number\n");
	  exit(EXIT_FAILURE);
	}
    }

  /* Convert the input to an int */
  int input_number = atoi(input);
  
  /* Make sure the input isn't out-of-bounds */
  if (input_number <= 0 || input_number >= 4000)
    {
      printf("Error: Enter a number between 1 and 3999\n");
      exit(EXIT_FAILURE);
    }
  
  int ints[] =   {1000, 900,  500, 400,  100,  90,  50,   40,  10,   9,    5,   4,    1};
  char *nums[] = {"M",  "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  char *result = NULL;

  /* Convert the number to roman. */
  for (i=0; i<13; i++)
    {
      int count = input_number/ints[i];
      int j;
      for (j=0; j<count; j++)
	{
	  if (!result)
	    {
	      result = malloc(strlen(nums[i]) + 1);
	      strcpy(result, nums[i]);
	      continue;
	    }
	  strcat(result, nums[i]);
	}
      input_number -= ints[i] * count;
    }

  printf("%s\n", result);

  return 0;
}
