#include "apdefap.h"
void ClickOnReleaseMode(char *lpszPictureName,char *lpszObjectName)
{
	SetBorderColorTop(lpszPictureName,lpszObjectName,CO_WHITE);
	SetBorderColorBottom(lpszPictureName,lpszObjectName,CO_DARK_GRAY);
	SetForeColor(lpszPictureName,lpszObjectName,CO_BLACK);
	SetBackColor(lpszPictureName,lpszObjectName,CO_LIGHT_GRAY); 
}
