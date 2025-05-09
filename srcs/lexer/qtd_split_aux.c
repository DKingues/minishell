

#include "minishell.h"

int skip_quotes(char *str, char quote_type)
{
    int i;

    i = 0;
    while (str[i] && str[i] != quote_type)
        i++;
    return (i);
}

int quote_counter(char *str)
{
    int i;
    int counter;
    char temp;

    i = 0;
    counter = 0;
    while (str[i])
    {
        if (str[i] == '\"' || str[i] == '\'' )
        {
            temp = str[i];
            counter++;
            i += skip_quotes(&str[i], temp);
            if (str[i] == temp)
            {
                counter++;
                i++;
            }
        }
        else  
            i++;
    }
    return (counter);
}