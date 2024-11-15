#include "apdefap.h"
void SetButtonCounter(char* lpszPictureName, char* lpszObjectName, double step)
{
double fCounter;
fCounter = GetOutputValueDouble(lpszPictureName,lpszObjectName);
printf("¨fCounter = %d", fCounter);
fCounter += step;
if( fCounter <= 0 )	
	fCounter =0;
printf("¨fCounter = %d", fCounter);
SetOutputValueDouble(lpszPictureName,lpszObjectName,fCounter);	//Return-Type: BOOL 
return ;

}
