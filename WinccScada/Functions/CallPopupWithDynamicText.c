void CallPopupWithDynamicText(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName, char* lpszPopupName, char* lpszText, BOOL bMovable)
{
#include "apdefap.h"
//This function provides the correct coordinates to place a non movable (fix) Popup window in a Parent Window.

int n;

int iPictureHeight;
int iPictureWidth;

int iButtonLeft;
int iButtonTop;
int iButtonHeight;
int iButtonWidth;

int iPopupHeight;
int iPopupWidth;

char szBasicPictureName[100];
char szParentPictureWindow[100];
char szHelp[100];
char szText[100];
char szPopupType[100];

float fZoomFactor;

printf("\r\nProjectfunction 'CallPopupWithDynamicText' :\r\n");

//Hiding every active Popup

SetVisible(lpszPictureName, "FixPopup0", FALSE);

fZoomFactor = 1;//(float)(GetTagWord("cluZoomFactor")) / 100;


//Determine wether to activate the movable or the fix popup
if(bMovable)
{
sprintf(szPopupType, "%s", "MovablePopup");
}
else
{
sprintf(szPopupType, "%s", "FixPopup0");
}

//First, an open Popup is placed outside the Windowarea (at x,y = 2000,2000) and de Display property is set to FALSE. 
//This way, any OnOpenPicture script will be executed as the Popup is activated (displayed).
SetLeft(lpszPictureName, szPopupType, 2000); 
SetTop(lpszPictureName, szPopupType, 2000); 
SetPictureName(lpszPictureName, szPopupType, lpszPopupName);
SetVisible(lpszPictureName, szPopupType, TRUE); 
//
strcpy(szBasicPictureName, GetParentPicture(lpszPictureName));
strcpy(szParentPictureWindow, GetParentPictureWindow(lpszPictureName));
iPictureHeight = (int)(GetHeight(szBasicPictureName, szParentPictureWindow) - (29 / fZoomFactor)); 
iPictureWidth = (int)(GetWidth(szBasicPictureName, szParentPictureWindow) - (10 / fZoomFactor));

//Reading the Origin coordinates and Height and Width of the Button pressed
iButtonLeft = GetLeft(lpszPictureName, lpszObjectName);		//X-coordinate of left corner of object
iButtonTop = GetTop(lpszPictureName, lpszObjectName);			//Y-coordinate of left corner of object
iButtonHeight = GetHeight(lpszPictureName, lpszObjectName); 
iButtonWidth = GetWidth(lpszPictureName, lpszObjectName); 
//printf("		Button (%s): %d, %d, %d, %d\r\n",lpszObjectName, iButtonLeft, iButtonTop, iButtonHeight, iButtonWidth);

//Filling the Popup window with the Popup to be called to determine its Height and Width
SetPictureName(lpszPictureName, szPopupType, lpszPopupName);
SetVisible(lpszPictureName, szPopupType, TRUE); 
iPopupHeight = GetHeight(lpszPictureName, szPopupType);		//Height of picture to be displayed
iPopupWidth = GetWidth(lpszPictureName, szPopupType);			//Width of picture to be displayed
//printf("		Popup (%s): %d, %d\r\n",szPopupType, iPopupHeight, iPopupWidth);

//If Popup appears outside the PictureWidth, shift it to fit into the PictureWidth
if ((iButtonLeft + iPopupWidth + (iButtonWidth + 160) / 2) > iPictureWidth)
{
//	printf("		Popup forced inside PictureWidth\r\n");
	iButtonLeft = iPictureWidth - iPopupWidth - (iButtonWidth +160)/2;
}

//If Popup appears outside the PictureHeight, shift it to fit into the PictureHeight
if((iButtonTop + iPopupHeight + iButtonHeight / 2) > iPictureHeight)
{
//	printf("		Popup forced inside PictureHeight\r\n");
	iButtonTop = iPictureHeight - iPopupHeight - iButtonHeight / 2;
}

SetLeft(lpszPictureName, szPopupType, iButtonLeft + (iButtonWidth +160) / 2); 
SetTop(lpszPictureName, szPopupType, iButtonTop + iButtonHeight / 2); 


if (strcmp(lpszText,"")==0)	//If no text is keyed in when calling the function, the ToolTipText will be used instead
{
	sprintf(szText, "%s", GetPropChar(lpszPictureName, lpszObjectName, "ToolTipText"));
}
else
{
	sprintf(szText, "%s", lpszText);
}

//Putting the appropriate text in the Popup window
SetPropChar(lpszPictureName,szPopupType,"CaptionText",szText);
	

printf("Called PopupWindow is : %s\r\n",szText);
//Set_Focus(lpszPictureName, lpszObjectName);
//printf("=The End===========================================================\r\n");
}