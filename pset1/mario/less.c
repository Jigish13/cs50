// Program to build right-aligned pyramid 
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    // Prompting the user to enter value between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    // Loop to build pyramid
    for (int i = 1; i <= height; i++)
    {
        // Loop to add whitespaces during each iteration
        for (int spaces = 1; spaces <= height - i; spaces++)
        {
            printf(" ");
        }
        
        // Loop to print '#' during each iteration
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }  
}
