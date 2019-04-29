#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* my_memcpy(void* dest, const void* src, size_t n){
    char* d = (char*)dest;
    const char* s = (const char*)src;
    while(n--){
        *d++ = *s++;
    }
    return dest;
}

void* my_memmove(void* dest, const void* src, size_t n){
    char* d = (char*)dest;
    const char* s = (const char*)src;
    if(s > d){
        while(n--){
            *d++ = *s++;
        }
    }else if(s < d){
        d = d+n-1;
        s = s+n-1;
        while(n--){
            *d-- = *s--;
        }
    }
    return dest;
}

char* my_strcpy(char* dest, const char* src){
    if (src == NULL || dest == NULL)return NULL;
    char* strDest = dest;
    char* strSrc = (char*)src;
    while((*strDest++ = *strSrc++)!='\0');
    return dest;
}

char* my_strcat(char* dest, const char* src){
    if (src == NULL ||dest == NULL)return NULL;
    char* strDest = dest;
    while(*dest != '\0')++dest;
    while((*dest++ = *src++) != '\0');
    return strDest;
}


int main(){
    const char *src = "test";
    char dest1[16];
    char dest2[16];
    
    strcpy(dest1, src);
    strcat(dest1, src);
    //memcpy(dest1, src, strlen(src)+1);
    printf("dest1 is %s\n",dest1);

    my_strcpy(dest2, src);
    my_strcat(dest2, src);
    //my_memcpy(dest2, src, strlen(src)+1);
    printf("dest2 is %s\n",dest2);

    return 0;
}

//g++ -o test main.cpp