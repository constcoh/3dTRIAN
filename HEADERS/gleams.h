#ifndef _GLEAMS_H_
#define _GLEAMS_H_

class CGleams{
private:
	static double dInfinity;
public:
	inline static bool fnCheckInfKoef(const POINT3 &d){
		if(d.x>CGOption::dInfKoefLight) return false;
		if(d.y>CGOption::dInfKoefLight) return false;
		if(d.z>CGOption::dInfKoefLight) return false;
		return true;
	}

	//фкнкция проверки луча на пересечение с однит лимбом
	inline static double fnCheckOne(const CTrian3d *(tr),const POINT3 (&vPos), const POINT3 (&vDirect)){
		//считаем геометрическую нормаль треугольника и проверяем с ней на ориентир
		{
			POINT3 vN;
			vN.x=(tr->vn0->x+tr->vn1->x+tr->vn2->x)/3.0;
			vN.y=(tr->vn0->y+tr->vn1->y+tr->vn2->y)/3.0;
			vN.z=(tr->vn0->z+tr->vn1->z+tr->vn2->z)/3.0;
			//cout<<"vN; ";vN.fnPrint();
			//cout<<"vD; "<<vDirect.x<<' '<<vDirect.y<<' '<<vDirect.z<<'\n';

			if(vN.x*vDirect.x+vN.y*vDirect.y+vN.z*vDirect.z>=0) return -1;
		}
		POINT3 vOA,vOB,vOC,vOM,vAB,vAC;
		POINT3 A,B,C;
		A=*(tr->v0); B=*(tr->v1); C=*(tr->v2);
		vAB.x=B.x-A.x;			vAB.y=B.y-A.y;			vAB.z=B.z-A.z;
		vAC.x=C.x-A.x;			vAC.y=C.y-A.y;			vAC.z=C.z-A.z;
		vOA.x=A.x-vPos.x;		vOA.y=A.y-vPos.y;		vOA.z=A.z-vPos.z;		
		vOB.x=vOA.x+vAB.x;		vOB.y=vOA.y+vAB.y;		vOB.z=vOA.z+vAB.z;		
		vOC.x=vOA.x+vAC.x;		vOC.y=vOA.y+vAC.y;		vOC.z=vOA.z+vAC.z;
		//cout<<"A: ";A.fnPrint();
		//cout<<"B: ";B.fnPrint();
		//cout<<"C: ";C.fnPrint();
		//cout<<"OA: ";vOA.fnPrint();
		//cout<<"OB: ";vOB.fnPrint();
		//cout<<"OC: ";vOC.fnPrint();
		//cout<<"vD: "<<vDirect.x<<' '<<vDirect.y<<' '<<vDirect.z<<'\n';;

		//проверяем по векторным произведениям попадания треугольника на прямую
		{
			bool b1=true,b2=true,b3=true;
			if(POINT3::fnSProis(POINT3::fnVProis(vOA,vOB),vDirect)<0) b1=false;
			if(POINT3::fnSProis(POINT3::fnVProis(vOB,vOC),vDirect)<0) b2=false;
			if(POINT3::fnSProis(POINT3::fnVProis(vOC,vOA),vDirect)<0) b3=false;
			//cout<<b1<<' '<<b2<<' '<<b3<<'\n';
			if(!(b1 & b2 & b3 || !b1 & !b2 & !b3)) return -2;
		}
		//считаем коэффициент дальности
		POINT3 vN=POINT3::fnVProis(vAB,vAC);vN.fnNormal();
		double sOAxN=POINT3::fnSProis(vOA,vN),sDxN=POINT3::fnSProis(vDirect,vN);
		return sOAxN/sDxN;
	}
	//функция, которая находит ближайший лимб и, если он оказался ближе ближайшего источника света, то тек. поз. перекидывается на него
	inline static int fnFind(CLTrian *pLT,int &sz,POINT3 &vPos,POINT3 &vDirect,double &dNear,double &dFar, POINT3 &koefColor,double &lenS,double &fullLen){
		//cout<<"vPos: ";vPos.fnPrint();
		double length=dInfinity,len=-1; int Index=-1;
		//нормируем vDirect
		{double l=sqrt(vDirect.x*vDirect.x+vDirect.y*vDirect.y+vDirect.z*vDirect.z);
			vDirect.x/=l;	vDirect.y/=l;	vDirect.z/=l;	
		}
		//cout<<" L:";
		for(int i=0;i<sz;++i){
			len=fnCheckOne(pLT->gP(i),vPos,vDirect);
			//cout<<len<<' ';
			if(len>0) if((len<length)) {length=len; Index=i;}
		}
		//cout<<"Length:"<<length;
		//cout<<'\n';
		if(Index>=0 && length<lenS){// если нашли пересечение ближе всех источников света, то нужно повернуть vDirect и домножить koef
			vDirect.x*=length;		vDirect.y*=length;		vDirect.z*=length;		
			//cout<<"vDirect*L: "; vDirect.fnPrint();
			CTrian3d *tr=pLT->gP(Index);
			POINT3 A;A=*(tr->v0);
			POINT3 vAB,vAC,vAM;
			vAB.x=tr->v1->x-A.x;	vAB.y=tr->v1->y-A.y;	vAB.z=tr->v1->z-A.z;
			vAC.x=tr->v2->x-A.x;	vAC.y=tr->v2->y-A.y;	vAC.z=tr->v2->z-A.z;
			vAM.x=vDirect.x-A.x;	vAM.y=vDirect.y-A.y;	vAM.z=vDirect.z-A.z;	
			POINTD coord; //x,y in [0, 1]
			double detZ=vAB.x*vAC.y-vAB.y*vAC.x;
			coord.x=(vAM.x*vAC.y-vAM.y*vAC.x)/detZ;
			coord.y=(vAB.x*vAM.y-vAB.y*vAM.x)/detZ;
			POINT cd,szT; tr->Img->fnGet_sz(szT);
			cd.x=int(coord.x*(tr->vt1->x-tr->vt0->x)+coord.y*(tr->vt2->x-tr->vt0->x))+tr->vt0->x;
			cd.y=int(coord.x*(tr->vt1->y-tr->vt0->y)+coord.y*(tr->vt2->y-tr->vt0->y))+tr->vt0->y;
			if(cd.x>=szT.x) cd.x=szT.x-1;					if(cd.y>=szT.y) cd.y=szT.y-1;					
			// исправляем koefColor
			{
				COLORREF TNA; int *pMNA; tr->ImgNs->fnGet_pM(pMNA);
				TNA=pMNA[cd.x+cd.y*szT.x];
				koefColor.x*=(float)((TNA&0x000000FF))/255.0;
				koefColor.y*=(float)((TNA&0x0000FF00)>>8)/255.0;
				koefColor.z*=(float)((TNA&0x00FF0000)>>16)/255.0;
			}
			//увеличиваем пройденный путь fullLen
			{
				fullLen+=sqrt(vDirect.x*vDirect.x+vDirect.y*vDirect.y+vDirect.z*vDirect.z);
			}
			// исправляем vPos
			vPos.x+=vDirect.x;		vPos.y+=vDirect.y;		vPos.z+=vDirect.z;		
			// исправляем vDirect
			POINT3 vN;
			vN.x=(coord.x*(tr->vn1->x-tr->vn0->x)+coord.y*(tr->vn2->x-tr->vn0->x))+tr->vn0->x;
			vN.y=(coord.x*(tr->vn1->y-tr->vn0->y)+coord.y*(tr->vn2->y-tr->vn0->y))+tr->vn0->y;
			vN.z=(coord.x*(tr->vn1->z-tr->vn0->z)+coord.y*(tr->vn2->z-tr->vn0->z))+tr->vn0->z;
			double sDxN=POINT3::fnSProis(vDirect,vN); if(sDxN<0) {/*cout<<'M';*/ sDxN=-sDxN;}
			vN.x*=sDxN;				vN.y*=sDxN;				vN.z*=sDxN;				
			vDirect.x+=2*vN.x;		vDirect.y+=2*vN.y;		vDirect.z+=2*vN.z;
			//cout<<"vDirectNew: "; vDirect.fnPrint();
			return 0;
		}
		return -1;
	}
	//функция, которая находит минимальный по дальности источник света и возвращает расстояние до него
	inline static double fnFindLight(CLLight *pLL,int &sz,POINT3 &vPos,POINT3 &vDirect,double &dNear,double &dFar,CLight *(&pOtv)){
		//нормируем vDirect
		{double l=sqrt(vDirect.x*vDirect.x+vDirect.y*vDirect.y+vDirect.z*vDirect.z);
			vDirect.x/=l;	vDirect.y/=l;	vDirect.z/=l;	
		}
		pOtv=NULL; double lenS=dInfinity*dInfinity;
		for(int i=0;i<sz;++i){
			CLight *pL=pLL->g(i);
			POINT3 vL; vL=pL->pos;
			POINT3 AB,BC,vH;
			AB.x=vL.x-vPos.x;		AB.y=vL.y-vPos.y;		AB.z=vL.z-vPos.z;
			double sABxD=vDirect.x*AB.x+vDirect.y*AB.y+vDirect.z*AB.z;
			vH.x=vPos.x+vDirect.x*sABxD;		vH.y=vPos.y+vDirect.y*sABxD;		vH.z=vPos.z+vDirect.z*sABxD;
			BC.x=vH.x-vL.x;			BC.y=vH.y-vL.y;			BC.z=vH.z-vL.z;		
			//cout<<"BC: ";BC.fnPrint();
			if(BC.x*BC.x+BC.y*BC.y+BC.z*BC.z<pL->Rst2){//луч пересекается с сферой источника света
				double lenSi=AB.x*AB.x+AB.y*AB.y+AB.z*AB.z; 
				//cout<<"lenSi:"<<lenSi<<'\n';
				//cout<<"lenS:"<<lenS<<'\n';

				if(lenSi<lenS){//рассматриваемый источник оказался ближе
					pOtv=pL; lenS=lenSi;
				}
			}
		}
		return lenS;
	}

