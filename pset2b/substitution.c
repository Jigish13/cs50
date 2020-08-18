// Program to implement Substitution cypher algorithm to encrypt messages.
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void substitute(string plaintext, string key);

int main(int argc, string argv[])
{
    // Invalid Key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int key_length = strlen(argv[1]);

    if (key_length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    // Optimized code to make sure the char's in key appears only once
    int a[26];

    for (int i = 0; i < 26; i++)
    {
        a[i] = 0;
    }

    for (int i = 0; i < 26; i++)
    {
        if (islower(argv[1][i]))
        {
            a[argv[1][i] - 'a'] += 1;
        }
        else
        {
            a[argv[1][i] - 'A'] += 1;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (a[i] != 1)
        {
            printf("Characters in key must be unique.\n");
            return 1;
        }
    }


    string plaintext = get_string("plaintext:  ");
    substitute(plaintext, argv[1]);
}

void substitute(string plaintext, string key)
{
    int plaintext_length = strlen(plaintext);
    char ciphertext[plaintext_length + 1];

    for (int i = 0; i < plaintext_length; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Get the encoded character.
            ciphertext[i] = toupper(key[plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]))
        {
            // Get the encoded character.
            ciphertext[i] = tolower(key[plaintext[i] - 'a']);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[plaintext_length + 1] = '\0';
    printf("ciphertext:  %s\n", ciphertext);
}