#ifndef _OBJECT_H_
#define _OBJECT_H_

struct CObjectGroup{
	char *szName;
	bool isGroup;
};

class CObject:public CObjectGroup{
public:
	struct el{	el *pN;	CTrian3d *trian;
		el(CTrian3d *Trian3d=NULL):pN(NULL),trian(Trian3d){}
	};
private:
	int iLen;
	el* pF,*pL;
	char *szMaterial;
public:
	CObject():iLen(0),pF(NULL),pL(NULL),szMaterial(NULL){szName=NULL; isGroup=false;}
	int fnSetName(const char *src){
		if(szName!=NULL) delete[] szName;
		int l=strlen(src); szName=new char[l+1];
		strcpy(szName,src);
		return 0;
	}
	int fnGetPName(char *pStr){
		if(szName==NULL) return 1;
		pStr=szName; return 0;
	}
	int fnSetMaterial(const char *src){
		if(szMaterial!=NULL) delete[] szMaterial;
		int l=strlen(src); szMaterial=new char[l+1];
		strcpy(szMaterial,src);
		return 0;

	}
	int fnGetPMaterial(char *(&pStr)){
		if(szMaterial==NULL) return 1;
		pStr=szMaterial; return 0;
	}
	int getLen(){return iLen;}
	int fnGet_pFirst(el *(&dest)){dest=pF; return 0;}
	int fnGet_pLast (el *(&dest)){dest=pL; return 0;}
	~CObject(){
		el* t;	
		while(pF!=NULL){t=pF->pN; delete pF->trian; delete pF; pF=t;}
		if(szMaterial!=NULL) {delete[] szMaterial; szMaterial=NULL;}
		if(szName!=NULL) {delete[] szName; szName=NULL;}
	}
	int fnPushTrian(CTrian3d *Trian3d){
		if(pF==NULL){
			pF=pL=new el(Trian3d);
		}else{
			pL->pN=new el(Trian3d); pL=pL->pN;
		}
		++iLen;
		return 0;
	}
};

class CGroup:public CObjectGroup{
public:
	struct el{	el *pN;	CObjectGroup *pObj;
		el(CObjectGroup *Obj=NULL):pN(NULL),pObj(Obj){}
	};
private:
	int iLen;
	el *pF,*pL;
	char *szMaterial;
public:
	CGroup():iLen(0),pF(NULL),pL(NULL){szName=NULL; isGroup=true;}
	int fnSetName(const char *src){int l=strlen(src); if(szName!=NULL) delete[] szName; szName=new char[l]; strcpy(szName,src); return 0;}
	int fnGetName(char *dest){if(szName==NULL) return 1; dest=szName; return 0;}
	int fnSetMaterial(const char *src){
		if(szMaterial!=NULL) delete[] szMaterial;
		int l=strlen(src); szMaterial=new char[l+1]; 
		strcpy(szMaterial,src);
		return 0;

	}
	int fnGetPMaterial(char *pStr){
		if(szMaterial==NULL) return 1;
		pStr=szName; return 0;
	}
	int getLen(){return iLen;}
	int fnGet_pFirst(el *(&dest)){dest=pF; return 0;}
	int fnGet_pLast (el *(&dest)){dest=pL; return 0;}
	~CGroup(){
		el* t;	
		while(pF!=NULL){t=pF->pN; delete pF->pObj; delete pF; pF=t;}
		if(szMaterial!=NULL) {delete[] szMaterial; szMaterial=NULL;}
		if(szName!=NULL) {delete[] szName; szName=NULL;}
	}
	int fnPushObject(CObjectGroup *pObjectGroup){
		if(pF==NULL){
			pF=pL=new el(pObjectGroup);
		}else{
			pL->pN=new el(pObjectGroup); pL=pL->pN;
		}
		++iLen;
		return 0;
	}
};

struct CBaseObject{
private:
	static CBaseObject *pBO;
	CBaseObject(){		pRoot=new CGroup;		pRoot->isGroup=true;	}
public:
	CObjectGroup *pRoot;
	static CBaseObject *getBaseObj(){if(pBO==NULL) pBO=new CBaseObject; return pBO;}
	~CBaseObject(){
		if(pRoot!=NULL){delete pRoot; pRoot=NULL;}
	}
};
CBaseObject *CBaseObject::pBO=NULL;

struct CByPassObj{
	CGroup *tek;
	CGroup::el *child;
	CByPassObj *last;
	CByPassObj(CGroup *Tek=NULL,CGroup::el *Child=NULL,CByPassObj *Last=NULL):tek(Tek),child(Child),last(Last){}
};
#endif