	//функция, просматривающая путь одного луча, и возвращающая добавочный цвет
	inline static int fnSeeWay(CLTrian *pLT,int &szTr,CLLight *pLL,int &szLi,POINT3 &vPos,POINT3 &vDirect){
		POINT3 koefColor; koefColor.x=koefColor.y=koefColor.z=1.0;
		double fullLen=0;
		double dNear=0,dFar=0;
		bool Persection=true;
		int sz_per=0;
		while(Persection & (!fnCheckInfKoef(koefColor))){
			++sz_per;
			CLight* pLOtv=NULL;
			double lenLight=CGleams::fnFindLight(pLL,szLi,vPos,vDirect,dNear,dFar,pLOtv);
//			if(sz_per==3) cout<<'!';
			int isFindTriangle=fnFind(pLT,szTr,vPos,vDirect,dNear,dFar,koefColor,lenLight,fullLen);
			//cout<<"Res Find:"<<isFindTriangle<<' '<<lenLight<<'\n';
			//cout<<"FullLen: "<<fullLen<<'\n';
			if(isFindTriangle==-1){
				//cout<<"L";
				if(lenLight<dInfinity){// если лимба на луче не нашли, но нашли источник света
//					cout<<"S find\n";
					fullLen+=sqrt(lenLight);
//					cout<<fullLen<<'\n';
					int otv; double K=pLOtv->K,Il=pLOtv->Il;
					//cout<<"K="<<K<<"\t Il="<<Il<<'\n';
					//cout<<"Ir="<<pLOtv->Ir<<'\t'<<"Ig="<<pLOtv->Ig<<'\t'<<"Ib="<<pLOtv->Ib<<'\n';
					int r=int(((pLOtv->Ir)*Il/(K+fullLen)*koefColor.z)*256.0); if(r>255) r=255;
					int g=int(((pLOtv->Ig)*Il/(K+fullLen)*koefColor.y)*256.0); if(g>255) g=255;
					int b=int(((pLOtv->Ib)*Il/(K+fullLen)*koefColor.z)*256.0); if(b>255) b=255;
					if(sz_per==1){
						r=pLOtv->Ir*255.0;
						g=pLOtv->Ig*255.0;
						b=pLOtv->Ib*255.0;

					}
					otv=(r<<16)|(g<<8)|(b);
//					cout<<"r:"<<r<<"g:"<<g<<"b:"<<b<<'\n';
					return otv;
				}else Persection=false;
			}
		}
		//cout<<sz_per;
		return 0;
	}

