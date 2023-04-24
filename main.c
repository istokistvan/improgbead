#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "methods.h"

int main(int argc, char* argv[])
{
    int size = 2;
    int* sizes = (int*)malloc((argc-1)*sizeof(int));
    char** data = readIn(argc, argv, &size, sizes);
    if(argc == 1) {
        write_from_console(data, &size);
    } else {
        write_from_txt(data, sizes, argc, &size);
    }
    free(sizes);

    return 0;
}