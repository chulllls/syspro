#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "사용법: %s -e [환경변수이름] | -u | -g | -i | -p\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            printf("My Process ID : [%d]\n", getpid());
        }
        else if (strcmp(argv[i], "-p") == 0) {
            printf("My Parent Process ID : [%d]\n", getppid());
        }
        else if (strcmp(argv[i], "-u") == 0) {
            uid_t ruid = getuid();
            uid_t euid = geteuid();
            printf("My Realistic User ID : %d(%s)\n", ruid, getpwuid(ruid)->pw_name);
            printf("My Valid User ID : %d(%s)\n", euid, getpwuid(euid)->pw_name);
        }
        else if (strcmp(argv[i], "-g") == 0) {
            gid_t rgid = getgid();
            gid_t egid = getegid();
            printf("My Realistic Group ID : %d(%s)\n", rgid, getgrgid(rgid)->gr_name);
            printf("My Valid Group ID : %d(%s)\n", egid, getgrgid(egid)->gr_name);
        }
        else if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc && argv[i+1][0] != '-') {
                char *env_name = argv[i+1];
                char *env_value = getenv(env_name);
                if (env_value) {
                    printf("%s = %s\n", env_name, env_value);
                } else {
                    printf("%s 환경 변수를 찾을 수 없습니다.\n", env_name);
                }
                i++;
            } else {
                char **ptr;
                for (ptr = environ; *ptr != NULL; ptr++) {
                    printf("%s\n", *ptr);
                }
            }
        }
        else {
            fprintf(stderr, "오류: 알 수 없는 옵션입니다. %s\n", argv[i]);
        }
    }

    return 0;
}
