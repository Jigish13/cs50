// Program to check whether credit card number is valid or invalid
#include<cs50.h>
#include<stdio.h>

// Function used to find particular digit at particular index from right to left of Card Number
int partDigits(long, int);

int main(void)
{
    // Prompt user to enter credit card number
    long credit_card_number = get_long("Number: ");
    
    // Code to find total digits of Credit Card Number
    long temp = credit_card_number;    
    int total_digits = 0;
    while (temp != 0)
    {
        temp = temp / 10;
        total_digits++;
    }
   
    // Using Luhn's Algorithm
    int sum_of_even_digits = 0, sum_of_odd_digits = 0, total_sum_of_digits = 0; 
    for (int i = 0; i < total_digits; i++)
    {
        if (i % 2 == 0)
        {
            // Odd index starting from last
            int digit = partDigits(credit_card_number, i);
            //printf("\nIteration = %i", i);
            //printf("\nDIGIT = %i", digit);
            sum_of_odd_digits += digit;
            //printf("\nSum of odd digits = %i", sum_of_odd_digits);
        }
        else
        {
            // Even index starting from last
            int digit = partDigits(credit_card_number, i); 
            //printf("\nIteration = %i", i);
            //printf("\nDIGIT = %i", digit);
            digit = digit * 2;
            if (digit >= 10)
            {
                // Part digits from digit and add them
                int x = partDigits(digit, 0);
                //printf("\nIteration = %i  X = %i", i,x);
                int y = partDigits(digit, 1);
                //printf("\nIteration = %i  Y = %i", i,y);
                sum_of_even_digits = sum_of_even_digits + x + y;
            }
            else
            {
                sum_of_even_digits += digit; 
            }
            // printf("\nIteration = %i  Sum of even digits = %i", i,sum_of_even_digits);
        }
    }
    
    total_sum_of_digits =  sum_of_even_digits + sum_of_odd_digits;
    
    //printf("\nTotal Digits = %i Total Sum Of Digits = %i", total_digits,total_sum_of_digits);
    
    if (total_sum_of_digits % 10 == 0)
    {
        if (total_digits == 15)
        {
            int x = partDigits(credit_card_number, 14);
            int y = partDigits(credit_card_number, 13);
            int starting_num = (x * 10) + y;
            if (starting_num == 34 || starting_num == 37) 
            {
                printf("AMEX\n");    
            }   
            else
            {
                printf("INVALID\n");  
            }       
        }
        else if (total_digits == 16)
        {
            if (partDigits(credit_card_number, 15) == 4)
            {
                printf("VISA\n");   
            }
            else
            { 
                int x = partDigits(credit_card_number, 15);
                int y = partDigits(credit_card_number, 14);
                int starting_num = (x * 10) + y;
                if (starting_num == 51 || starting_num == 52 || 
                    starting_num == 53 || starting_num == 54 || starting_num == 55)
                {
                    printf("MASTERCARD\n");   
                }
                else
                {
                    printf("INVALID\n");     
                }         
            }
        }
        else if (total_digits == 13)
        {
            if (partDigits(credit_card_number, 12) == 4)
            {
                printf("VISA\n");   
            }
            else
            {
                printf("INVALID\n");     
            }
        }
        else
        {
            printf("INVALID\n");   
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int partDigits(long num, int tens)
{
    long power = 1; 
    int x = 1;
    while (x <= tens)
    {
        power = power * 10;
        x ++;
    }
    return (num / power) % 10;
}