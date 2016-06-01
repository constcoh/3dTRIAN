#include <windows.h>
#include <process.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
using namespace std;
#include "HEADERS\global_options.h"
#include "HEADERS\easystack.h"
#include "HEADERS\triangle2d.h"
#include "HEADERS\cimage.h"
#include "HEADERS\material.h"
#include "HEADERS\listarray.h"
#include "HEADERS\triangle3d.h"
#include "HEADERS\zbuffer.h"
#include "HEADERS\camera.h"
#include "HEADERS\zlight.h"
#include "HEADERS\light.h"
#include "HEADERS\base.h"
#include "HEADERS\object.h"
#include "HEADERS\objreader.h"
#include "HEADERS\gleams.h"
#include "HEADERS\drawing.h"
#include "HEADERS\drawlights.h"
#include "HEADERS\drawshadow.h"
#include "HEADERS\basetreads.h"
#include "HEADERS\cwindow.h"



int main(){
	cout.precision(10);
	//int a=255+256;
	//int b=a&0x0000FF00;
	//unsigned char *pC=(unsigned char *)&a;
	//cout<<(int)*(pC)<<endl<<(int)*(pC+1)<<endl;

	srand(NULL);
	InitializeCriticalSection(&CGOption::cs);
	MainWindow::RegWndClass();
	HWND hWnd=MainWindow::Create();
	MSG msg;
	ShowWindow(hWnd,1);
	while(GetMessageA(&msg,hWnd,0,0)!=-1){
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	
	//CTrian3dbu d,o1,o2;
	//int res; double f=-100;
	//d.Img=NULL;
	//d.v0.x=2;	d.v0.y=0;	d.v0.z=0;	
	//d.v1.x=0;	d.v1.y=0;	d.v1.z=2;	
	//d.v2.x=0;	d.v2.y=2;	d.v2.z=0;	
	//d.vt0.x=0;			d.vt0.y=0;			
	//d.vt1.x=200;		d.vt1.y=0;			
	//d.vt2.x=200;		d.vt2.y=200;		
	//cout<<"dano:\n";
	//d.fnPrint();
	//CDrawing::fnAmputationXFront(d,o1,o2);
	//cout<<"otv:\n";
	//o1.fnPrint();
	//o2.fnPrint();
	//system("pause");
	CBaseTread::fnKillTreads();
	DeleteCriticalSection(&CGOption::cs);
	//system("pause");
	return 0;
}