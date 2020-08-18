// Program to implement Caesar cypher algorithm to encrypt messages.
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Encode char by Caesar Algo.
char encrypt(char c, int k);

int main(int argc, string argv[])
{
    // Invalid Key
    if (argc != 2)
    { 
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Invalid Key
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
        { 
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    // Valid Key
    int key = 0;
    for (int i = strlen(argv[1]) - 1, tens = 1; i >= 0; i--)
    {
        key += (argv[1][i] - '0') * tens;
        tens *= 10; 
    }
    
    string plaintext = get_string("plaintext:  ");
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length];
        
    printf("ciphertext: ");  
    for (int i = 0; i < plaintext_length; i++)
    {
        if (islower(plaintext[i]) || isupper(plaintext[i]))
        {
            // Get the encoded character.
            ciphertext[i] = encrypt(plaintext[i], key);       
        }
        else
        {
            ciphertext[i] = plaintext[i];   
        }
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    
    return 0;
}

char encrypt(char c, int k)
{
    if (islower(c))
    {
        return (((c - 'a') + k) % 26) + 'a';  
    }
    return (((c - 'A') + k) % 26) + 'A';
}