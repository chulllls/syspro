#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int mysystem(const char *cmdstring);

int main()
{
    int status;

    if ((status = system("date")) == -1)
        perror("system() 오류");
    else
        printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("hello")) == -1)
        perror("system() 오류");
    else
        printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("who; exit 44")) == -1)
        perror("system() 오류");
    else
        printf("종료코드 %d\n", WEXITSTATUS(status));

    return 0;
}

int mysystem(const char *cmdstring) {
    int pid, status;

    if (cmdstring == NULL)
        return 1;

    pid = fork();
    if (pid == -1)
        return -1;   // 잘못된 긴 대시 수정

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);  // exec 실패
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR)
                return -1;
        } else {
            return status;
        }
    } while (1);
}

