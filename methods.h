#ifndef MYMETHODS
#define MYMETHODS

char** readIn(int argc, char* argv[], int* size, int sizes[]);

void reverse(char* str);

void write_from_console(char** data, int* size);

void write_from_txt(char** data, int sizes[], int argc, int* size);

#endif