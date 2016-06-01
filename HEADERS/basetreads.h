#ifndef _BASETREADS_H_
#define _BASETREADS_H_

class CBaseTread{
private:
	static int status;
	static int iCount;
	static int iWait;
	static int iStackSize;
	static bool* bFinish;
	static bool fnCheckFinish(){
		bool *pF=bFinish;
		for(int i=0;i<iCount;++i,++pF) if(!(*pF)) return false;
		return true;
	}
	static int fnSetFinishFalse(){
		bool *pF=bFinish;
		for(int i=0;i<iCount;++i,++pF) *pF=false;
		return 0;
	}
	static int FuncDrawZBuffer(int ID){
		//CDanoTread *dano=(CDanoTread *)d;
		int iStart,iFinish,iSize=CBase::get()->light.fnGetSize();
		if(iSize%iCount==0){
			iSize/=iCount;
			iStart=iSize*ID; iFinish=iSize+iStart;
		}else{
			iSize/=(iCount-1);
			if(ID<iCount-1){
				iStart=iSize*ID; iFinish=iSize+iStart;
			}else{
				iStart=iSize*ID; iFinish=CBase::get()->light.fnGetSize();
			}
		}
		CLight *pLight;
		CCamera *pCam; CZLight *pZBuf;
		CLLight *pLLight=&(CBase::get()->light);
		EnterCriticalSection(&CGOption::cs);
		std::cout<<"TREAD:"<<ID<<" start drawing z-buffer St:"<<iStart<<"\t finish:"<<iFinish<<'\n';
		LeaveCriticalSection(&CGOption::cs);

		for(int i=iStart;i<iFinish;++i){
			if(CGOption::check) std::cout<<"i="<<i<<"\n";
			pLight=pLLight->g(i); pCam=pLight->cam;	pZBuf=pLight->zbuf;
			switch(pLight->type){
				case(0):	for(int j=0;j<6;++j,++pCam,++pZBuf) CDrawLights::fnDrawZ(pCam,pZBuf);	break;
				case(1):	CDrawLights::fnDrawZ(pCam,pZBuf);	break;
			}
		}
		EnterCriticalSection(&CGOption::cs);
		std::cout<<"TREAD:"<<ID<<" finish drawing z-buffer\n";
		LeaveCriticalSection(&CGOption::cs);
		return 0;
	}
	static int FuncDrawShadow(int ID){
		//CDanoTread *dano=(CDanoTread *)d;
		int iStart,iFinish,iSize=CBase::get()->light.fnGetSize();
		if(iSize%iCount==0){
			iSize/=iCount;
			iStart=iSize*ID; iFinish=iSize+iStart;
		}else{
			iSize/=(iCount-1);
			if(ID<iCount-1){
				iStart=iSize*ID; iFinish=iSize+iStart;
			}else{
				iStart=iSize*ID; iFinish=CBase::get()->light.fnGetSize();
			}
		}
		CLight *pLight;
		CCamera *pCam; CZLight *pZBuf;
		CLLight *pLLight=&(CBase::get()->light);
		EnterCriticalSection(&CGOption::cs);
		std::cout<<"TREAD:"<<ID<<" start drawing shadow St:"<<iStart<<"\t finish:"<<iFinish<<'\n';
		LeaveCriticalSection(&CGOption::cs);

		for(int i=iStart;i<iFinish;++i){
			CDrawShadow::fnDrawShadow(ID,pLLight->g(i));
		}
		EnterCriticalSection(&CGOption::cs);
		std::cout<<"TREAD:"<<ID<<" finish drawing shadow\n";
		LeaveCriticalSection(&CGOption::cs);
		return 0;
	}
public:
	struct CDano{
		int ID;
	};

	static void fnTread(void *PD){
		CDano *pD=(CDano*)PD;
		bool *pFinish=bFinish+(pD->ID);
		EnterCriticalSection(&CGOption::cs);
		std::cout<<"TREAD ID="<<pD->ID<<" is new\n";
		LeaveCriticalSection(&CGOption::cs);

		while(true){
			if(status!=0 && !(*pFinish)) switch(status){
				case(1):// оманда на завершение
					EnterCriticalSection(&CGOption::cs);
					std::cout<<"TREAD ID="<<pD->ID<<" is died\n";
					--iCount;
					LeaveCriticalSection(&CGOption::cs);
					delete pD; 
					return;
				break;
				case(2)://¬ывести информацию о потоке
					EnterCriticalSection(&CGOption::cs);
					std::cout<<"TREAD ID="<<pD->ID<<'\n';
					LeaveCriticalSection(&CGOption::cs);
					*pFinish=true;
				break;
				case(3)://отрисовка z-буферов
					FuncDrawZBuffer(pD->ID);
					*pFinish=true;
				break;
				case(4)://отрисовка освещени€
					FuncDrawShadow(pD->ID);
					*pFinish=true;
				break;

			}
			_sleep(iWait);
		}
		return;
	}
	static int fnCreateTreads(const int &TreadNumber){
		if(status!=-1) return -1;
		status=0;
		iCount=TreadNumber;
		if(bFinish!=NULL) delete[] bFinish; bFinish=new bool[iCount]; fnSetFinishFalse();
		CDano *pD=NULL;
		for(int i=0;i<iCount;++i){
			pD=new CDano; pD->ID=i;
			_beginthread(fnTread,iStackSize,pD);
			pD=NULL;
		}
		return 0;
	}
	static int fnCommand(const int &iCmd){
		if(status!=0) return -1;
		std::cout<<"fnCommand("<<iCmd<<")\n";
		if(iCmd==4)	CBaseMaterial::getPBM()->fnMakeCopy(CGOption::TreadCount+1);
		status=iCmd;
		if(iCmd==4)	CBaseMaterial::getPBM()->fnMultIaLast(CLight::Ia);		//если команда на освещение, то главный поток рисует свет тьмы
		while(!fnCheckFinish()) _sleep(iWait);
		fnSetFinishFalse();
		status=0;
		return 0;
	}
	static int fnKillTreads(){
		if(status!=0) return -1;
		std::cout<<"fnKillTreads()\n";
		status=1;
		while(iCount>0) _sleep(iWait);
		status=-1;
		if(bFinish!=NULL){delete[] bFinish; bFinish=NULL;}
		return 0;
	}
};

int CBaseTread::status=-1;
int CBaseTread::iCount=0;
int CBaseTread::iWait=250;
int CBaseTread::iStackSize=4096*4;
bool* CBaseTread::bFinish=NULL;

#endif