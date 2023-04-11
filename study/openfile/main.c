#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char filename[] = "example.txt";
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
		printf("Error Number: %d\n",errno);
        printf("Error opening file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    printf("File opened successfully!\n");
    fclose(fp);
    
    return 0;
}