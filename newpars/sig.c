#include "minishell.h"

void ctrl_c(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    printf("\n");
    rl_redisplay();
}

void handle_signals(void)
{
    signal(SIGINT, ctrl_c);
    signal(SIGQUIT, SIG_IGN);
}