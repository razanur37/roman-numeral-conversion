/* Copyright (C) 2013 by Casey English */
/* roman.c - main program for roman <-> integer conversion */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <argp.h>

const char *argp_program_version = "roman 1.0";

const char *argp_program_bug_address = "<kcpisme@gmail.com>";

struct arguments
{
  char *args[1];
  int numeral;
};

static struct argp_option options[] =
{
  {"numeral", 'n', 0, 0, "Convert from a roman numeral to an integer"},
  {0}
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'n':
      arguments->numeral = 1;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
	argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num < 1)
	argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static char args_doc[] = "ARG1";

static char doc[] =
"roman -- Convert an integer to a roman numeral or vice-versa";

static struct argp argp = {options, parse_opt, args_doc, doc};

char* int_to_roman(char *input)
{
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

  return result;
}

#define fail -1

/* Checks if a value is in an array and returns the index to the value, or
   an impossible index if the value is not in the array. */
int placeInArray(char val, char *arr, int size)
{
  int i;
  for (i=0; i<size; i++)
    {
      if (arr[i] == val)
	return i;
    }
  return fail;
}

int roman_to_int(char *input)
{
  int i;
  for (i=0; i<strlen(input); i++)
    input[i] = toupper(input[i]);

  char nums[] = {'M',  'D', 'C', 'L', 'X', 'V', 'I'};
  int ints[] =  {1000,  500, 100, 50,  10,  5,   1};
  int *places = NULL;
  int places_size = 0;
  int value;
  int next_value;

  /* Make sure the input is a valid roman numeral */
  int c;
  for (c=0; c<strlen(input); c++)
    {
      if (placeInArray(input[c], nums, 7) == fail)
	{
	  printf("Error: Enter a valid roman numeral\n");
	  exit(EXIT_FAILURE);
	}
    }
  
  /* For each character in the numeral, find out what value that
     character represents and store that value in an array */
  for (c=0; c<strlen(input); c++)
    {
      int temp;
      value = ints[placeInArray(input[c], nums, 7)];

      /* If there's more to the string, we have to figure out if the
	 current character is 'negative' or not by looking at the next
	 character */
      if (input[c+1])
	{
	  next_value = ints[placeInArray(input[c+1], nums, 7)];
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

  /* Now sum up all the values in the places array to get the final
     value */
  int sum = 0;
  for (i=0; i<places_size; i++)
    sum += places[i];

  /* Easiest way to sanity check */
  char sum_str[5];
  sprintf(sum_str, "%d", sum);
  char *test = int_to_roman(sum_str);
  if(strcmp(test, input) != 0)
    {
      printf("roman: enter a valid roman numeral\n");
      exit(EXIT_FAILURE);
    }

  free(places);
  free(test);

  return sum;
}

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.numeral = 0;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.numeral)
    {
      int result = roman_to_int(arguments.args[0]);
      printf("%i\n", result);
    }
  else
    {
      char *result = int_to_roman(arguments.args[0]);
      printf("%s\n", result);
      free(result);
    }

  return 0;
}
