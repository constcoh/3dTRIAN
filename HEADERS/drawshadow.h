#ifndef _DRAWSHADOW_H_
#define _DRAWSHADOW_H_

class CDrawShadow{
private:

	static int fnRound(const double &d){
		if(d>0){
			if(d-(double)(int)d>=0.5) return (int)d+1; else return (int)d;
		}else{
			if(d-(double)(int)d<-0.5) return (int)d-1; else return (int)d;
		}
		return 0;
	}
public:
	inline static int fnDrawShadow(const int &ID,CLight *(pL)){
		POINT3	posL;posL=pL->pos;
		double IL=pL->Il,KL=pL->K,Ir=pL->Ir,Ig=pL->Ig,Ib=pL->Ib;
		CLTrian* pLT=&(CBase::get()->trian);
		int szLT=pLT->fnGetSize();

		if(pL->type==1){
			CCamera* pCam=pL->cam;
			CMatrix mTransform;		pCam->fnGetMatrixTransform(mTransform);
			//mTransform.fnPrint(); system("pause");
			double ctgX=pCam->A.s1.x,ctgY=pCam->A.s2.y;
			double camF=-pCam->f, camN=-pCam->n;
			double camA=2/(camN-camF),camB=(-camF-camN)/(camN-camF);
			double *ZBuf=pL->zbuf->get_Z();
			POINT szZBuf; pL->zbuf->fnGet_sz(szZBuf);
			POINT hszZbuf; hszZbuf.x=szZBuf.x/2; hszZbuf.y=szZBuf.y/2;
			//std::cout<<"  szLT="<<szLT<<'\n';
			for(int tekTrian=0;tekTrian<szLT;++tekTrian){ 
				//std::cout<<"  fnDrawShadow: tekTrian="<<tekTrian<<'\n';
				CTrian3d *pTek=pLT->gP(tekTrian);
				POINT3 &vn0=*(pTek->vn0),&vn1=*(pTek->vn1),&vn2=*(pTek->vn2),	&v0=*(pTek->v0),&v1=*(pTek->v1),&v2=*(pTek->v2);
				POINT &vt0=*(pTek->vt0),&vt1=*(pTek->vt1),&vt2=*(pTek->vt2);
				POINT sz;	pTek->Img->fnGet_sz(sz);
				unsigned char *pUsed=pTek->Img->get_PChange(ID);
				unsigned char *pHelp=pTek->Img->get_PHelp(ID);
			//находим промежуток Y
				int yi=vt0.y,ya=yi;
				if(vt1.y>ya) ya=vt1.y;	if(vt1.y<yi) yi=vt1.y;
				if(vt2.y>ya) ya=vt2.y;	if(vt2.y<yi) yi=vt2.y;
				int dy=ya-yi+1;
			//выделяем память для X
				int *Xl=new int[dy],*Xr=new int[dy],*Pl=Xl,*Pr=Xr;
				POINT3 *POSl=new POINT3[dy],*pPOSl=POSl-yi,		*POSr=new POINT3[dy],*pPOSr=POSr-yi;
				POINT3 *NORMl=new POINT3[dy],*pNORMl=NORMl-yi,	*NORMr=new POINT3[dy],*pNORMr=NORMr-yi; 
				for(int y=yi;y<=ya;++y,++Pl,++Pr){*Pl=sz.x;*Pr=0;}
				Pl=Xl-yi;Pr=Xr-yi; 

				//std::cout<<"  yi:"<<yi<<"\t ya:"<<ya<<'\n';
				//system("pause");
			//растеризуем отрезок v0-v1
				{
					POINT a=vt0,b=vt1; POINT3 aPos=v0,bPos=v1; POINT3 aNorm=vn0,bNorm=vn1;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=fnRound(tx);	tp.y=fnRound(ty);
						//std::cout<<" tx:"<<tx<<" ty:"<<ty<<" tp.x:"<<tp.x<<" tp.y:"<<tp.y<<'\n';
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
			//растеризуем отрезок v1-v2
				{
					POINT a=vt1,b=vt2; POINT3 aPos=v1,bPos=v2; POINT3 aNorm=vn1,bNorm=vn2;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=fnRound(tx);	tp.y=fnRound(ty);
						//std::cout<<" tx:"<<tx<<" ty:"<<ty<<" tp.x:"<<tp.x<<" tp.y:"<<tp.y<<'\n';
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
			//растеризуем отрезок v0-v2
				{
					POINT a=vt0,b=vt2; POINT3 aPos=v0,bPos=v2; POINT3 aNorm=vn0,bNorm=vn2;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=fnRound(tx);	tp.y=fnRound(ty);
						//std::cout<<" tx:"<<tx<<" ty:"<<ty<<" tp.x:"<<tp.x<<" tp.y:"<<tp.y<<'\n';
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
				//system("pause");

				//std::cout<<"h"<<endl;
				sz.x=sz.x>>1;sz.y=sz.y>>1;
			//перебираем точки по горизонтали
			{
				int *pTexture=pTek->Img->get_PCopy(ID); POINT szTexture; pTek->Img->fnGet_sz(szTexture);
				unsigned char *pUsed=pTek->Img->get_PChange(ID);

				int *pImg;pTek->Img->fnGet_pM(pImg);
				POINT t;
				POINT3 vPl, vPr, vPd, vPt, vNl, vNr, vNd, vNt;
				for(t.y=yi;t.y<ya;++t.y){ //std::cout<<"yi ";
					vPt=vPl=pPOSl[t.y];		vPr=pPOSr[t.y];
					vNt=vNl=pNORMl[t.y];	vNr=pNORMr[t.y];
					vPd.x=vPr.x-vPl.x;		vPd.y=vPr.y-vPl.y;		vPd.z=vPr.z-vPl.z;
					vNd.x=vNr.x-vNl.x;		vNd.y=vNr.y-vNl.y;		vNd.z=vNr.z-vNl.z;
					int xl=Pl[t.y],xr=Pr[t.y];
					//std::cout<<"  y:"<<t.y<<"\t xl:"<<xl<<"\t xr:"<<xr<<'\n';
					int lenx=xr-xl;
					if(lenx==0) continue;
					vPd.x/=lenx;			vPd.y/=lenx;			vPd.z/=lenx;
					vNd.x/=lenx;			vNd.y/=lenx;			vNd.z/=lenx;
					for(t.x=xl;t.x<=xr;++t.x,
						vPt.x+=vPd.x,	vPt.y+=vPd.y,	vPt.z+=vPd.z,
						vNt.x+=vNd.x,	vNt.y+=vNd.y,	vNt.z+=vNd.z){	
//						pHelp[t.x+t.y*szTexture.x]=1;
						POINT3 vAB;																//A - источник света В - лимб
						vAB.x=posL.x-vPt.x;		vAB.y=posL.y-vPt.y;		vAB.z=posL.z-vPt.z;
						double cosAB=vAB.x*vNt.x+vAB.y*vNt.y+vAB.z*vNt.z;
						//std::cout<<"vAB: ";vAB.fnPrint();
						//std::cout<<"vNt: ";vNt.fnPrint();
						//std::cout<<" cosAB";
						if(cosAB<=0) continue;
						double lenN2=vNt.x*vNt.x+vNt.y*vNt.y+vNt.z*vNt.z;			//find1//
						double lenAB2=vAB.x*vAB.x+vAB.y*vAB.y+vAB.z*vAB.z;
						double lenAB=sqrt(lenAB2);
						//std::cout<<" lenN2||lenAB";
						if(lenN2==0 || lenAB2==0) continue;
						cosAB=sqrt(cosAB*cosAB/(lenN2*lenAB2));
						
						POINT4 pt4;pt4=vPt;
						//if(/*800/500 */ t.x==800 && t.y==500) {cout<<"!!!";
						//	cout<<"vPt.x="<<vPt.x<<"\t vPt.y="<<vPt.y<<"\t vPt.z="<<vPt.z<<'\n';
						//	cout<<"pt4.x="<<pt4.x<<"\t pt4.y="<<pt4.y<<"\t pt4.z="<<pt4.z<<'\n';
						//	cout<<"vPl.x="<<vPl.x<<"\t vPl.y="<<vPl.y<<"\t vPl.z="<<vPl.z<<'\n';
						//	cout<<"vPr.x="<<vPr.x<<"\t vPr.y="<<vPr.y<<"\t vPr.z="<<vPr.z<<'\n';
						//	cout<<"vPd.x="<<vPd.x<<"\t vPd.y="<<vPd.y<<"\t vPd.z="<<vPd.z<<'\n';
						//	
						//}
						pt4=mTransform.fnMultRight(pt4); pt4.fnDoNormal();
						POINT3 pt3;pt3=pt4;
						//std::cout<<" Z";
						//cout<<camN<<' '<<camF<<' ';system("pause");
						if(pt3.z>camN || pt3.z<camF) continue;		//отсечение по оси - Z
//						pHelp[t.x+t.y*szTexture.x]=1;
						//if(/*800/500 */ t.x==800 && t.y==500) {cout<<"!!!";
						//	cout<<"pt3.x="<<pt3.x<<"\t pt3.y="<<pt3.y<<"\t pt3.z="<<pt3.z<<'\n';
						//	cout<<"pt4.x="<<pt4.x<<"\t pt4.y="<<pt4.y<<"\t pt4.z="<<pt4.z<<'\n';
						//}
						pt3.x=-(pt3.x)*ctgX/(pt3.z);		pt3.y=-(pt3.y)*ctgY/(pt3.z);		pt3.z=camA*(pt3.z)+camB;
						//std::cout<<" XY";
						//pHelp[t.x+t.y*szTexture.x]=1;
//						pHelp[t.x+t.y*szTexture.x]=1;
//						pHelp[t.x+t.y*szTexture.x]=1;
						if(pt3.x>1+CGOption::dEpsLight || pt3.x<-1-CGOption::dEpsLight || pt3.y>1+CGOption::dEpsLight || pt3.y<-1-CGOption::dEpsLight) continue;	//отсечение по осям X,Y  //!!!change!!!
						//POINT pt2; pt2.x=(int)((pt3.x+1.0)*(double)hszZbuf.x); pt2.y=(int)((pt3.y+1.0)*(double)hszZbuf.y); //!!!change!!!
						POINT pt2; pt2.x=(int)(pt3.x*(double)hszZbuf.x)+hszZbuf.x; pt2.y=(int)(pt3.y*(double)hszZbuf.y)+hszZbuf.y;
						//std::cout<<" ZB\n";
						//std::cout<<"x:"<<pt2.x<<" y:"<<pt2.y<<" ZB:"<<ZBuf[pt2.x+pt2.y*sz.x]<<'|'<<pt3.z<<'\t';
						//if(/*800/500 */ t.x==800 && t.y==500) {cout<<"!!!";
						//	cout<<"pt3.x="<<pt3.x<<"\t pt3.y="<<pt3.y<<"\t pt3.z="<<pt3.z<<'\n';
						//	cout<<"pt2.x="<<pt2.x<<"\t pt2.y="<<pt2.y<<'\n';
						//	cout<<"ZBuf="<<ZBuf[pt2.x+pt2.y*szZBuf.x]<<'\n';

						//	system("pause");
						//}
						if(pt3.z<ZBuf[pt2.x+pt2.y*szZBuf.x]-CGOption::dEpsZBufCompare) continue;	//сверка по дальности с Z-буффером источника света
						pHelp[t.x+t.y*szTexture.x]=1;
						//std::cout<<"cos:"<<cosAB<<"\t IL:"<<IL<<"\t lenAB:"<<sqrt(lenAB2)<<"\t KL:"<<KL<<'\n';
						//std::cout<<(int)pUsed[t.x+t.y*szTexture.x]<<'\t';
						if(pUsed[t.x+t.y*szTexture.x]==0){//изменяем текстуру
							//std::cout<<"+\t"<<endl;
							pUsed[t.x+t.y*szTexture.x]=1;
							unsigned char *pD=(unsigned char *)(pImg+t.x+t.y*szTexture.x);
							unsigned char *pS=(unsigned char *)(pTexture+t.x+t.y*szTexture.x);
							//std::cout<<"cos:"<<cosAB<<"\t lenAB:"<<sqrt(lenAB2)<<"\t res:"<<(((double)*(pD+0))*cosAB*(IL/(sqrt(lenAB2)+KL)))<<'\n';
							*(pS+0)+=(unsigned char)(Ib*((double)*(pD+0))*cosAB*(IL/(sqrt(lenAB2)+KL)));
							*(pS+1)+=(unsigned char)(Ig*((double)*(pD+1))*cosAB*(IL/(sqrt(lenAB2)+KL)));
							*(pS+2)+=(unsigned char)(Ir*((double)*(pD+2))*cosAB*(IL/(sqrt(lenAB2)+KL)));
							//*(pS+3)+=(unsigned char)(((double)*(pD+3))*cosAB*(IL/(sqrt(lenAB2)+KL)));
						}
					}
					//system("pause");
				}
			}
			
			//std::cout<<"s"<<endl;

			//освобождение памяти
			//std::cout<<'!';
				delete[] Xl;		delete[] Xr;
			//std::cout<<'!';
				delete[] POSl;		delete[] POSr;
			//std::cout<<'!';
				delete[] NORMl;	delete[] NORMr;
			//std::cout<<"!\n";
			}//for(tekTrian)
		}//type==1
		if(pL->type==0){
			CCamera* pCam=pL->cam;
			CMatrix mTransform[6];
			double *zBuf[6];
			for(int i=0;i<6;++i){pCam[i].fnGetMatrixTransform(mTransform[i]); zBuf[i]=pL->zbuf[i].get_Z();}
			for(int i=0;i<6;++i){mTransform[i].fnPrint();}
			double ctgX=pCam->A.s1.x,ctgY=pCam->A.s2.y;
			double camF=-pCam->f, camN=-pCam->n;
			double camA=2/(camN-camF),camB=(-camF-camN)/(camN-camF);
			POINT szZBuf; pL->zbuf->fnGet_sz(szZBuf); int gszZbuf=szZBuf.x*szZBuf.y;
			POINT hszZbuf; hszZbuf.x=szZBuf.x/2; hszZbuf.y=szZBuf.y/2;
			//std::cout<<"  szLT="<<szLT<<'\n';
			for(int tekTrian=0;tekTrian<szLT;++tekTrian){ 
				//std::cout<<"  fnDrawShadow: tekTrian="<<tekTrian<<'\n';
				CTrian3d *pTek=pLT->gP(tekTrian);
				POINT3 &vn0=*(pTek->vn0),&vn1=*(pTek->vn1),&vn2=*(pTek->vn2),	&v0=*(pTek->v0),&v1=*(pTek->v1),&v2=*(pTek->v2);
				POINT &vt0=*(pTek->vt0),&vt1=*(pTek->vt1),&vt2=*(pTek->vt2);
				POINT sz;	pTek->Img->fnGet_sz(sz);
			//находим промежуток Y
				int yi=vt0.y,ya=yi;
				if(vt1.y>ya) ya=vt1.y;	if(vt1.y<yi) yi=vt1.y;
				if(vt2.y>ya) ya=vt2.y;	if(vt2.y<yi) yi=vt2.y;
				int dy=ya-yi+1;
			//выделяем память для X
				int *Xl=new int[dy],*Xr=new int[dy],*Pl=Xl,*Pr=Xr;
				POINT3 *POSl=new POINT3[dy],*pPOSl=POSl-yi,		*POSr=new POINT3[dy],*pPOSr=POSr-yi;
				POINT3 *NORMl=new POINT3[dy],*pNORMl=NORMl-yi,	*NORMr=new POINT3[dy],*pNORMr=NORMr-yi; 
				for(int y=yi;y<=ya;++y,++Pl,++Pr){*Pl=sz.x;*Pr=0;}
				Pl=Xl-yi;Pr=Xr-yi; 

				//std::cout<<"  yi:"<<yi<<"\t ya:"<<ya<<'\n';
				//system("pause");
				int *pTexture=pTek->Img->get_PCopy(ID); POINT szTexture; pTek->Img->fnGet_sz(szTexture);
				unsigned char *pUsed=pTek->Img->get_PChange(ID);
				unsigned char *pHelp=pTek->Img->get_PHelp(ID);
				//cout<<" sz          x:"<<sz.x<<"\t y:"<<sz.y<<'\n';
				//cout<<" szTexture   x:"<<szTexture.x<<"\t y:"<<szTexture.y<<'\n';
				//cout<<" vt0         x:"<<vt0.x<<"\t y:"<<vt0.y<<'\n';
				//cout<<" vt1         x:"<<vt1.x<<"\t y:"<<vt1.y<<'\n';
				//cout<<" vt2         x:"<<vt2.x<<"\t y:"<<vt2.y<<'\n';
				//system("pause");
			//растеризуем отрезок v0-v1
				{
					POINT a=vt0,b=vt1; POINT3 aPos=v0,bPos=v1; POINT3 aNorm=vn0,bNorm=vn1;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=(int)tx;	tp.y=(int)ty;
						//pHelp[tp.x+tp.y*sz.x]=1;
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
			//растеризуем отрезок v1-v2
				{
					POINT a=vt1,b=vt2; POINT3 aPos=v1,bPos=v2; POINT3 aNorm=vn1,bNorm=vn2;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=(int)tx;	tp.y=(int)ty;
						//pHelp[tp.x+tp.y*sz.x]=1;
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
			//растеризуем отрезок v0-v2
				{
					POINT a=vt0,b=vt2; POINT3 aPos=v0,bPos=v2; POINT3 aNorm=vn0,bNorm=vn2;
					if(a.y>b.y) {swap(a,b); swap(aPos,bPos); swap(aNorm,bNorm);}
					double dtx=b.x-a.x,dty=b.y-a.y;
					POINT3 dPos,dNorm;
					dPos.x=bPos.x-aPos.x;		dPos.y=bPos.y-aPos.y;		dPos.z=bPos.z-aPos.z;
					dNorm.x=bNorm.x-aNorm.x;	dNorm.y=bNorm.y-aNorm.y;	dNorm.z=bNorm.z-aNorm.z;
					int N=dtx; if(dty>N) N=dty; dtx/=(float)N; dty/=(float)N;
					dPos.x/=(float)N;				dPos.y/=(float)N;				dPos.z/=(float)N;
					dNorm.x/=(float)N;			dNorm.y/=(float)N;			dNorm.z/=(float)N;
					double tx=a.x,ty=a.y;
					POINT3 tPos=aPos,tNorm=aNorm;	
					POINT tp;
					//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
					for(int i=0;i<=N;++i,tx+=dtx,ty+=dty){
						tp.x=(int)tx;	tp.y=(int)ty;
						//pHelp[tp.x+tp.y*sz.x]=1;
						if(Pl[tp.y]>tp.x) {Pl[tp.y]=tp.x; pPOSl[tp.y]=tPos; pNORMl[tp.y]=tNorm;}
						if(Pr[tp.y]<tp.x) {Pr[tp.y]=tp.x; pPOSr[tp.y]=tPos; pNORMr[tp.y]=tNorm;}
						tPos.x+=dPos.x;		tPos.y+=dPos.y;		tPos.z+=dPos.z;
						tNorm.x+=dNorm.x;		tNorm.y+=dNorm.y;		tNorm.z+=dNorm.z;
						//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t dy="<<dy<<"\t uy="<<(tp.y-yi)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
					}
				}
				//system("pause");

				//std::cout<<"h"<<endl;
				sz.x=sz.x>>1;sz.y=sz.y>>1;
			//перебираем точки по горизонтали
			{

				int *pImg;pTek->Img->fnGet_pM(pImg);
				double *Zhelp[6];for(int i=0;i<6;++i) Zhelp[i]=pL->zbuf[i].get_Zhelp();
				POINT t;
				POINT3 vPl, vPr, vPd, vPt, vNl, vNr, vNd, vNt;
				for(t.y=yi;t.y<ya;++t.y){ //std::cout<<"yi ";
					vPt=vPl=pPOSl[t.y];		vPr=pPOSr[t.y];
					vNt=vNl=pNORMl[t.y];		vNr=pNORMr[t.y];
					vPd.x=vPr.x-vPl.x;		vPd.y=vPr.y-vPl.y;		vPd.z=vPr.z-vPl.z;
					vNd.x=vNr.x-vNl.x;		vNd.y=vNr.y-vNl.y;		vNd.z=vNr.z-vNl.z;
					int xl=Pl[t.y],xr=Pr[t.y];
					//std::cout<<"  y:"<<t.y<<"\t xl:"<<xl<<"\t xr:"<<xr<<'\n';
					//system("pause");
					int lenx=xr-xl;
					if(lenx!=0){
						vPd.x/=lenx;			vPd.y/=lenx;			vPd.z/=lenx;
						vNd.x/=lenx;			vNd.y/=lenx;			vNd.z/=lenx;
					}
					for(t.x=xl;t.x<=xr;++t.x){	
						//if(t.y>50) {std::cout<<"ok-";system("pause");}
						//std::cout<<(int)pHelp[t.x+t.y*sz.x]<<'-';
						//pHelp[t.x+t.y*szTexture.x]=1;//std::cout<<t.x<<'|'<<t.y<<'\t';

						//if(pImg[t.x+t.y*szTexture.y]==0x0000FFFF) cout<<"!!ok!!\n";
						//if(t.x==61 && t.y==szTexture.y-9){cout<<"!!!!!!!!!\n";
						//	std::cout<<pImg[t.x+(szTexture.y-t.y)*szTexture.x-1]<<endl;
						//	std::cout<<pImg[t.x+(szTexture.y-t.y)*szTexture.x+1]<<endl;
						//}
						POINT3 vAB;																//A - источник света В - лимб
						vAB.x=posL.x-vPt.x;		vAB.y=posL.y-vPt.y;		vAB.z=posL.z-vPt.z;
						double cosAB=vAB.x*vNt.x+vAB.y*vNt.y+vAB.z*vNt.z;
						//std::cout<<"vAB: ";vAB.fnPrint();
						//std::cout<<"vNt: ";vNt.fnPrint();
						//if(t.x==61 && t.y==9) cout<<" cosAB:"<<cosAB<<'\n';
						if(cosAB<=0) continue;
						//pHelp[t.x+t.y*szTexture.x]=1;
						//if(t.x==61 && t.y==9) cout<<"!!!!!!!!!\n";
						double lenN2=vNt.x*vNt.x+vNt.y*vNt.y+vNt.z*vNt.z;		//find2//
						double lenAB2=vAB.x*vAB.x+vAB.y*vAB.y+vAB.z*vAB.z;
						double lenAB=sqrt(lenAB2);
						//std::cout<<" lenN2||lenAB";
						if(lenN2==0 || lenAB2==0) continue;
						//pHelp[t.x+t.y*szTexture.x]=1;
						//if(t.x==61 && t.y==9) cout<<"!!!!!!!!!\n";
						cosAB=sqrt(cosAB*cosAB/(lenN2*lenAB2));

						for(int i=0;i<6;++i){
							POINT4 pt4;pt4=vPt;
							pt4=mTransform[i].fnMultRight(pt4); pt4.fnDoNormal();
							POINT3 pt3;pt3=pt4;
							//std::cout<<" Z";
							//cout<<camN<<' '<<camF<<' ';system("pause");
							if(pt3.z>camN || pt3.z<camF) continue;		//отсечение по оси - Z
							//pHelp[t.x+t.y*szTexture.x]=1;
							pt3.x=-(pt3.x)*ctgX/(pt3.z);		pt3.y=-(pt3.y)*ctgY/(pt3.z);		pt3.z=camA*(pt3.z)+camB;
							//std::cout<<" XY";
							//if(t.x==29 && t.y==2) {cout<<"29/2:  x,y:"<<pt3.x<<'\t'<<pt3.y<<'\n'; system("pause");}
							if(pt3.x>1+CGOption::dEpsLight || pt3.x<-1-CGOption::dEpsLight || pt3.y>1+CGOption::dEpsLight || pt3.y<-1-CGOption::dEpsLight) continue;	//отсечение по осям X,Y
							//pHelp[t.x+t.y*szTexture.x]=1;

							//std::cout<<"x:"<<pt3.x<<" y:"<<pt3.y<<'\t';
							POINT pt2; pt2.x=(int)(pt3.x*(double)hszZbuf.x)+hszZbuf.x; pt2.y=(int)(pt3.y*(double)hszZbuf.y)+hszZbuf.y;
							//std::cout<<" ZB\n";
							//std::cout<<"x:"<<pt2.x<<" y:"<<pt2.y<<'\n';
							//if(t.x==13 && t.y==8) {cout<<"13/8:"<<pt3.z<<'<'<<zBuf[i][pt2.x+pt2.y*szTexture.x]<<'\n'; system("pause");}
							/*if(t.y>=0 && t.y<=27 && pt3.z<zBuf[i][pt2.x+pt2.y*szZBuf.x]-0.00001){
								std::cout<<"fat t: "<<t.x<<"."<<t.y<<"\t pt3.z"<<pt3.z<<"\t zBuf:"<<zBuf[i][pt2.x+pt2.y*szZBuf.x]<<'\n';
							}
							*///std::cout<<"  szTexture: "<<szTexture.x<<' '<<szTexture.y<<'\n';
							//system("pause");
							//Zhelp[i][pt2.x+pt2.y*szZBuf.x]=pt3.z;

							//if(pt3.z>=zBuf[i][pt2.x+pt2.y*szZBuf.x]-0.0003) std::cout<<"fat t: "<<t.x<<"."<<t.y<<"\t pt3.z"<<pt3.z<<"\t zBuf:"<<zBuf[i][pt2.x+pt2.y*szZBuf.x]<<'\n';
							if(pt2.x>=szZBuf.x) pt2.x=szZBuf.x-1;	if(pt2.y>=szZBuf.y) pt2.y=szZBuf.y-1;
							if(pt2.x<0) pt2.x=0;	if(pt2.y<0) pt2.y=0;
							int tmp=pt2.x+pt2.y*szZBuf.x; //if(tmp>=gszZbuf) tmp=gszZbuf-1;
							pHelp[t.x+t.y*szTexture.x]=1;
							if(pt3.z<zBuf[i][tmp]-CGOption::dEpsZBufCompare) continue;	//сверка по дальности с Z-буффером источника света
							pHelp[t.x+t.y*szTexture.x]=1;
							//std::cout<<"cos:"<<cosAB<<"\t IL:"<<IL<<"\t lenAB:"<<sqrt(lenAB2)<<"\t KL:"<<KL<<'\n';
							//std::cout<<(int)pUsed[t.x+t.y*szTexture.x]<<'\t';
		 					if(pUsed[t.x+t.y*szTexture.x]==0){//изменяем текстуру
								//std::cout<<"+\t"<<endl;
								pUsed[t.x+t.y*szTexture.x]=1;
								unsigned char *pD=(unsigned char *)(pImg+t.x+t.y*szTexture.x);
								unsigned char *pS=(unsigned char *)(pTexture+t.x+t.y*szTexture.x);
								//std::cout<<"cos:"<<cosAB<<"\t lenAB:"<<sqrt(lenAB2)<<"\t res:"<<(((double)*(pD+0))*cosAB*(IL/(sqrt(lenAB2)+KL)))<<'\n';
								*(pS+0)+=(unsigned char)(Ib*((double)*(pD+0))*cosAB*(IL/(lenAB+KL)));
								*(pS+1)+=(unsigned char)(Ig*((double)*(pD+1))*cosAB*(IL/(lenAB+KL)));
								*(pS+2)+=(unsigned char)(Ir*((double)*(pD+2))*cosAB*(IL/(lenAB+KL)));
								//*(pS+3)+=(unsigned char)(((double)*(pD+3))*cosAB*(IL/(sqrt(lenAB2)+KL)));
							}
						}//for(i...)
						vPt.x+=vPd.x;	vPt.y+=vPd.y;	vPt.z+=vPd.z;
						vNt.x+=vNd.x;	vNt.y+=vNd.y;	vNt.z+=vNd.z;
					}
				}
				//system("pause");
			}
			
			//std::cout<<"s"<<endl;

			//освобождение памяти
			//std::cout<<'!';
				delete[] Xl;		delete[] Xr;
			//std::cout<<'!';
				delete[] POSl;		delete[] POSr;
			//std::cout<<'!';
				delete[] NORMl;	delete[] NORMr;
			//std::cout<<"!\n";
			}//for(tekTrian)
		}//type==0
		CBaseMaterial::getPBM()->fnChangeDown(ID);
		return 0;
	}
};

#endif