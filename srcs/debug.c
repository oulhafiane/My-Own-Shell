#include "shell.h"


void    debug_msg(char *msg, ...)
{
        va_list ap;

        va_start(ap, msg);
        int fd = open(TERM_TTY, O_WRONLY);
        ft_vprintf(fd, msg, &ap);
        va_end(ap);
        close(fd);
}
