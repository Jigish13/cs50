#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <crypt.h>

const int TOTAL_2D_STRINGS = 2704;

// Set's array of all string's made up of length two.
void set(char a[TOTAL_2D_STRINGS][3]);
bool is_password_correct(string generated_hash_value, string inputed_hash_value);
string generate_hash_value(string pswd, string salt);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Invalid input !!! \n");
        return 1;
    }
    
    // Code to generate string of salt
    char salt[3];   
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }
    salt[2] = '\0';

    // Password check for string of length one.
    for (int i = 0, j = 0; i < 26; i++, j++)
    {
        char s[2];
        s[0] = i + 97;
        s[1] = '\0';
        if (is_password_correct(generate_hash_value(s, salt), argv[1]))
        {
            printf("%s\n", s);
            return 0;
        }   
        
        s[0] = j + 65;
        s[1] = '\0';
        if (is_password_correct(generate_hash_value(s, salt), argv[1]))
        {
            printf("%s\n", s);
            return 0;
        }    
    }
    
    char a[TOTAL_2D_STRINGS][3];
    set(a);
    // Password check for string of length two.
    for (int i = 0; i < TOTAL_2D_STRINGS; i++)
    {
        if (is_password_correct(generate_hash_value(a[i], salt), argv[1]))
        {
            printf("%s\n", a[i]);
            return 0;
        }   
    }
     
    // Password check for string of length three, starting with lowercase 
    char pswd[4];
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        pswd[0] = ch;
        for (int i = 0; i < TOTAL_2D_STRINGS; i++)
        {
            pswd[1] = a[i][0];
            pswd[2] = a[i][1];
            pswd[3] = '\0';
            if (is_password_correct(generate_hash_value(pswd, salt), argv[1]))
            {
                printf("%s\n", pswd);
                return 0;
            }  
        }
    
        // Password check for string of lenght three, starting with uppercase
        pswd[0] = toupper(ch);
        for (int i = 0; i < TOTAL_2D_STRINGS; i++)
        {
            pswd[1] = a[i][0];
            pswd[2] = a[i][1];
            pswd[3] = '\0';
            if (is_password_correct(generate_hash_value(pswd, salt), argv[1]))
            {
                printf("%s\n", pswd);
                return 0;
            }  
        }
    }
    
    // Password check for string of length four.
    char p4[5];
    for (int i = 0; i < TOTAL_2D_STRINGS; i++)
    {
        p4[0] = a[i][0];
        p4[1] = a[i][1];   
        for (int j = 0; j < TOTAL_2D_STRINGS; j++)
        {
            p4[2] = a[j][0];
            p4[3] = a[j][1];
            p4[4] = '\0';
            if (is_password_correct(generate_hash_value(p4, salt), argv[1]))
            {
                printf("%s\n", p4);
                return 0;
            }  
        }
    }
    
    // Password check for string of length five.
    char p5[6];
    for (char c = 'a'; c <= 'z'; c++)
    {
        p5[0] = c;
        for (int i = 0; i < TOTAL_2D_STRINGS; i++)
        {
            p5[1] = a[i][0];
            p5[2] = a[i][1];   
            for (int j = 0; j < TOTAL_2D_STRINGS; j++)
            {
                p5[3] = a[j][0];
                p5[4] = a[j][1];
                p5[5] = '\0';
                if (is_password_correct(generate_hash_value(p5, salt), argv[1]))
                {
                    printf("%s\n", p5);
                    return 0;
                }  
            }
        }    
        
        p5[0] = toupper(c);
        for (int i = 0; i < TOTAL_2D_STRINGS; i++)
        {
            p5[1] = a[i][0];
            p5[2] = a[i][1];   
            for (int j = 0; j < TOTAL_2D_STRINGS; j++)
            {
                p5[3] = a[j][0];
                p5[4] = a[j][1];
                p5[5] = '\0';  
                if (is_password_correct(generate_hash_value(p5, salt), argv[1]))
                {
                    printf("%s\n", p5);
                    return 0;
                }  
            }
        }    
    }
    
    return 0;
}

void set(char a[TOTAL_2D_STRINGS][3])
{
    int index = 0;
    for (char c1 = 'a'; c1 <= 'z'; c1++)
    {
        for (char c2 = 'a'; c2 <= 'z'; c2++)
        {
            a[index][0] = c1;
            a[index][1] = c2;
            index++;
        
            a[index][0] = c1;
            a[index][1] = toupper(c2);
            index++;
            
            a[index][0] = toupper(c1);
            a[index][1] = c2;
            index++;
        
            a[index][0] = toupper(c1);
            a[index][1] = toupper(c2);
            index++;
        }
    }    
}

string generate_hash_value(string pswd, string salt)
{
    return crypt(pswd, salt); 
}

bool is_password_correct(string generated_hash_value, string inputed_hash_value)
{  
    for (int i = 0; i < 13; i++)
    {
        if (generated_hash_value[i] != inputed_hash_value[i])
        {  
            return false;
        }
    }
    return true;
}