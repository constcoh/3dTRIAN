#ifndef _MATERIAL_H_
#define _MATERIAL_H_

class CBaseMaterial{
public:
	struct el{
		el* pN;
		char *szName;
		CImage Img,ImgNs;
		el():pN(NULL),szName(NULL){}
		int setName(const char *name){
			if(szName!=NULL) delete[] szName;
			int l=strlen(name);
			szName=new char[l+1];
			strcpy(szName,name);
			return 0;
		}
		~el(){if(szName!=NULL){delete[] szName; szName=NULL;}}
	};
private:
	int iLen;
	el *pF,*pL;
public:
	int fnMakeCopy(const int &iCopyCount){
		if(pF==NULL) return -1;
		el *pT=pF;
		do{
			std::cout<<"  fnCreateCopy("<<pT->szName<<")\n";
			pT->Img.fnCreateCopy(iCopyCount);
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}	
	int fnDeleteCopy(){
		if(pF==NULL) return -1;
		el *pT=pF;
		do{
			pT->Img.fnDeleteCopy();
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnMegreCopy(){
		if(pF==NULL) return -1;
		el *pT=pF;
		do{
			pT->Img.fnMergeCopy();
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnSaveCopy(const char *floder){
		if(pF==NULL) return -1;
		char filename[1024]; filename[0]=0;
		strcpy(filename,floder);
		int l=strlen(filename);
		if(filename[l-1]!='\\') {filename[l]='\\'; ++l; filename[l]=0;} strcat(filename,"00.bmp");
		el *pT=pF;
		do{
			pT->Img.fnSaveCopies(filename,l+1);
			++filename[l+1]; filename[l+1]=0;
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnSaveChange(const char *floder){
		if(pF==NULL) return -1;
		char filename[1024]; filename[0]=0;
		strcpy(filename,floder);
		int l=strlen(filename);
		if(filename[l-1]!='\\') {filename[l]='\\'; ++l; filename[l]=0;} strcat(filename,"00.bmp");
		el *pT=pF;
		do{
			pT->Img.fnSaveChange(filename,l+1);
			++filename[l]; filename[l+1]='0';
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnSaveHelp(const char *floder){
		if(pF==NULL) return -1;
		char filename[1024]; filename[0]=0;
		strcpy(filename,floder);
		int l=strlen(filename);
		if(filename[l-1]!='\\') {filename[l]='\\'; ++l; filename[l]=0;} strcat(filename,"00.bmp");
		el *pT=pF;
		do{
			pT->Img.fnSaveHelp(filename,l+1);
			++filename[l]; filename[l+1]='0';
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnChangeDown(const int &ID){
		if(pF==NULL) return -1;
		el *pT=pF;
		do{
			pT->Img.fnChangeDown(ID);
			pT=pT->pN;
		}while(pT!=NULL);		
		return 0;
	}

	int fnMultIaLast(const double &Ia){
		if(pF==NULL) return -1;
		el *pT=pF;
		do{
			std::cout<<"  fnMultIaCopy("<<pT->szName<<")\n";
			pT->Img.fnMult(Ia);
			pT=pT->pN;
		}while(pT!=NULL);
		return 0;
	}
	int fnGet_pFirst(el *(&dest)){dest=pF; return 0;}
	int fnGet_pLast (el *(&dest)){dest=pL; return 0;}
	int getLen(){return iLen;}
	int fnPushMaterial(el *material){
		if(pF==NULL){
			pF=pL=material;
		}else{
			pL->pN=material; pL=pL->pN;
		}
		++iLen;
		return 0;
	}
	~CBaseMaterial(){
		el *t;
		while(pF!=NULL){t=pF->pN; delete pF; pF=t;}
		pL=NULL;
	}
	int fnSaveMaterials(const char *floder=NULL){
		char namefile[1024]; namefile[0]=0;
		char nameend[5]; strcpy(nameend,".bmp");
		char *pName, *pEnd;
		int len;
		if(floder==NULL){pName=&(namefile[0]); len=0;}else{
			strcpy(namefile,floder); len=strlen(namefile); pName=&(namefile[len]);
			if(*(pName-1)!='\\'){	*pName='\\'; ++pName;	++len;	}
		}
		el* tek=pF;
		if(pF==NULL) return 0;
		int j;
		do{
			strcpy(pName,tek->szName);
			j=strlen(tek->szName); pEnd=pName+j;
			strcpy(pEnd,nameend);
			tek->Img.fnSaveBMP(namefile);
			tek=tek->pN;
		}while(tek!=NULL);

		return 0;
	}
//одиночка
private:
	static CBaseMaterial *pBM;
	CBaseMaterial():iLen(0),pF(NULL),pL(NULL){}
public:
	static CBaseMaterial *getPBM(){if(pBM==NULL) pBM=new CBaseMaterial(); return pBM;}
};
CBaseMaterial *CBaseMaterial::pBM;
#endif