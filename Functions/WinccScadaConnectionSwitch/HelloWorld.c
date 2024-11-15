#include <stdio.h>
#include <string.h>
void main()
{
    char *sMyname, *sNameBuffer = "Kisystem" ;
    char sConstName[100] = "Joongseok" ;
//    strcpy(sMyname,sNameBuffer);
    sMyname = sNameBuffer ;
    printf("Hello World\n");
    printf("Hello %s\n",sMyname);
    return ;
}