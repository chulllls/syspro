#include <stdio.h>
#include <unistd.h>

 int main()
 {    
     printf("my process num : [%d] \n", getpid());
     printf("my parents's process num : [%d] \n", getppid());
}

