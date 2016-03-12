#include <stdio.h>

int *getBinary(int n)
{
  int c, k;
  int *output;
  output = (int*)malloc(32 *sizeof(int));
  for (c = 0; c <= 31; c++)
  {
    k = n >> c;
    if (k &1)
    {
      *output = 1;
    }
    else
      *output = 0;
    output++;
  }

  return output - 32;
}

int mainAddBinaries(int argc, char **argv)

{
  int num1, num2;
  printf("enter number1\n");
  scanf("%d", &num1);
  printf("\nenter number1\n");
  scanf("%d", &num2);
  //Convert to binary
  int *A = getBinary(num1);
  int *B = getBinary(num2);

  int C[33] = 
  {
    0
  };

  int i, carry = 0;

  for (i = 0; i < 32; i++)
  {

    if (A[i] + B[i] == 2 && carry == 1)
    {
      C[i] = 1;

      carry = 1;

    }
    else if (A[i] + B[i] == 2 && carry == 0)
    {

      C[i] = 0;

      carry = 1;

    }
    else if (A[i] + B[i] == 0 && carry == 1)
    {

      C[i] = 1;

      carry = 0;

    }
    else if (A[i] + B[i] == 0 && carry == 0)
    {

      C[i] = 0;

      carry = 0;

    }
    else if (A[i] + B[i] == 1 && carry == 1)
    {

      C[i] = 0;

      carry = 1;

    }
    else if (A[i] + B[i] == 1 && carry == 0)
    {
      C[i] = 1;
      carry = 0;
    }
  }

  C[33] = carry;
  printf("answer = ");
  for (i = 33; i >= 0; i--)
  {

    printf("%d", C[i]);
  }

  return 0;
}
