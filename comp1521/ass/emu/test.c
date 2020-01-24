#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <spawn.h>
int main(void) {
pid_t pid;
extern char **environ;
while(environ != NULL){
printf("%s\n",environ);
environ++;
}
char *spawn_argv[] = {"/bin/date", "--utc", NULL};
if (posix_spawn(&pid, "/bin/date", NULL, NULL,
spawn_argv, environ) != 0) {
return 1;
}
int exit_status;
if (waitpid(pid, &exit_status, 0) != 0) {
return 1;
}
printf("date exit status was %d\n", exit_status);
}