	static int fnDrawGleams(){
		CCamera *pCam= CCamera::getCam();
		CZBuffer *pZBuf= CZBuffer::get(); POINT szZBuf; pZBuf->fnGet_sz(szZBuf);
		int *pM=pZBuf->get_M();
		CLTrian* pLT=&(CBase::get()->trian);

		POINT3 posC;posC=pCam->pos;
		POINT3 vLU,vRD,dH,dV,vTek,vLeft;
		POINT sz,t;
		{

			POINT3 vBack;vBack=pCam->w;POINT3 vUp;vUp=pCam->v; vUp.fnMultIt(-1); POINT3 vRight;vRight=pCam->u; double Near=pCam->n; //vUp.fnMult(Near); vRight.fnMult(Near);
			POINT3 vCenter;
			vCenter.x=/*posC.x-*/-vBack.x*Near;		vCenter.y=/*posC.y-*/-vBack.y*Near;		vCenter.z=/*posC.z-*/-vBack.z*Near;
			double upper=tan((pCam->a)/2)*Near,lefter=tan((pCam->b)/2)*Near;
			//cout<<"upper: "<<upper<<'\n';
			//cout<<"lefter: "<<lefter<<'\n';
			vLU.x=vCenter.x+upper*vUp.x-vRight.x*lefter;	vLU.y=vCenter.y+upper*vUp.y-vRight.y*lefter;	vLU.z=vCenter.z+upper*vUp.z-vRight.z*lefter;	
			vRight.x*=2;	vRight.y*=2;	vRight.z*=2;			vUp.x=-2*vUp.x;	vUp.y=-2*vUp.y;	vUp.z=-2*vUp.z;	
			vLeft=vLU;
			//vToLeft.x=-vRight.x;				vToLeft.y=-vRight.y;				vToLeft.z=-vRight.z;					
			vRD.x=vLU.x+vRight.x+vUp.x;			vRD.y=vLU.y+vRight.y+vUp.y;			vRD.z=vLU.z+vRight.z+vUp.z;			
			pZBuf->fnGet_sz(sz);
			//cout<<sz.x<<' '<<sz.y<<'\n';
			double	d=upper/(double(sz.y)); dV.x=vUp.x*d;	dV.y=vUp.y*d;	dV.z=vUp.z*d;	
			d=lefter/(double(sz.x)); dH.x=vRight.x*d;	dH.y=vRight.y*d;	dH.z=vRight.z*d;	
			vTek=vLU;
			//cout<<"vUp: ";vUp.fnPrint();
			//cout<<"vRg: ";vRight.fnPrint();
			//system("pause");
		}

		{
			CBase *pBase=CBase::get();
			CLTrian *pLT=&(pBase->trian); int szLT=pLT->fnGetSize();
			CLLight *pLL=&(pBase->light); int szLL=pLL->fnGetSize();
			cout<<"dV: "; dV.fnPrint();
			cout<<"dH: "; dH.fnPrint();
			//system("pause");
			for(t.y=0;t.y<sz.y;++t.y,vLeft.x+=dV.x,vLeft.y+=dV.y,vLeft.z+=dV.z){
				
				vTek.x=vLeft.x;			vTek.y=vLeft.y;			vTek.z=vLeft.z;
				//cout<<"vLeft: ";vLeft.fnPrint(); 
				//system("pause");
				//cout<<t.y<<'\n';
				for(t.x=0;t.x<sz.x;++t.x,vTek.x+=dH.x,vTek.y+=dH.y,vTek.z+=dH.z){
//					if(t.x==150 && t.y==0){
					POINT3 posT,directT;
					posT=posC; directT=vTek; 
					//cout<<"vdirectT: ";directT.fnPrint(); 
					int ColorAdd=fnSeeWay(pLT,szLT,pLL,szLL,posT,directT);
					if(ColorAdd!=0) {
//						cout<<"ColorAdd:"<<ColorAdd<<"\t x="<<t.x<<"\t y="<<t.y<<'\n';
						int D=pM[t.x+t.y*sz.x];
						int bs=0x000000FF&D, bd=0x000000FF&ColorAdd; bs=bs+bd; if(bs>0x000000FF) bs=0x000000FF;
						int gs=0x0000FF00&D, gd=0x0000FF00&ColorAdd; gs=gs+gd; if(gs>0x0000FF00) gs=0x0000FF00;
						int rs=0x00FF0000&D, rd=0x00FF0000&ColorAdd; rs=rs+rd; if(rs>0x00FF0000) rs=0x00FF0000;
						D=bs|rs|gs; 
						pM[t.x+t.y*sz.x]=D;
					}
					//cout<<sz.x<<' '<<sz.y<<'\n';
					//if(t.x==t.y && t.y==150) system("pause");
//					}
				}
			}
		}

		return 0;
	};
};

double CGleams::dInfinity=10e50;

#endif