
// C program to demonstrate use of variable 
// number of arguments. 
#include <stdarg.h> 
#include <stdio.h> 
#include <stdlib.h>
// this function returns minimum of integer 
// numbers passed.  First argument is count 
// of numbers. 
int min(const char *s, ...) 
{ 
    int i; 
    int min, a; 
  
    // va_list is a type to hold information about 
    // variable arguments 
    va_list ap; 
  
    // va_start must be called before accessing 
    // variable argument list 
    va_start(ap, s); 
  
    // Now arguments can be accessed one by one 
    // using va_arg macro. Initialize min as first 
    // argument in list 
  
    // traverse rest of the arguments to find out minimum 
    for (i = 1; i <= 5; i++) 
        printf("%s\n", va_arg(ap, const char *));
  
    // va_end should be executed before the function 
    // returns whenever va_start has been previously 
    // used in that function 
    va_end(ap); 
  
    return 0;
} 

void file(int count, int *arq, ...)  {
    int i;
    va_list ap;
    va_start(ap, arq);
    FILE *arquivo;
    for(i = 0; i<count; i++){
        arquivo = va_arg(ap, FILE*);
        if (arquivo != NULL){
            fprintf(arquivo, "coocococo");
            printf("foi\n");
        }else
        {
            printf("se fufuf\n");
        }   
    }
    char letter;

    printf("%d\n", va_arg(ap, int));
    letter = va_arg(ap, int);
    printf("%c\n", letter);
    va_end(ap);
}

// Driver code 
int main() 
{ 
    char *str = (char*)malloc(sizeof(char)*10), letter = 'd';
    int count = 5, r = 6, g; 
    printf("Minimum value is %d\n", min( str,"co", "as", "cc", "7c", "10")); 
    FILE *arq, *s;
    arq = fopen("testando.txt", "w");
    file(1, &g, arq, r, letter);

    return 0; 
} 
