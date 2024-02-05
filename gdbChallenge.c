#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float frand();

int main(int argc, char** argv)
{
  srand(999);
  int i;
  for(i = 1; i <= 100; i++)
    {
      int value = (int)frand() * 1000000;
      printf("%6d ",value);
      if(i % 20 == 0) printf("\n");
    }
  printf("\n");
  return 0;
}

float frand()
{
  return ((float)rand())/RAND_MAX;
}
