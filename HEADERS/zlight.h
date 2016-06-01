#ifndef _ZLIGHT_H_
#define _ZLIGHT_H_

struct CZLight{
protected:
	POINT sz;
	double *Z,*Zhelp;
public:
	double* get_Z(){return Z;}
	double* get_Zhelp(){return Zhelp;}
	CZLight():Z(0),Zhelp(0){sz.x=sz.y=0;}
	~CZLight(){		 if(Z!=NULL) {delete[] Z; Z=NULL;}if(Zhelp!=NULL) {delete[] Zhelp; Zhelp=NULL;}}
	int fnClear(){	sz.x=sz.y=NULL; if(Z!=NULL) {delete[] Z; Z=NULL;} if(Zhelp!=NULL) {delete[] Zhelp; Zhelp=NULL;}  return 0;}
	int fnSetSize(const POINT &size){
		fnClear();
		sz.x=size.x;	sz.y=size.y;
		Z=new double[sz.x*sz.y]; memset(Z,0,sz.x*sz.y*4);
		Zhelp=new double[sz.x*sz.y]; memset(Zhelp,0,sz.x*sz.y*4);
		return 0;
	}
	int fnSetFog(const int &color){
		int gsz=sz.x*sz.y;
		double *tekZ=Z;
		for(int i=0;i<gsz;++i,++tekZ) {*tekZ=-1;}
		tekZ=Zhelp;
		for(int i=0;i<gsz;++i,++tekZ) {*tekZ=-1;}
		return 0;
	}
	int fnDrawTrian2D(CTrian3dibu tr){
		//if(CGOption::check){
			//std::cout<<"   tr:\n";
			//cout<<"    v0:  "<<tr.v0.x<<"\t "<<tr.v0.y<<'\n';
			//cout<<"    v1:  "<<tr.v1.x<<"\t "<<tr.v1.y<<'\n';
			//cout<<"    v2:  "<<tr.v2.x<<"\t "<<tr.v2.y<<'\n';
			//cout<<"    vt0: "<<tr.vt0.x<<"\t "<<tr.vt0.y<<'\n';
			//cout<<"    vt1: "<<tr.vt1.x<<"\t "<<tr.vt1.y<<'\n';
			//cout<<"    vt2: "<<tr.vt2.x<<"\t "<<tr.vt2.y<<'\n';
			//cout<<"    Img: "<<tr.Img<<'\n';
			//cout<<"    g0: "<<tr.g0<<"\t g1: "<<tr.g1<<"\t g2: "<<tr.g2<<'\n';
			//system("pause");
		//}
	//находим промежуток Y
		int yi=tr.v0.y,ya=yi;
		if(tr.v1.y>ya) ya=tr.v1.y;	if(tr.v1.y<yi) yi=tr.v1.y;
		if(tr.v2.y>ya) ya=tr.v2.y;	if(tr.v2.y<yi) yi=tr.v2.y;
		int dy=ya-yi+1;
	//выделяем память для X
		int *Xl=new int[dy],*Xr=new int[dy],*Pl=Xl,*Pr=Xr;
		//POINT *TRl=new POINT[dy],*pTRl=TRl-yi, *TRr=new POINT[dy],*pTRr=TRr-yi;
		double *Gl=new double[dy],*pGl=Gl-yi, *Gr=new double[dy],*pGr=Gr-yi; 
		for(int y=yi;y<=ya;++y,++Pl,++Pr){*Pl=sz.x;*Pr=0;}
		Pl=Xl-yi;Pr=Xr-yi; 
	//растеризуем отрезок v0-v1
		{
			POINT a=tr.v0,b=tr.v1; /*POINTD at,bt;at=tr.vt0;bt=tr.vt1;*/ double ag=tr.g0,bg=tr.g1;
			if(a.y>b.y) {swap(a,b); /*swap(at,bt);*/ swap(ag,bg);}
			double dvx=b.x-a.x,dvy=b.y-a.y, /*dtx=bt.x-at.x, dty=bt.y-at.y,*/ dg=bg-ag; 
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N; /*dtx/=(float)N; dty/=(float)N;*/ dg/=(float)N;
			double tx=a.x,ty=a.y,/*ttx=at.x,tty=at.y,*/ tg=ag;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy,/*ttx+=dtx,tty+=dty,*/tg+=dg){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pGl[tp.y]=tg; /*pTRl[tp.y].x=ttx; pTRl[tp.y].y=tty;*/}
				if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pGr[tp.y]=tg; /*pTRr[tp.y].x=ttx; pTRr[tp.y].y=tty;*/}
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
			}
		}
	//растеризуем отрезок v1-v2
		{
			POINT a=tr.v1,b=tr.v2; /*POINTD at,bt;at=tr.vt1;bt=tr.vt2;*/ double ag=tr.g1,bg=tr.g2;
			if(a.y>b.y) {swap(a,b); /*swap(at,bt);*/ swap(ag,bg);}
			double dvx=b.x-a.x,dvy=b.y-a.y, /*dtx=bt.x-at.x, dty=bt.y-at.y,*/ dg=bg-ag; 
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N; /*dtx/=(float)N; dty/=(float)N;*/ dg/=(float)N;
			double tx=a.x,ty=a.y,/*ttx=at.x,tty=at.y,*/ tg=ag;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy,/*ttx+=dtx,tty+=dty,*/tg+=dg){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pGl[tp.y]=tg; /*pTRl[tp.y].x=ttx; pTRl[tp.y].y=tty;*/}
				if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pGr[tp.y]=tg; /*pTRr[tp.y].x=ttx; pTRr[tp.y].y=tty;*/}
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
			}
		}
	//растеризуем отрезок v0-v2
		{
			POINT a=tr.v0,b=tr.v2; /*POINTD at,bt;at=tr.vt0;bt=tr.vt2;*/ double ag=tr.g0,bg=tr.g2;
			//cout<<"   tr.vt0: "<<tr.vt0.x<<' '<<tr.vt0.y<<'\n';
			//cout<<"   tr.vt0: "<<tr.vt0.x<<' '<<tr.vt0.y<<'\n';

			if(a.y>b.y) {swap(a,b); /*swap(at,bt);*/ swap(ag,bg);}
			double dvx=b.x-a.x,dvy=b.y-a.y, /*dtx=bt.x-at.x, dty=bt.y-at.y,*/ dg=bg-ag; 
			//cout<<"   dtx: "<<dtx<<"   dty: "<<dty<<'\n';
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N; /*dtx/=(float)N; dty/=(float)N;*/ dg/=(float)N;
			//cout<<"   dtx: "<<dtx<<"   dty: "<<dty<<'\n';
			double tx=a.x,ty=a.y,/*ttx=at.x,tty=at.y,*/ tg=ag;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy,/*ttx+=dtx,tty+=dty,*/tg+=dg){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pGl[tp.y]=tg; /*pTRl[tp.y].x=ttx; pTRl[tp.y].y=tty;*/}
				if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pGr[tp.y]=tg; /*pTRr[tp.y].x=ttx; pTRr[tp.y].y=tty;*/}
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\t pTRr.x="<<pTRr[tp.y].x<<"\t pTRr.y="<<pTRr[tp.y].y<<"\n";
			}
		}
		//system("pause");
	//рисуем на M
		{
			//int *Ml=M+sz.x*yi,*Mt;
			//int *Texture; tr.Img->fnGet_pM(Texture);
			//POINT szt; tr.Img->fnGet_sz(szt);
			for(int y=yi;y<=ya && y<sz.y;++y/*,Ml+=sz.x*/){
				int left=Pl[y],right=Pr[y];
				if(right==left) continue;
				//POINT pti; POINTD ptd,dtd; ptd=pTRl[y]; dtd=pTRr[y]; dtd.x-=ptd.x; dtd.y-=ptd.y;
				//std::cout<<"dtd:"<<dtd.x<<' '<<dtd.y<<'\n';
				//dtd.x/=(double)(right-left); dtd.y/=(double)(right-left);
				//Mt=Ml+left;
				double tgl=pGl[y],tgi=tgl,tgr=pGr[y],tgd=(tgr-tgl)/(double)(right-left); 

				
				/*std::cout<<"l,r="<<left<<' '<<right<<'\n';
				std::cout<<"ptd:"<<ptd.x<<' '<<ptd.y<<'\n';
				std::cout<<"dtd:"<<dtd.x<<' '<<dtd.y<<'\n';
				system("pause");*/
				for(int x=left;x<=right;++x,/*++Mt,ptd.x+=dtd.x,ptd.y+=dtd.y,*/tgi+=tgd){
					//pti.x=(int)(ptd.x); 	pti.y=(int)(ptd.y);
					if(tgi>Z[y*sz.x+x]){
						Z[y*sz.x+x]=tgi;
					}
					//cout<<"		p="<<x<<' '<<y<<" tgi="<<tgi<<" Z[]="<<Z[y*sz.x+x]<<'\n';

				}
				//system("pause");
			}
		}
		delete[] Xl;		delete[] Xr;
		//delete[] TRl;		delete[] TRr;
		delete[] Gl;		delete[] Gr;
		//сохраняем
		{
			//SaveBuf0((COLORREF*)M,sz,"drawing0.txt");
			//SaveBuf1((COLORREF*)M,sz,"drawing1.txt");
			//SaveBuf2((COLORREF*)M,sz,"drawing2.txt");
			//SaveBuf3((COLORREF*)M,sz,"drawing3.txt");

		}
		return 0;
	}
	int fnGet_sz(POINT (&size)){size=sz; return 0;}
	int fnPrint(const char *filename){
		CImage OutBuf;
		OutBuf.fnSetSize(sz);
		int *pI;OutBuf.fnGet_pM(pI);
		for(int y=0;y<sz.y;++y) for(int x=0;x<sz.x;++x) {pI[y*sz.x+x]=((int)((Z[y*sz.x+x]+1.0)*128.0))<<8;
		//if(Z[y*sz.x+x]!=-1) std::cout<<Z[y*sz.x+x]; 
		}
		OutBuf.fnSaveBMP(filename);
		return 0;
	}
	int fnPrintHelp(const char *filename){
		CImage OutBuf;
		OutBuf.fnSetSize(sz);
		int *pI;OutBuf.fnGet_pM(pI);
		for(int y=0;y<sz.y;++y) for(int x=0;x<sz.x;++x) {pI[y*sz.x+x]=((int)((Zhelp[y*sz.x+x]+1.0)*128.0))<<8;
		//if(Z[y*sz.x+x]!=-1) std::cout<<Z[y*sz.x+x]; 
		}
		OutBuf.fnSaveBMP(filename);
		return 0;
	}
};


#endif