#ifndef SHELL_H
#define SHELL_H

void   shell_loop(); 
char   *get_line();
char   **split_line(char *line);
int run_process(); 
int cd_cmd(char **args);
#endif 