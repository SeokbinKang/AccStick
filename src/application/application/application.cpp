// application.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "application.h"
#include <conio.h>
#include "SerialUtil.h"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int initMagnification(float );
extern int endMagnification();
extern void _tmain2();
extern BOOL SetDisplayResolution(long PelsWidth, long PelsHeight);
extern void SetDisplayDefaults();
extern void setDisplayBrightness(int);
extern void testbr();
extern bool ChangeVolume(double nVolume,bool bScalar);
extern void setupDesk();
extern void changeBR(int);
extern void changeCursor(int);
// 유일한 응용 프로그램 개체입니다.

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int resolutionProfile[5][2]={1920,1080,1600,900,1280,800,1024,768,1024,768};
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 오류 코드를 필요에 따라 수정합니다.
			_tprintf(_T("심각한 오류: MFC를 초기화하지 못했습니다.\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 응용 프로그램의 동작은 여기에서 코딩합니다.
		}
	}
	else


	{
		// TODO: 오류 코드를 필요에 따라 수정합니다.
		_tprintf(_T("심각한 오류: GetModuleHandle 실패\n"));
		nRetCode = 1;
	}
//	testbr();
	//setupDesk();
	//changeCursor(4);
	//changeBR(30);
	int kk=0;
	try{
		//create an instance of SerialUtil object
		SerialUtil* su = new SerialUtil();
		string str;
		int nStick;
		int ids[5];
		int values[5];
		int prev_values[5]={0,0,0,0,0};

		while (SerialUtil::SP->IsConnected())
		{
			//read string from commandLine
			string readString = su->read();
			int ret=0;
			if(readString.empty()) continue;
	//printf("msg %d : %s\n",ret,readString.c_str());
			
	
			
			ret=sscanf_s(readString.c_str(),"%d %d %d %d %d %d %d %d %d %d ",&nStick,ids,values,ids+1,values+1,ids+2,values+2,ids+3,values+3,values+4);
			
			//write the string read from commandLine
					
			//process MSG
			
			if(ret==10) {
					for(int i=0;i<4;i++){
						if(values[i]>6) values[i]=6;
						if(values[i]<2) values[i]=2;
					}
					

					if(ids[0]==0 && values[0]!=prev_values[0]) {
						//change volume [2,6] is mapped to [0.2,0.6]
							initMagnification(0.7f+0.3*(values[0]-1));
						prev_values[0]=values[0];
						
						
						
					} else 	if(ids[1]==9 && values[1]!=prev_values[1]) {
						//change display resolution
						
						SetDisplayResolution(resolutionProfile[values[1]-2][0],resolutionProfile[values[1]-2][1]);
						prev_values[1]=values[1];
						
					} else 		if(ids[2]==5&& values[2]!=prev_values[2]) {
						//change volume [2,6] is mapped to [0.2,0.6]    
						changeCursor((values[2]));
						prev_values[2]=values[2];
						
						
					}else if(ids[3]==3 && values[3]!=prev_values[3]) {
						//change brightness of display
						changeBR(20*(values[3]-1));
						prev_values[3]=values[3];
						

					} else 	if(values[4]!=prev_values[4] ) {
						ChangeVolume(values[4]*0.05f,true);
						prev_values[4]=values[4];
						
					}
			}
			kk=waitKey(500);
			if(kk=='q') break;
		}
	}
	catch (string s)
	{
		cout << "..ERROR OCCURED::" << s << " :( \n";
	}




	/*ChangeVolume(0.1,true);
	Sleep(2000);
	ChangeVolume(0.2,true);
	Sleep(2000);
	ChangeVolume(0.3,true);
	
	Sleep(2000);
	ChangeVolume(0.4,true);
	Sleep(2000);
	ChangeVolume(0.2,true);*/
	
	/* if (SetDisplayResolution(resolutionProfile[1][0],resolutionProfile[1][1]))
    {
        printf("\nPress Enter to return to default mode.\n");
        _getch();
        SetDisplayDefaults();
    }
	  if (SetDisplayResolution(resolutionProfile[2][0],resolutionProfile[2][1]))
    {
        printf("\nPress Enter to return to default mode.\n");
        _getch();
        SetDisplayDefaults();
    }
	   if (SetDisplayResolution(resolutionProfile[3][0],resolutionProfile[3][1]))
    {
        printf("\nPress Enter to return to default mode.\n");
        _getch();
        SetDisplayDefaults();
    }*/
	//initMagnification(2.0f);
	//Sleep(5000);
	//endMagnification();
	return nRetCode;
}
