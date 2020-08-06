// Program to implement Greedy Algorithm 
#include<cs50.h>
#include<stdio.h>
#include<math.h>

int main(void)
{
    float dollars;
    int min_no_of_coins = 0, quarter = 25, dime = 10, nickel = 5, penny = 1;
    
    // Prompting the user to enter the change owed in dollars.
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    
    // Converting the entered dollars to cents
    int cents = round(dollars * 100);  
    
    while (cents != 0)
    {
        if (quarter <= cents)
        {
            if (cents % quarter == 0)
            {
                min_no_of_coins = min_no_of_coins + (cents / quarter);
                cents = cents % quarter;  
            }
            else
            {
                min_no_of_coins = min_no_of_coins + (cents / quarter);
                cents = cents % quarter;
                //min_no_of_coins++;  
            }
        }
        
        else if (dime <= cents)
        {
            if (cents % dime == 0)
            {
                min_no_of_coins = min_no_of_coins + (cents / dime);
                cents = cents % dime;  
            }
            else
            {
                min_no_of_coins = min_no_of_coins + (cents / dime);
                cents = cents % dime;           
            }
        }
        
        else if (nickel <= cents)
        {
            if (cents % nickel == 0)
            {
                min_no_of_coins = min_no_of_coins + (cents / nickel);
                cents = cents % nickel;  
            }
            else
            {
                min_no_of_coins = min_no_of_coins + (cents / nickel);
                cents = cents % nickel;
            }
        }
        
        else 
        {
            if (cents % penny == 0)
            {
                min_no_of_coins = min_no_of_coins + (cents / penny);
                cents = cents % penny;
            }
            else
            {
                min_no_of_coins = min_no_of_coins + (cents / penny);
                cents = cents % penny;   
            }
        }
    }
    printf("%i\n", min_no_of_coins);
}
