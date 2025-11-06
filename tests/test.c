#include <flags.h>
#include <stdio.h>

/*
    Develop into a modular program that can print different flags.
*/

#define X_SIZE 36 // Size of array in X dir
#define Y_SIZE 12 // Size of array in Y dir

char flag[X_SIZE][Y_SIZE];

// Set one bit in a diagonal order of X and Y size
#define SET_BIT(array, bit_index)                                              \
  flag[(array) / 8][bit_index] |=                                              \
      (0x80 >> ((array) % 8)) // Left most to right most 7 -> 1

void print_flag();

int main()
{

  int location;

  print_hello();
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

  // For each y rows (VERTICAL), start at first
  for (y = 0; y < Y_SIZE; y++)
  {

    // For each byte, start at first (HORIZONTAL)
    for (x = 0; x < X_SIZE / 8; x++)
    {

      // Start at MSB (most significant bit) == bit 7
      // If bit is higher than 0 (assign bit the right-shifted bit)
      for (bit = 0x80; bit > 0; bit = (bit >> 1))
      {

        // If a bit is set
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