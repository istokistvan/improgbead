#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "methods.h"

char** readIn(int argc, char* argv[], int* size, int sizes[]) {
    int guard = 0;
    char** data;
    data = (char**)malloc(*size * sizeof(char*));
    if (data == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    char* buf = (char*)malloc(1024*sizeof(char));
    if(buf == NULL) {
        printf("Memory allocation failed!");
        exit(2);
    }
    
    if (argc == 1) {
        while (fgets(buf,1024,stdin)) {
            buf[strcspn(buf, "\n")] = '\0';
            if(*size == guard+1) {
                (*size)*=2;
                data = (char**)realloc(data, (*size) * sizeof(char*));
            }
            if (data == NULL) {
                printf("Memory allocation failed!");
                exit(3);
            }
            data[guard] = (char*)malloc(strlen(buf) * sizeof(char));
            if (data[guard] == NULL) {
                printf("Memory allocation failed!");
                exit(4);
            }
            strcpy(data[guard], buf);
            guard++;
        }
    } else {
        int tmp;
        for(int i=argc-1; i>=1; i--) {
            tmp = 0;
            FILE* txt;
            txt = fopen(argv[i],"r");
            if(txt == NULL) {
                fprintf(stderr, "File opening unsuccessful!");
            } else {
                while(fgets(buf,1024,txt)) {
                    buf[strcspn(buf, "\r\n")] = '\0';
                    if(*size == guard+1) {
                        (*size)*=2;
                        data = (char**)realloc(data, (*size) * sizeof(char*));
                    }
                    if (data == NULL) {
                        printf("Memory allocation failed!");
                        exit(5);
                    }
                    data[guard] = (char*)malloc((strlen(buf) + 1) * sizeof(char));
                    if (data[guard] == NULL) {
                        printf("Memory allocation failed!");
                        exit(6);
                    }
                    strcpy(data[guard], buf);
                    guard++;
                    tmp++;
                }
            }
            fclose(txt);
            sizes[i-1] = tmp;
        }
    }
    (*size) = guard;
    free(buf);
    return data;
}

void reverse(char* str) {
    int ln = strlen(str);
    for(int i=0; i<ln/2; i++) {
        char temp = str[i];
        str[i] = str[ln-i-1];
        str[ln-i-1] = temp;
    }

    printf("%s\n",str);
}

void write_from_console(char** data, int* size) {
    for(int i=*size-1; i>=0; i--) {
        if(data[i] != NULL) {
            printf("%d ", i+1);
            reverse(data[i]);
            free(data[i]);
        }
    }
    free(data);
}

void write_from_txt(char** data, int sizes[], int argc, int* size) {
    for(int i=1; i<=argc-1; i++) {
        for(int j=sizes[i-1]; j>=1; j--) {
            printf("%d ",j);
            reverse(data[*size-1]);
            free(data[*size-1]);
            (*size)--;
        }
    }
    free(data);
}