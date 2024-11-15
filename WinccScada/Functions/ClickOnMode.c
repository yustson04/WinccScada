#include "apdefap.h"
void ClickOnMode(char *lpszPictureName,char *lpszObjectName)
{
	SetBorderColorTop(lpszPictureName,lpszObjectName,CO_BLACK);
	SetBorderColorBottom(lpszPictureName,lpszObjectName,CO_WHITE);
	SetForeColor(lpszPictureName,lpszObjectName,CO_WHITE);
	SetBackColor(lpszPictureName,lpszObjectName,CO_DARK_GRAY); 
}
