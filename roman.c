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

int main(int argc, char *argv[])
{
  struct arguments arguments;

  arguments.numeral = 0;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.numeral)
    printf("Roman Numeral: %s", arguments.args[0]);
  else
    printf("Integer: %s", arguments.args[0]);

  return 0;

  
}
