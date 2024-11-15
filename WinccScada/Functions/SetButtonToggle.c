#include "apdefap.h"
BOOL SetButtonToggle(char *lpszPictureName,char *lpszObjectName)
{
if (GetBackColor(lpszPictureName,lpszObjectName) == CO_DARK_GRAY)
{
	SetBorderColorTop(lpszPictureName,lpszObjectName,CO_WHITE);
	SetBorderColorBottom(lpszPictureName,lpszObjectName,CO_DARK_GRAY);
	SetForeColor(lpszPictureName,lpszObjectName,CO_BLACK);
	SetBackColor(lpszPictureName,lpszObjectName,CO_LIGHT_GRAY); 
	return(FALSE);  
}
else
{
	SetBorderColorTop(lpszPictureName,lpszObjectName,CO_BLACK);
	SetBorderColorBottom(lpszPictureName,lpszObjectName,CO_WHITE);
	SetForeColor(lpszPictureName,lpszObjectName,CO_WHITE);
	SetBackColor(lpszPictureName,lpszObjectName,CO_DARK_GRAY);   
	return(TRUE);  
}
}