#include "minishell.h"

int execute_cmds(t_command *cmd){
    int fds[2];
    // int prev_fd;

    // int pid;
    
    printf("execute\n"); 
    while (cmd) {
        pipe(fds);
        // pid = fork();
        // if (pid = 1) {
            dup2(fds[0], 0);
            printf("while\n");
            printf("arg0 %s\n", cmd->args[0]);
            execve(cmd->path, cmd->args, NULL);
        // }
        // else
        // {
            close(fds[0]);
            // prev_fd = dup(fds[1]);
            close(fds[1]);
        // }
        cmd = cmd->next;
    }
    return 0;
}
