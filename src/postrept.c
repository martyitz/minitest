#include <stdio.h>

int
main(int argc, char** argv, char** envp)
{
  //Routine to burn cpu time and then print a line and then exit

  int	j,k;	/* temp values for loops */
  volatile float	x;	/* temp variable for f.p. calculation */
  long long count = 0;

  for (k= 0; k < 200; k++) {
    x = 0.0;
    for(j=0; j<1000000; j++) {
      x = x + 1.0;
    }
    count++;
  }

  fprintf( stderr, "\n   postrpt completed -- performed %lld while-loop iterations\n\n", count);

  return 0;
}

