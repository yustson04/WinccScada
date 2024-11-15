#include "apdefap.h"
void CallPopupWithDynamicTextMoreWindow(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName, char* lpszPopupName, char* lpszText)
{

//This function provides the correct coordinates to place a non movable (fix) Popup window in a Parent Window.
#define		POPUP_WINDOW_MAX	9
int n;

int iPictureHeight;
int iPictureWidth;

int iButtonLeft;
int iButtonTop;
int iButtonHeight;
int iButtonWidth;

int iPopupHeight;
int iPopupWidth;

int iLoopCounter;				// Loop Counter


char szBasicPictureName[100];
char szParentPictureWindow[100];
char szHelp[100];
char szText[100];
char szPopupType[100];
char szPopupTypeTemp[10][100];			// Temporary Popup type holder
char* szActivatingPopupPictureName;		// Activating Popup window picture name

float fZoomFactor;

bool window1;
bool window2;
bool window3;
bool window[10];				// Window visable status flag
bool PopupWindowNameComapreFlag;	// Compare Activating Window name to Target Popup Window Name

printf("\r\nProjectfunction 'CallPopupWithDynamicTextMoreWindow' :\r\n");
fZoomFactor = 1;//(float)(GetTagWord("cluZoomFactor")) / 100;


//Get Pop up Window One to Ten Status

for(iLoopCounter = 0 ; iLoopCounter < POPUP_WINDOW_MAX ; iLoopCounter++){
	sprintf(szPopupTypeTemp[iLoopCounter], "%s%d", "FixPopup",iLoopCounter); 
	window[iLoopCounter] = GetVisible(lpszPictureName,szPopupTypeTemp[iLoopCounter]);
}

// Check if target Popup is activated  and if already Activated then return
for(iLoopCounter = 0 ; iLoopCounter < POPUP_WINDOW_MAX ; iLoopCounter++){
	if(window[iLoopCounter]){
		szActivatingPopupPictureName = GetPictureName(lpszPictureName,szPopupTypeTemp[iLoopCounter]);	//Return-Type: char* 
		printf("%s  %s\r\n", szActivatingPopupPictureName,lpszPopupName); 
		PopupWindowNameComapreFlag = strcmp(lpszPopupName,szActivatingPopupPictureName);
		if(!PopupWindowNameComapreFlag){
			return;
		}
		else
			continue ;
	}
}

// Search Unactivated WIndow to Activat it
for(iLoopCounter = 0 ; iLoopCounter < POPUP_WINDOW_MAX ; iLoopCounter++){
	if(!window[iLoopCounter])
	{
		strcpy(szPopupType,szPopupTypeTemp[iLoopCounter]);
		break;
	}
	else
	{
		;
	}
	
}

/*
	window1 = GetVisible(lpszPictureName,"FixPopup");
	window2 = GetVisible(lpszPictureName,"FixPopup2");
	window3 = GetVisible(lpszPictureName,"FixPopup3");


SetVisible(lpszPictureName, "FixPopup", FALSE);
SetVisible(lpszPictureName, "FixPopup1", FALSE);
SetVisible(lpszPictureName, "FixPopup2", FALSE);

//All window is Moveable
	if (!window1) { 
//		SetTagPrefix(lpszPictureName, "FixPopup", Struct);		// open box in Window 1 set instance name for Picture Block
		sprintf(szPopupType, "%s", "FixPopup"); 
		}
	else if (!window2) { 
//		SetTagPrefix(lpszPictureName, "FixPopup2", Struct);		// open box in Window 2 set instance name for Picture Block
		sprintf(szPopupType, "%s", "FixPopup2"); 
		}
	else if (!window3) { 
//		SetTagPrefix(lpszPictureName, "FixPopup3", Struct);		// open box in Window 3 set instance name for Picture Block
		sprintf(szPopupType, "%s", "FixPopup3"); 
		}
	else
		sprintf(szPopupType, "%s", "FixPopup"); 

*/

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
printf("		PIC(%s); %d, %d,%d, %d\r\n", lpszPictureName, iPictureWidth, iPictureHeight,iPopupWidth,iPopupHeight);
printf("		Button (%s): %d, %d, %d, %d\r\n",lpszObjectName, iButtonLeft, iButtonTop, iButtonHeight, iButtonWidth);
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