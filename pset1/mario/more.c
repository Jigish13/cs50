// Program to print right and left aligned adjacent pyramids of hashes. 
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int i = 1; i <= height; i++)
    {
        for (int spaces = 1; spaces <= height - i; spaces++)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n"); 
    }
}
