#ifndef _CWINDOW_H_
#define _CWINDOW_H_
HWND hEdit;

class MainWindow{
private:
	
public:
	static const char szClassName[];
	static const char szWindowName[];
	static LRESULT _stdcall WinProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam);
 	static void RegWndClass(){
		WNDCLASSA CWnd;
		CWnd.cbClsExtra=0;
		CWnd.cbWndExtra=0;
		CWnd.hbrBackground=(HBRUSH)GetStockObject(GRAY_BRUSH);
		CWnd.hCursor=LoadCursorA(NULL,IDC_ARROW);
		CWnd.hIcon=LoadIconA(NULL,IDI_APPLICATION);
		CWnd.hInstance=NULL;
		CWnd.lpfnWndProc=&WinProc;
		CWnd.lpszClassName=szClassName;
		CWnd.lpszMenuName=NULL;
		CWnd.style=CS_DBLCLKS;
		if(!RegisterClassA(&CWnd)) std::cout<<"Error of register window class.\n";
	}
	static HWND Create(){
		HWND hWnd= CreateWindowA(szClassName,szWindowName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,340,420,HWND_DESKTOP,NULL,NULL,NULL);

// Label 1
   HWND hLabel = CreateWindowA("static", "ST_U",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                              5, 310, 300, 16,
                              hWnd, NULL,
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
   SetWindowText(hLabel, "Вперед, назад, влево, вправо - стрелки");
// Label 2
   HWND hLabel2 = CreateWindowA("static", "ST_U",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                              5, 310+16+5, 300, 16,
                              hWnd, NULL,
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
   SetWindowText(hLabel2, "Вверх - ', вниз - /");
 // Label 3
   HWND hLabel3 = CreateWindowA("static", "ST_U",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                              5, 310+(16+5)*2, 300, 16,
                              hWnd, NULL,
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
   SetWindowText(hLabel3, "поворот влево - G, поворот вправо - J");
 
    // Label 3
   HWND hLabel4 = CreateWindowA("static", "Для отрисовки нажмите любую стрелку на клавиатуре",
                              WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                              5, 5, 300, 300,
                              hWnd, NULL,
							  (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);

   return hWnd;
	}
};

const char MainWindow::szClassName[]="KSTriangle";
const char MainWindow::szWindowName[]="KSTriangle";

LRESULT MainWindow::WinProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	HDC dc;
	POINT point,params,pos;
	RECT rc;
	bool res;
	int iX,iY;
	//std::cout<<"!";
	

	switch(iMsg){
		case(WM_CREATE):
			{//1+1
				CGOption::check^=true;				cout<<"CGOption::Check is ";
				if(CGOption::check) cout<<"on.\n"; else cout<<"off.\n";
				if(!CGOption::check) CGOption::awtoredraw=false;
			}
			{//I
				std::cout<<"Initial:\n";
				CCamera *pCam=CCamera::getCam();
				pCam->fnLoadTXT("OPTIONS\\camera_gleams.txt");
				CObjReader::readlight("OPTIONS\\lights_gleams.txt");

			}
			{//L
				//CObjReader::readobj("TEST\\BIGCUBE\\input.obj");
				//CObjReader::readobj("TEST\\CUBEM500\\input.obj");
				CObjReader::readobj("TEST\\GLEAMS\\SQUARE\\input.obj");
				//CObjReader::readobj("TEST\\SQUARE2\\input.obj");
				//CObjReader::readobj("TEST\\SQUARE3\\input.obj");
				//CObjReader::readobj("TEST\\SPHERA\\input.obj");

				CObjReader::setPointerImgToTrians();

			}
			{//F1
				CBaseTread::fnCreateTreads(CGOption::TreadCount);

			}
			{//F4
				CBaseTread::fnCommand(3);

			}
			{//2+1
				CGOption::awtoredraw^=true;		cout<<"CGOption::awtoredraw is "; if(CGOption::awtoredraw) cout<<"on.\n"; else cout<<"off.\n";
				if(CGOption::awtoredraw)   CGOption::check=false;
			}
			{//0
				//CLight* pL=CBase::get()->light.g(0);
				//CDrawShadow::fnDrawShadow(0,pL);
				//CBaseMaterial::getPBM()->fnMultIaLast(CLight::Ia);
				//std::cout<<"end 71\n";

			}
			{//D
				cout<<"Drawing:\n";
				CDrawing::fnDraw();
				POINT pos; pos.x=pos.y=5;
				CZBuffer::get()->fnDrawWHND(hWnd,pos);
			}
			break;
		case(WM_TIMER):
			break;
		case(WM_DESTROY):
			break;
		case(WM_PAINT):
			break;
		case(WM_LBUTTONDOWN):{

		}break;
		case(WM_LBUTTONDBLCLK):
		break;
		case(WM_RBUTTONDBLCLK):
		break;
		case(WM_MOUSEMOVE):
			break;
		case(WM_LBUTTONUP):
			break;
		case(WM_RBUTTONDOWN):
			//Img.fnVerticalReflect();
			break;
		case(WM_RBUTTONUP):
			break;
		case(WM_COMMAND):
		case(WM_HOTKEY):
			break;
		case(WM_KEYDOWN):
			//std::cout<<"WM_KEYDOWN\n";
			int scan=0x00FF0000;
			scan=(scan&lParam)>>16;
			std::cout<<"scan="<<scan<<'\n';
			if(scan==30){//A - загрузка тестовой картинки
//					HDC tdc=GetDC(hWnd),dc=CreateCompatibleDC(tdc);
//					HBITMAP btm=CreateCompatibleBitmap(tdc,240,140); SelectObject(dc,btm);
//					std::cout<<BitBlt(tdc,10,10,240,140,dc,0,0,SRCCOPY);
//					ReleaseDC(hWnd,tdc);

			}
			if(scan==23){//I - инициализация
				std::cout<<"Initial:\n";
				CCamera *pCam=CCamera::getCam();
				pCam->fnLoadTXT("OPTIONS\\camera_gleams.txt");
				CObjReader::readlight("OPTIONS\\lights_gleams.txt");
			}
			if(scan==38){//L - Loading
				//CObjReader::readobj("TEST\\BIGCUBE\\input.obj");
				//CObjReader::readobj("TEST\\CUBEM500\\input.obj");
				CObjReader::readobj("TEST\\GLEAMS\\SQUARE\\input.obj");
				//CObjReader::readobj("TEST\\SQUARE2\\input.obj");
				//CObjReader::readobj("TEST\\SQUARE3\\input.obj");
				//CObjReader::readobj("TEST\\SPHERA\\input.obj");

				CObjReader::setPointerImgToTrians();
								
//				CDrawing::fnDraw(
//					HDC tdc=GetDC(hWnd),dc=CreateCompatibleDC(tdc);
//					HBITMAP btm=CreateCompatibleBitmap(tdc,240,140); SelectObject(dc,btm);
//					Img.fnSaveDC(dc,btm);  
//					std::cout<<BitBlt(tdc,10,10,240,140,dc,0,0,SRCCOPY);
//					ReleaseDC(hWnd,tdc);
			}
			if(scan==32){//D - Drawing
				cout<<"Drawing:\n";
				CDrawing::fnDraw();
				POINT pos; pos.x=pos.y=5;
				CZBuffer::get()->fnDrawWHND(hWnd,pos);
			}
//			}
			if(scan==31){
				std::cout<<"SAVE MATERIALS\n";
				CBaseMaterial::getPBM()->fnSaveMaterials("ANSWER\\MATERIALS\\");
			}
			if(scan==2){CGOption::check^=true;				cout<<"CGOption::Check is ";		 if(CGOption::check) cout<<"on.\n"; else cout<<"off.\n";
				if(!CGOption::check) CGOption::awtoredraw=false;}
			if(scan==3){CGOption::awtoredraw^=true;		cout<<"CGOption::awtoredraw is "; if(CGOption::awtoredraw) cout<<"on.\n"; else cout<<"off.\n";
				if(CGOption::awtoredraw)   CGOption::check=false;}
			if(scan==4){CGOption::checktime^=true;		cout<<"CGOption::checktime is "; if(CGOption::checktime) cout<<"on.\n"; else cout<<"off.\n";}
			if(scan==5){CGOption::gleams^=true;		cout<<"CGOption::gleams is "; if(CGOption::gleams) cout<<"on.\n"; else cout<<"off.\n";}
			if(scan==72){//вперёд
				CCamera::getCam()->fnMoveFront(); if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==80){//назад
				CCamera::getCam()->fnMoveBack();  if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==75){//влево
				CCamera::getCam()->fnMoveLeft();  if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==77){//вправо
				CCamera::getCam()->fnMoveRight(); if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==40){//вверх
				CCamera::getCam()->fnMoveUp();    if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==53){//вниз
				CCamera::getCam()->fnMoveDown();  if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==34){//поворот влево
				CCamera::getCam()->fnRotateLeft(); if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}
			if(scan==36){//поворот вправо
				CCamera::getCam()->fnRotateRight();if(CGOption::awtoredraw) {CDrawing::fnDraw();	POINT pos; pos.x=pos.y=5;	CZBuffer::get()->fnDrawWHND(hWnd,pos);}}

			if(scan==25){ //|P| рисуем z-буфера источников света
				//CDrawLights::fnDraw(2);
			}
			if(scan==24){// |O| тотальная проверка
				std::cout<<"CHECK:\n"; 
				CBase::fnCheck();
				CBaseMaterial::getPBM()->fnSaveChange("ANSWER\\USED\\");
				CBaseMaterial::getPBM()->fnSaveHelp("ANSWER\\HELP\\");
			}
			if(scan==59){//|F1| запуск потоков
				CBaseTread::fnCreateTreads(CGOption::TreadCount);
			}
			if(scan==60){//|F2| остановка потоков
				CBaseTread::fnKillTreads();
			}
			if(scan==61){//|F3| проверка потоков
				CBaseTread::fnCommand(2);
			}
			if(scan==62){//|F4| рисование z-буфферов
				CBaseTread::fnCommand(3);
			}
			if(scan==66){//|F8| рисование освещения
				CBaseTread::fnCommand(4);
			}
			if(scan==7){//|6| создание копий тексур
				std::cout<<"fnMakeCopy("<<CGOption::TreadCount<<")\n";
				CBaseMaterial::getPBM()->fnMakeCopy(CGOption::TreadCount+1);
			}
			if(scan==8){//|7| удаление копий тексур
				std::cout<<"fnDeleteCopy()\n";
				CBaseMaterial::getPBM()->fnDeleteCopy();
			}
			if(scan==9){//|8| слияние копий текстур
				std::cout<<"fnMergeCopy()\n";
				CBaseMaterial::getPBM()->fnMegreCopy();
			}
			if(scan==10){//|9| сохраняем освещённую картинку
				std::cout<<"fnMergeCopy()\n";
				CBaseMaterial::getPBM()->fnSaveCopy("ANSWER\\COPIES\\");
			}
			if(scan==11){//|0| проба отрисовки теней
				CLight* pL=CBase::get()->light.g(0);
				CDrawShadow::fnDrawShadow(0,pL);
				CBaseMaterial::getPBM()->fnMultIaLast(CLight::Ia);
				std::cout<<"end 71\n";
			}
			break;
	}
	
	return DefWindowProc(hWnd,iMsg,wParam,lParam);
}
#endif