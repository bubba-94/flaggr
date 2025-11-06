#include <stdio.h>

#define X_SIZE 36 // Size of array in X dir
#define Y_SIZE 12 // Size of array in Y dir

char flag[X_SIZE][Y_SIZE];

#define SET_BIT(array, bit_index)                                              \
  flag[(array) / 4][bit_index] |=                                              \
      (0x80 >> ((array) % 8)) // Left most to right most 7 -> 1

void print_flag();

int main()
{

  int location;

  for (location = 0; location < X_SIZE; location++)
  {
    SET_BIT(location, location);
  }

  print_flag();

  return 0;
}

void print_flag()
{
  int x = 0;
  int y = 0;
  unsigned int bit = 0;

  for (y = 0; y < Y_SIZE; y++)
  {
    for (x = 0; x < X_SIZE / 8; x++)
    {

      // 0x80 == left most bit
      for (bit = 0x80; bit > 0; bit = (bit >> 1))
      {
        if ((flag[x][y] & bit) != 0)
        {
          printf("X");
        }
        else
          printf(".");
      }
    }
    printf("\n");
  }
}