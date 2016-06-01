#ifndef _CIMAGE_H_
#define _CIMAGE_H_

void SaveBuf0(COLORREF* buf,POINT params,const char *filename){
	std::ofstream out;
	out.open(filename);
	for(int y=0;y<params.y;++y){
		for(int x=0;x<params.x;++x) {out<<(((int)*((unsigned char*)buf+0)==0)?0:1); ++buf;}
		out<<'\n';
	}
	out.close();
}
void SaveBuf1(COLORREF* buf,POINT params,const char *filename){
	std::ofstream out;
	out.open(filename);
	for(int y=0;y<params.y;++y){
		for(int x=0;x<params.x;++x) {out<<(((int)*((unsigned char*)buf+1)==0)?0:1); ++buf;}
		out<<'\n';
	}
	out.close();
}
void SaveBuf2(COLORREF* buf,POINT params,const char *filename){
	std::ofstream out;
	out.open(filename);
	for(int y=0;y<params.y;++y){
		for(int x=0;x<params.x;++x) {out<<(((int)*((unsigned char*)buf+2)==0)?0:1); ++buf;}
		out<<'\n';
	}
	out.close();
}
void SaveBuf3(COLORREF* buf,POINT params,const char *filename){
	std::ofstream out;
	out.open(filename);
	for(int y=0;y<params.y;++y){
		for(int x=0;x<params.x;++x) {out<<(((int)*((unsigned char*)buf+3)==0)?0:1); ++buf;}
		out<<'\n';
	}
	out.close();
}


