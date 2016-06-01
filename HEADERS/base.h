#ifndef _BASE_H_
#define _BASE_H_

typedef CListArray<POINT> CL2d;
typedef CListArray<POINT3> CL3d;
typedef CListArray<CTrian3d> CLTrian;
typedef CListArray<CLight*> CLLight;


struct CBase{
private:
	static CBase *P;
	CBase(){}
public:
	CL3d v,vn;
	CL2d vt;
	CLTrian trian;
	CLLight light;
	static CBase *get(){
		if(P==NULL) P=new CBase();
		return P;
	}
	static int fnCheck();
};
CBase* CBase::P=NULL;

int CBase::fnCheck(){
	CBase *base;	CL2d *VT;	CL3d *V,*VN;	CLTrian *TR; CLLight *LI;
	{CBase *base=CBase::get(); V=&(base->v); VN=&(base->vn); VT=&(base->vt); TR=&(base->trian); LI=&(base->light);}//достаём указатели на с-массивы
	int size;
	POINT3 v3; POINT v2; POINT4 v4; CTrian3d* tr3d;
	//вывод V
	std::cout<<"Base V\n";
	size=V->fnGetSize();
	std::cout<<"  size:"<<size<<'\n';
	for(int i=0;i<size;++i){
		v3=V->g(i); std::cout<<"  i:"<<i<<"\t x:"<<v3.x<<"\t y:"<<v3.y<<"\t z:"<<v3.z<<'\n';
	}
	//ввывод VT
	std::cout<<"Base VT\n";
	size=VT->fnGetSize();
	std::cout<<"  size:"<<size<<'\n';
	for(int i=0;i<size;++i){
		v2=VT->g(i); std::cout<<"  i:"<<i<<"\t x:"<<v2.x<<"\t y:"<<v2.y<<'\n';
	}
	//ввывод VN
	std::cout<<"Base VN\n";
	size=VN->fnGetSize();
	std::cout<<"  size:"<<size<<'\n';
	for(int i=0;i<size;++i){
		v3=VN->g(i); std::cout<<"  i:"<<i<<"\t x:"<<v3.x<<"\t y:"<<v3.y<<"\t z:"<<v3.z<<'\n';
	}
	//ввывод TR
	std::cout<<"Base TR\n";
	size=TR->fnGetSize();
	std::cout<<"  size:"<<size<<'\n';
	for(int i=0;i<size;++i){
		tr3d=TR->gP(i); std::cout<<"  i:"<<i<<"\t Img:"<<tr3d->Img<<"\t ImgNs:"<<tr3d->ImgNs<<' ';
		POINT sz; tr3d->ImgNs->fnGet_sz(sz);
		std::cout<<sz.x<<' '<<sz.y<<'\n';
	}
	//вывод LI
	{
		char namef[20],namef2[20]; strcpy(namef,"ANSWER\\ZBUF\\A0.bmp"); strcpy(namef2,"ANSWER\\HBUF\\A0.bmp");
		std::cout<<"Base LI\n";
		size=LI->fnGetSize();
		std::cout<<"  size:"<<size<<'\n';
		CLight *li;
		for(int i=0;i<size;++i){
			li=LI->g(i);
			std::cout<<"  i:"<<i<<"\t type:"<<li->type<<"\n";
			v4=li->pos;	std::cout<<"   pos:";v4.fnPrint();
			v4=li->u;	std::cout<<"     u:";v4.fnPrint();
			v4=li->v;	std::cout<<"     v:";v4.fnPrint();
			v4=li->w;	std::cout<<"     w:";v4.fnPrint();

			namef[13]='0';	namef2[13]='0';
			switch(li->type){
				case(0):
					for(int j=0;j<6;++j) { li->zbuf[j].fnPrint(namef); ++namef[13]; li->zbuf[j].fnPrintHelp(namef2); ++namef2[13]; }
				break;
				case(1):
				li->zbuf[0].fnPrint(namef); ++namef[13];	li->zbuf[0].fnPrintHelp(namef2); ++namef2[13];
			}
			std::cout<<"  Ia:"<<li->Ia<<"\t Ir:"<<li->Ir<<"\t Ig:"<<li->Ig<<"\t Ib:"<<li->Ib<<'\n';
			++namef[12]; ++namef2[12];
		}
	}
		

	return 0;
}


#endif