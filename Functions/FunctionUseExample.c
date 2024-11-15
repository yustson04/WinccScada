//Call Popup with mouse click
//Popup Window File Object name ="Fixpopup0"
#include "apdefap.h"
void OnClick(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName)
{
/// WINCC:PICNAME_SECTION_END
#define PIC_NAME "P_RECIPE_1-6_READY_CON.PDL"
// WINCC:PICNAME_SECTION_END

#define INSTANCENAME ""
#define WINDOW "FixPopup0"
#define TITLE "1-6"
CallPopupWithDynamicTextMoreWindow(lpszPictureName, lpszObjectName, lpszPropertyName,PIC_NAME,TITLE);
}

//Set tag bit with press mouse left button
#include "apdefap.h"
void OnLButtonDown(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName, UINT nFlags, int x, int y)
{
// WINCC:TAGNAME_SECTION_START
// syntax: #define TagNameInAction "DMTagName"
// next TagID : 1
// WINCC:TAGNAME_SECTION_END

// WINCC:PICNAME_SECTION_START
// syntax: #define PicNameInAction "PictureName"
// next PicID : 1
// WINCC:PICNAME_SECTION_END
SetTagByte("DB112_DBB0",0x01);	//Return-Type: BOOL 

}
#include "apdefap.h"
void OnLButtonDown(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName, UINT nFlags, int x, int y)
{
SetTagBit("M82_6",1);	//Return-Type: BOOL 

}

//Get color by global defined color code
#include "apdefap.h"
 long _main(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName)
{
  if( GetTagByte("DB500_DBB1") & 0x07 )
      return CO_GREEN;
  else
      return CO_DARK_GRAY;

}

//Start event if condition required, if not show message box
#include "apdefap.h"
void OnLButtonDown(char* lpszPictureName, char* lpszObjectName, char* lpszPropertyName, UINT nFlags, int x, int y)
{
  #define   TAG_STT_CONDITION   "DB500_DBB2"
  #define   TAG_STT_ACTION   "DB500_DBB4"
  #define   PIC_NAME "P_RECIPE_2-1_READY_CON.PDL"
  #define   TITLE "2-1"

  BYTE temp,btVal;
  long RetBox;
  HWND Handle;
  BOOL bReady;

  bReady = GetTagByte(TAG_STT_CONDITION) & 0x10;	
  if( bReady )      //**** Ready Condition is OK*******//
  {
//****************** Start Sequence Command Action*******************//
    temp = GetTagByte(TAG_STT_ACTION) ;	
    btVal = (BYTE)(( temp & 0xFC ) | 0x01 );
    SetTagByte(TAG_STT_ACTION,btVal);
  return ;
  }
  else
  {
    Handle = FindWindow("PDLRTisAliveAndWaitsForYou","WinCC-Runtime - ");
    RetBox=MessageBox(Handle,"This line is NOT ready to RUN\r\nWant to see condition list?","Please Chek!!!",MB_OKCANCEL|MB_ICONEXCLAMATION|MB_SETFOREGROUND|MB_SYSTEMMODAL);
    if(RetBox==1) 
    {
        CallPopupWithDynamicTextMoreWindow(lpszPictureName, lpszObjectName, lpszPropertyName,PIC_NAME,TITLE);
     }
    else 
        return;
  }

return ;
}