class CImage{
protected:
	int *M;
	POINT sz;
	int **pCopy; int iCopyCount;
	unsigned char **pChange;
	unsigned char **pHelp;

public:
	int fnChangeDown(const int &ID){
		if(pChange==NULL) return -1;
		unsigned char *pT=pChange[ID];
		int gsz=sz.x*sz.y;
		for(int i=0;i<gsz;++i,++pT) *pT=0; 
		return 0;
	}
	int fnSaveChange(char *filename,const int indNumber){
		CImage Img;
		Img.fnSetSize(sz);
		int *pImg;Img.fnGet_pM(pImg);
		unsigned char *pC;
		for(int k=0;k<iCopyCount;++k){
			pC=pChange[k];
			for(int x=0;x<sz.x;++x) for(int y=0;y<sz.y;++y)	pImg[x+y*sz.x]=(pC[x+y*sz.x]==0)?0x00FFFFFF:0;
			Img.fnSaveBMP(filename); ++filename[indNumber];
		}
		return 0;
	}
	int fnSaveHelp(char *filename,const int indNumber){
		CImage Img;
		Img.fnSetSize(sz);
		int *pImg;Img.fnGet_pM(pImg);
		unsigned char *pC;
		for(int k=0;k<iCopyCount;++k){
			pC=pHelp[k];
			for(int x=0;x<sz.x;++x) for(int y=0;y<sz.y;++y)	pImg[x+y*sz.x]=(pC[x+y*sz.x]==0)?0x00FFFFFF:0;
			Img.fnSaveBMP(filename); ++filename[indNumber];
		}
		return 0;
	}
	int fnCreateCopy(const int (&CopyCount)){
		if(M==NULL || pCopy!=NULL) return -1;
		iCopyCount=CopyCount;
		pCopy=new int*[iCopyCount]; pChange=new unsigned char*[iCopyCount]; pHelp=new unsigned char*[iCopyCount];
		int **pC=pCopy; unsigned char **pH=pChange,**pHp=pHelp; 
		int gsz=sz.x*sz.y;
		for(int i=0;i<iCopyCount;++i,++pC,++pH,++pHp){*pC=new int[gsz]; memset(*pC,0,gsz*sizeof(int)); *pH=new unsigned char[gsz]; memset(*pH,0,gsz*sizeof(unsigned char)); *pHp=new unsigned char[gsz]; memset(*pHp,0,gsz*sizeof(unsigned char));}
		return 0;
	}
	int fnDeleteCopy(){
		if(pCopy==NULL) return -1;
		int **pC=pCopy;
		for(int i=0;i<iCopyCount;++i,++pC) delete[] *pC;
		delete[] pCopy; pCopy=NULL;
		if(pChange!=NULL){
			unsigned char **pH=pChange;
			for(int i=0;i<iCopyCount;++i,++pH) delete[] *pH;
			delete[] pChange; pChange=NULL;
			pChange=NULL;
		}
		if(pHelp!=NULL){
			unsigned char **pH=pHelp;
			for(int i=0;i<iCopyCount;++i,++pH) delete[] *pH;
			delete[] pHelp; pHelp=NULL;
			pHelp=NULL;
		}
		iCopyCount=0;
		return 0;
	}
	int* get_PCopy(const int &iNumber){
		if(iCopyCount==0) return NULL;
		if(iNumber<0 || iNumber>=iCopyCount) return NULL;
		return pCopy[iNumber];
	}
	unsigned char *get_PChange(const  int &iNumber){
		if(iCopyCount==0) return NULL;
		if(iNumber<0 || iNumber>=iCopyCount) return NULL;
		return pChange[iNumber];		
	}
	unsigned char *get_PHelp(const  int &iNumber){
		if(iCopyCount==0) return NULL;
		if(iNumber<0 || iNumber>=iCopyCount) return NULL;
		return pHelp[iNumber];		
	}
	int fnMult(const double &koef){
		std::cout<<"  fnMult()\n";
		std::cout<<"  iCopyCount:"<<iCopyCount<<" KOEF="<<koef<<'\n';
		if(pCopy==NULL) return -1;
		int gsz=sz.x*sz.y*4;
		memcpy(pCopy[iCopyCount-1],M,gsz);
		unsigned char *pT=(unsigned char *)pCopy[iCopyCount-1];
		for(int i=0;i<gsz;++i,++pT) *pT=(unsigned char)(((double)*pT)*koef);
		return 0;
	}
	int fnMergeCopy(){
		if(M==NULL || iCopyCount==0) return -1;
		int gsz=sz.x*sz.y*4;
		int **pC=pCopy;
		unsigned char *pM,*pT;
		int tmp;
		memset(M,0,gsz);
		for(int j=0;j<iCopyCount;++j,++pC){
			pT=(unsigned char *)*pC; pM=(unsigned char *)M;
			for(int i=0;i<gsz;++i,++pT,++pM){
				if((tmp=*pT+*pM)<256) *pM=tmp;
			}
		}
		return 0;
	}
	CImage():M(0){sz.x=sz.y=0; iCopyCount=0; pCopy=NULL;}
	~CImage(){		 fnDeleteCopy();	if(M!=NULL){delete[] M; M=NULL; sz.x=sz.y=NULL;}}
	int fnClear(){	fnDeleteCopy();	if(M!=NULL){delete[] M; M=NULL; sz.x=sz.y=NULL;} return 0;}
	int fnLoadBMP(const char *filename){
		cout<<"fnLoadBMP("<<filename<<")\n";
		this->fnClear();

		BITMAPINFOHEADER bi;
		BITMAPFILEHEADER bf;
		FILE *in=NULL;	in=fopen(filename,"rb");
		if(in==NULL) return 1;
		//cout<<"   file open\n";
		int tmp;
		WORD uc;
		fread(&(bf.bfType		),1,2,in);	//bfType
		fread(&(bf.bfSize		),4,1,in);	//bfSize
		fread(&(bf.bfReserved1	),4,1,in);	//bfReserved
		fread(&(bf.bfOffBits	),4,1,in);	//bfOffBits
		fread(&(bi.biSize			),4,1,in);   //biSize
		fread(&(bi.biWidth			),4,1,in);	//biWidth
		fread(&(bi.biHeight			),4,1,in);	//biHeight
		fread(&(bi.biPlanes			),2,1,in);	//biPanels
		fread(&(bi.biBitCount  	    ),2,1,in);	//biBitCount
		fread(&(bi.biCompression	),4,1,in);	//biCompression
		fread(&(bi.biSizeImage		),4,1,in);	//biSizeImage
		fread(&(bi.biXPelsPerMeter	),4,1,in);	//biXPelsPerMeter
		fread(&(bi.biYPelsPerMeter	),4,1,in);	//biYPelsPerMeter
		fread(&(bi.biClrUsed		),4,1,in);	//biClrUsed
		fread(&(bi.biClrImportant	),4,1,in);	//biClrImprotant
		if(bf.bfType!=0x4D42) { fclose(in); return 1;}
		if(bf.bfOffBits!=54 ||bi.biBitCount!=24 || bi.biCompression!=0 || bi.biPlanes!=1) {fclose(in); return 1;}
		//cout<<"   parameters ok\n";
		sz.x=(int)bi.biWidth; sz.y=(int)bi.biHeight;
		M=new int[sz.x*sz.y]; memset(M,0,sz.x*sz.y*4);
		if(sz.y>=0){

			int add=0; while((sz.x*3+add)%4!=0) ++add;
			int size=sz.x*sz.y;
			int *buf=M;
			int zero=0,read=0;
			unsigned char *tm=(unsigned char*)buf;
			for(int i=0;i<size;++i) {
				fread(tm+0,1,1,in);
				fread(tm+1,1,1,in);
				fread(tm+2,1,1,in);
					//*(tm+3)=NULL;
				read+=3;
				if(add>0) {if((i+1)%(sz.x)==0) fread(&zero,1,add,in); read+=add;}
				tm+=4;
			}
			//std::cout<<"   read:"<<read<<"\n";
		}
		fclose(in);
		cout<<"loaded: sz.x="<<sz.x<<"\t sz.y="<<sz.y<<'\n';
		//SaveBuf0((COLORREF*)M,sz,"load0.txt");
		//SaveBuf1((COLORREF*)M,sz,"load1.txt");
		//SaveBuf2((COLORREF*)M,sz,"load2.txt");
		//SaveBuf3((COLORREF*)M,sz,"load3.txt");
		//cout<<(M[(sz.y-1)*sz.x]>>24)<<'\t'<<(int)(M[(sz.y-1)*sz.x]&0x00FF0000>>16)<<'\t'<<(int)(M[(sz.y-1)*sz.x]&0x0000FF00>>8)<<'\t'<<(int)(M[(sz.y-1)*sz.x]&0x000000FF)<<'\n';
		return 0;
	}
	int fnSaveBMP(const char *filename){
		cout<<"fnSaveBMP("<<filename<<")\n";
		if(M==NULL) return 0;
		BITMAPINFO bmpInfo;
		memset(&bmpInfo.bmiHeader,0,sizeof(bmpInfo.bmiHeader));
		bmpInfo.bmiHeader.biSize=sizeof(bmpInfo);
		bmpInfo.bmiHeader.biWidth=(LONG)sz.x;
		bmpInfo.bmiHeader.biHeight=(LONG)sz.y;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biCompression = 0;
		bmpInfo.bmiHeader.biSizeImage = sz.x*sz.y * 32;
		FILE *out=NULL;
		out=fopen(filename,"wb");
		if(out==NULL) return 1;
		int tmp;
		WORD uc;
		int add=0; while((sz.x*3+add)%4!=0) ++add;
		fwrite(&"BM",1,2,out);	//bfType
		fwrite(&(tmp=(unsigned int)(54+(sz.x*3+add)*sz.y		 )),4,1,out);	//bfSize
		fwrite(&(tmp=(unsigned int)(0							 )),4,1,out);	//bfReserved
		fwrite(&(tmp=(unsigned int)(54						     )),4,1,out);	//bfOffBits
		fwrite(&(tmp=(unsigned int)(40							 )),4,1,out);   //biSize
		fwrite(&(tmp=(int)( sz.x					 )),4,1,out);	//biWidth
		fwrite(&(tmp=(int)( sz.y					 )),4,1,out);	//biHeight
		fwrite(&(uc=(WORD)(1				 )),2,1,out);	//biPanels
		fwrite(&(uc=(WORD)(24				 )),2,1,out);	//biBitCount
		fwrite(&(tmp=(unsigned int)(0					 )),4,1,out);	//biCompression
		fwrite(&(tmp=(unsigned int)((sz.x*3+add)*sz.y	 )),4,1,out);	//biSizeImage
		fwrite(&(tmp=(int)(0					 )),4,1,out);	//biXPelsPerMeter
		fwrite(&(tmp=(int)(0					 )),4,1,out);	//biYPelsPerMeter
		fwrite(&(tmp=(unsigned int)(0					 )),4,1,out);	//biClrUsed
		fwrite(&(tmp=(unsigned int)(0					 )),4,1,out);	//biClrImprotant
		int size=sz.x*sz.y;
		unsigned char tm=0,*buf=(unsigned char*)M;
		int zero=0,written=0;
		for(int i=0;i<size;++i) {
			tm=*(buf+0); fwrite(&tm,1,1,out);
			tm=*(buf+1); fwrite(&tm,1,1,out);
			tm=*(buf+2); fwrite(&tm,1,1,out); written+=3;
			if(add>0) {if((i+1)%sz.x==0) fwrite(&zero,1,add,out); written+=add;}
			buf+=4;
		}
		if(add>0) {fwrite(&zero,1,add,out); written+=add;}
		cout<<"saved: sz.x="<<sz.x<<"\t sz.y="<<sz.y<<'\t';
		std::cout<<"written:"<<written<<"\n";
		fclose(out);

	}
	int fnGet_pM(int *(&Array)){Array=M; return 0;}
	int fnGet_sz(POINT (&size)){size=sz; return 0;}
	int fnSaveDC(HDC &dc,HBITMAP &btm){
		BITMAPINFO bmpInfo;
		memset(&bmpInfo.bmiHeader,0,sizeof(bmpInfo.bmiHeader));
		bmpInfo.bmiHeader.biSize=sizeof(bmpInfo);
		bmpInfo.bmiHeader.biWidth=sz.x;
		bmpInfo.bmiHeader.biHeight=sz.y;
		bmpInfo.bmiHeader.biPlanes = 1;
		bmpInfo.bmiHeader.biBitCount = 32;
		bmpInfo.bmiHeader.biCompression = 0;
		bmpInfo.bmiHeader.biSizeImage = 0;
		int er=GetLastError();
		std::cout<<"er="<<er<<'\n';
		SetDIBits(dc,btm,0,sz.y,M,&bmpInfo,DIB_RGB_COLORS);
		 er=GetLastError();
		std::cout<<"er="<<er<<'\n';
		GetDIBits(dc,btm,0,sz.y,M,&bmpInfo,DIB_RGB_COLORS);
		return 0;
	}
	int fnVerticalReflect(){
		if(M==NULL) return 0;
		int nst=sz.y/2;

		int *su=&M[0],*sd=&M[(sz.y-1)*sz.x],*u,*d,tmp;
		for(int i=0;i<nst;++i,su+=sz.x,sd-=sz.x){
			u=su; d=sd;
			for(int k=0;k<sz.x;++k,++u,++d){tmp=*u;*u=*d;*d=tmp;}
		}
		return 0;
	}
	int fnVerticalReflect1(){
		if(M==NULL) return 0;
		int *nM=new int[sz.x*sz.y],*dest=nM,*srcl=&M[(sz.y-1)*sz.x],*src;
		for(int i=0;i<sz.y;++i,srcl-=sz.x){
			src=srcl;
			for(int j=0;j<sz.x;++j,++dest,++src) *dest=*src;
		}
		delete[] M; M=nM;
	}
	int fnDrawTrian2D(CTrian2d tr){
	//находим промежуток Y
		int yi=tr.v0.y,ya=yi;
		if(tr.v1.y>ya) ya=tr.v1.y;	if(tr.v1.y<yi) yi=tr.v1.y;
		if(tr.v2.y>ya) ya=tr.v2.y;	if(tr.v2.y<yi) yi=tr.v2.y;
		int dy=ya-yi+1;
	//выделяем память для X
		int *Xl=new int[dy],*Xr=new int[dy],*Pl=Xl,*Pr=Xr;
		for(int y=yi;y<=ya;++y,++Pl,++Pr){*Pl=sz.x;*Pr=0;}
		Pl=Xl-yi;Pr=Xr-yi;
	//растеризуем отрезок v0-v1
		{
			POINT a=tr.v0,b=tr.v1;
			if(a.y>b.y) swap(a,b);
			double dvx=b.x-a.x,dvy=b.y-a.y; 
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
			double tx=a.x,ty=a.y;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
				if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
			}
		}
	//растеризуем отрезок v1-v2
		{
			POINT a=tr.v1,b=tr.v2;
			if(a.y>b.y) swap(a,b);
			double dvx=b.x-a.x,dvy=b.y-a.y; 
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
			double tx=a.x,ty=a.y;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
				if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
			}
		}
	//растеризуем отрезок v0-v2
		{
			POINT a=tr.v0,b=tr.v2;
			if(a.y>b.y) swap(a,b);
			double dvx=b.x-a.x,dvy=b.y-a.y; 
			int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
			double tx=a.x,ty=a.y;
			POINT tp;
			//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
			for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
				tp.x=(int)tx;	tp.y=(int)ty;
				if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
				if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
				//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
			}
		}
	//рисуем на M
		int *Ml=M+sz.x*yi,*Mt;
		for(int y=yi;y<=ya;++y,Ml+=sz.x){
			int left=Pl[y],right=Pr[y];
			Mt=Ml+left;
			//std::cout<<"l,r="<<left<<' '<<right<<'\n';
			for(int x=left;x<=right;++x,++Mt) *Mt=tr.color;
		}
		delete[] Xl;
		delete[] Xr;
		return 0;
	}
	int fnDrawTrian2D(CTrian2d *trian, int count){
		CTrian2d tr;
		for(int gi=0;gi<count;++gi){
		//находим промежуток Y
			int yi=tr.v0.y,ya=yi;
			if(tr.v1.y>ya) ya=tr.v1.y;	if(tr.v1.y<yi) yi=tr.v1.y;
			if(tr.v2.y>ya) ya=tr.v2.y;	if(tr.v2.y<yi) yi=tr.v2.y;
			int dy=ya-yi+1;
		//выделяем память для X
			int *Xl=new int[dy],*Xr=new int[dy],*Pl=Xl,*Pr=Xr;
			for(int y=yi;y<=ya;++y,++Pl,++Pr){*Pl=sz.x;*Pr=0;}
			Pl=Xl-yi;Pr=Xr-yi;
		//растеризуем отрезок v0-v1
			{
				POINT a=tr.v0,b=tr.v1;
				if(a.y>b.y) swap(a,b);
				double dvx=b.x-a.x,dvy=b.y-a.y; 
				int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
				double tx=a.x,ty=a.y;
				POINT tp;
				//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
				for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
					tp.x=(int)tx;	tp.y=(int)ty;
					if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
					if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
					//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
				}
			}
		//растеризуем отрезок v1-v2
			{
				POINT a=tr.v1,b=tr.v2;
				if(a.y>b.y) swap(a,b);
				double dvx=b.x-a.x,dvy=b.y-a.y; 
				int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
				double tx=a.x,ty=a.y;
				POINT tp;
				//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
				for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
					tp.x=(int)tx;	tp.y=(int)ty;
					if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
					if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
					//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
				}
			}
		//растеризуем отрезок v0-v2
			{
				POINT a=tr.v0,b=tr.v2;
				if(a.y>b.y) swap(a,b);
				double dvx=b.x-a.x,dvy=b.y-a.y; 
				int N=dvx; if(dvy>N) N=dvy; dvx/=(float)N; dvy/=(float)N;
				double tx=a.x,ty=a.y;
				POINT tp;
				//std::cout<<"a:"<<a.x<<'\t'<<a.y<<"\tb:"<<b.x<<'\t'<<b.y<<"\n";
				for(int i=0;i<=N;++i,tx+=dvx,ty+=dvy){
					tp.x=(int)tx;	tp.y=(int)ty;
					if(Pl[tp.y]>tp.x) Pl[tp.y]=tp.x;
					if(Pr[tp.y]<tp.x) Pr[tp.y]=tp.x;
					//std::cout<<"  tx="<<int(tx)<<"\t ty="<<int(ty)<<"\t Pl="<<Pl[tp.y]<<"\t Pr="<<Pr[tp.y]<<"\n";
				}
			}
		//рисуем на M
			int *Ml=M+sz.x*yi,*Mt;
			for(int y=yi;y<=ya;++y,Ml+=sz.x){
				int left=Pl[y],right=Pr[y];
				Mt=Ml+left;
				//std::cout<<"l,r="<<left<<' '<<right<<'\n';
				for(int x=left;x<=right;++x,++Mt) *Mt=tr.color;
			}
			delete[] Xl;
			delete[] Xr;

		}
		return 0;
	}

	int fnSetSize(const POINT &size){
		fnClear();
		sz.x=size.x;	sz.y=size.y;
		M=new int[sz.x*sz.y]; memset(M,0,sz.x*sz.y);
		return 0;
	}
	int fnSaveCopies(char *floder,const int indNumber){
		if(iCopyCount<=0) return 0;
		std::cout<<"    iCopyCount="<<iCopyCount<<'\n';
		for(int i=0;i<iCopyCount;++i){
			swap(M,pCopy[i]);
			fnSaveBMP(floder); 
			swap(M,pCopy[i]); ++floder[indNumber];
		}
		return 0;
	}
};


#endif