#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Encrypt each char of plaintext with each char of keyword
char encode_letter(char p, char k);

int main(int argc, string argv[])
{   
    // Invalid Keyword
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    // Length of Keyword
    int key_length = strlen(argv[1]);
    
    // Invalid Keyword
    for (int i = 0; i < key_length; i++)
    {
        if (!(islower(argv[1][i]) || isupper(argv[1][i])))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;   
        }
    }
    
    string plaintext = get_string("plaintext:  ");
    int plaintext_length = strlen(plaintext);
     
    printf("ciphertext: ");
    for (int i = 0, j = 0; i < plaintext_length; i++, j++)
    {
        if (islower(plaintext[i]) || isupper(plaintext[i]))
        {
            if (j == key_length)
            {
                j = 0;
            }    
            printf("%c", encode_letter(plaintext[i], argv[1][j]));
        }
        else
        {
            j--;
            printf("%c", plaintext[i]);    
        }
    }
    printf("\n");
    return 0;
}

char encode_letter(char p, char k)
{
    if (isupper(p))
    {
        return (((p - 'A') + (toupper(k) - 'A')) % 26) + 'A';    
    }
    return (((p - 'a') + (tolower(k) - 'a')) % 26) + 'a'; 
}