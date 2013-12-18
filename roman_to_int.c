/* Copyright (C) 2013 by Casey English */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define fail -1

int isValueInArray(char val, char *arr, int size)
{
  int i;
  for (i=0; i<size; i++)
    {
      if (arr[i] == val)
	return i;
    }
  return fail;
}

int main(int argc, char *argv[])
{
  /* Make sure there's an input */
  if (argc < 2)
    {
      printf("Error: Enter an operand\n");
      exit(EXIT_FAILURE);
    }

  char *input = argv[1];
  int i;
  for (i=0; i<strlen(input); i++)
    input[i] = toupper(input[i]);

  /* Make sure there's only 1 input */
  if (argc > 2)
    {
      printf("Error: Enter only 1 operand\n");
      exit(EXIT_FAILURE);
    }

  char nums[] = {'M',  'D', 'C', 'L', 'X', 'V', 'I'};
  int ints[] =   {1000,  500, 100, 50,  10,  5,   1};
  int *places = NULL;
  int places_size = 0;
  int value;
  int next_value;

  /* Make sure the input is a valid roman numeral */
  int c;
  for (c=0; c<strlen(input); c++)
    {
      if (isValueInArray(input[c], nums, 7) == fail)
	{
	  printf("Error: Enter a valid roman numeral\n");
	  exit(EXIT_FAILURE);
	}
    }

  for (c=0; c<strlen(input); c++)
    {
      int temp;
      value = ints[isValueInArray(input[c], nums, 7)];

      if (input[c+1])
	{
	  next_value = ints[isValueInArray(input[c+1], nums, 7)];
	  if (next_value > value)
	    value *= -1;
	}

      if (places)
	{
	  int *old_places = (int *)malloc(sizeof(int)*places_size);
	  for (i=0; i<places_size; i++)
	    old_places[i] = places[i];
	  places = (int *)realloc(places, sizeof(int)*(places_size+1));
	  places_size;
	  for (i=0; i<places_size; i++)
	    places[i] = old_places[i];
	  free(old_places);
	}
      else
	places = (int *)malloc(sizeof(int));
      
      places[places_size] = value;
      places_size++;	  
    }

  int sum = 0;
  for (i=0; i<places_size; i++)
    sum += places[i];

  printf("%i\n", sum);

  free(places);

  return 0;

}
