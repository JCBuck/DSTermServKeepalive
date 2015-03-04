#include <stdio.h>
#include <windows.h>
/****************************************************************************
 *                                                                          *
 * Function: main                                                           *
 *                                                                          *
 * Purpose : Main entry point.                                              *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/
//-------------------------------------------------------------------------------
BOOL CALLBACK enum_wnd_proc(HWND hUIMainClass, LPARAM lp)
{
    char cls[1024] = {0};
    GetClassNameA(hUIMainClass, cls, 1024);

    if(!strcmp("NeoterisTermServices",cls))
    {
		char logging[512] = "";
		char mainTitle[80] = "";
		GetWindowText(hUIMainClass,mainTitle,80);
		sprintf(logging,"%sFound %s => %s!\n",logging, cls, mainTitle);

		HWND hAtlAxWin80 = FindWindowEx(hUIMainClass,0,"AtlAxWin80",0);
		if(!hAtlAxWin80)
			return TRUE;
		sprintf(logging,"%s> Found AtlAxWin80: 0x%p\n",logging, hAtlAxWin80);


		HWND hATL= FindWindowEx(hAtlAxWin80,0,0,0);
		if(!hATL)
			return TRUE;
		sprintf(logging,"%s> Found ATL:xxxxxxxx: 0x%p\n",logging, hATL);

		hUIMainClass = FindWindowEx(hATL,0,"UIMainClass",0);
		if(!hUIMainClass)
			return TRUE;
		printf("%s> Found UIMainClass: 0x%p (Not fullscreen, windowed)\n> ",logging, hUIMainClass);

	}
    GetClassNameA(hUIMainClass, cls, 1024);

    if(!strcmp("UIMainClass",cls))
    {
		
		char mainTitle[80] = "";
		GetWindowText(hUIMainClass,mainTitle,80);
		printf("Found %s => %s!\n", cls, mainTitle);

		HWND hUIContainerClass = FindWindowEx(hUIMainClass,0,"UIContainerClass",0);
		if(!hUIContainerClass)
			return TRUE;
		printf("> Found UIContainerClass: 0x%p\n", hUIContainerClass);


		HWND hIHWindowClass = FindWindowEx(hUIContainerClass,0,"IHWindowClass",0);
		if(!hIHWindowClass)
			return TRUE;
		printf("> Found IHWindowClass: 0x%p\n", hIHWindowClass);


		SendMessage(hUIMainClass,WM_ACTIVATEAPP,TRUE,0);
		SendMessage(hUIMainClass,WM_NCACTIVATE,TRUE,0);
		SendMessage(hUIMainClass,WM_ACTIVATE,WA_ACTIVE,0);

		PostMessage(hIHWindowClass,WM_KEYDOWN,'A',0);
		Sleep(100);
		PostMessage(hIHWindowClass,WM_KEYUP,'A',0);

		SendMessage(hUIMainClass,WM_NCACTIVATE,TRUE,0);
		SendMessage(hUIMainClass,WM_ACTIVATE,WA_INACTIVE,0);
		SendMessage(hUIMainClass,WM_ACTIVATEAPP,FALSE,0);
		
		
		printf("> Sent Key\n");

        // match!
    }


    return TRUE;
}

//-------------------------------------------------------------------------------
int main(int argc, char *argv[])
{	
	int count = 0;
	char title[80] = "DSTermServ KEEP ALIVE";

	
	
	while(1){

		  SYSTEMTIME lt;
		  
		  GetLocalTime(&lt);
		  
		printf("Sending Keep Alive at %d/%d/%d %02d:%02d:%02d\n",  lt.wMonth,lt.wDay,lt.wYear, lt.wHour, lt.wMinute, lt.wSecond);
		EnumWindows(enum_wnd_proc, 0); 

		while(count < 60*1){

			sprintf(title,"DSTermServe KEEP ALIVE - Last Keep Alive: %d seconds",count);
			SetConsoleTitle(title);
			count++;
			Sleep(1000);
		}
		count = 0;


	}
    return 0;
}


