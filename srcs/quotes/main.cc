#include "quote.h"

static void    loop_shell()
{
    char *line;
    t_token_list *list;

    list = NULL;
    while (1)
    {
        line = readline("$> ");
        if (!ft_strcmp(line, "exit"))
        {
            free(line);
            exit(0);
        }
        list = handle_quote(&line);
        free(line);
        print_tokens(list);
        free_token_list(list);
        free(list);
    }
}

int     main()
{
    loop_shell();
    return (0);
}
