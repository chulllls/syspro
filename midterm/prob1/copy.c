#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;
    int mode = atoi(argv[1]); 
    
   
    fp1 = fopen(argv[2], "r");
    fp2 = fopen(argv[3], "w");


    while ((c = fgetc(fp1)) != EOF) {
        if (mode == 1) { 
            c = tolower(c);
        } else if (mode == 2) {
            c = toupper(c);
        }
        fputc(c, fp2);
    }
    
    if (fp1 != NULL) fclose(fp1);
    if (fp2 != NULL) fclose(fp2);
    
    return 0;
}
