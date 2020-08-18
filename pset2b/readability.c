#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int count_letters(int len, string text);
int count_words(int len, string text);
int count_sentences(int len, string text);

int main(void)
{
    string text = get_string("Text: ");

    int text_length = strlen(text);

    int L = count_letters(text_length, text);
    int W = count_words(text_length, text);
    int S = count_sentences(text_length, text);

    // computing Coleman-Liau index
    int index = round((5.88 * L) / W - (29.6 * S) / W - 15.8);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(int len, string text)
{
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            c++;
        }
    }
    return c;
}

int count_words(int len, string text)
{
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            c++;
        }
    }
    c += 1;
    return c;
}

int count_sentences(int len, string text)
{
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            c++;
        }
    }
    return c;
}