#ifndef _LISTARRAY_H_
#define _LISTARRAY_H_

#define _LISTARRAY_QUICK_

template<typename T>
class CListArray{
private:
	struct el{
		el *pNext;
		int iLen;
		T* M;
		el():pNext(NULL),M(NULL),iLen(0){}
		int fnSetSize(int count){if(M!=NULL) delete[] M; M=new T[count]; iLen=count;}
		el(int count):pNext(NULL){M=new T[count]; iLen=count;}
		~el(){
			if(M!=NULL){delete[] M; M=NULL;}
			if(pNext!=NULL){delete pNext; pNext=NULL;}
		}
	};
	el* pS,*pL;
	int iGSize,iT;
	int iKB,iLFirst;
public:
	CListArray(int iLenFirst=512,int iKoefBig=2):iT(0),iKB(iKoefBig),iLFirst(iLenFirst){pS=pL=new el(iLFirst); iGSize=iLFirst;}
	~CListArray(){if(pS!=NULL) {delete pS; pL=pS=NULL;}}
	int get(T& d,int iIndex){
		if(iIndex<0 || iIndex>=iT) return 1;
		el* tek=pS;
		while(iIndex>=pS->iLen) iIndex-=pS->iLen;
		d=pS->M[iIndex];
		return 0;
	}
	int getP(T* (&d),int iIndex){
		if(iIndex<0 || iIndex>=iT) return 1;
		el* tek=pS;
		while(iIndex>=tek->iLen) {iIndex-=tek->iLen; tek=tek->pNext;}
		d=&(tek->M[iIndex]);
		return 0;
	}
	T   g(int iIndex){el* tek=pS;	while(iIndex>=tek->iLen) {iIndex-=tek->iLen; tek=tek->pNext;}		return tek->M[iIndex];}
	T* gP(int iIndex){el* tek=pS;	while(iIndex>=tek->iLen) {iIndex-=tek->iLen; tek=tek->pNext;}		return &(tek->M[iIndex]);}
	int push(T &d){
		int t=iT;
		el* tek=pS;
		while(t>tek->iLen) {t-=tek->iLen; tek=tek->pNext;}
		if(t==tek->iLen){
			if(tek->pNext==NULL){pL=tek->pNext=new el((tek->iLen)*iKB); iGSize+=tek->pNext->iLen;}
			t-=tek->iLen; tek=tek->pNext;
		}
		tek->M[t]=d;
		++iT;
		return 0;
	}
	int fnGetSize(){return iT;}
	int fnGetMemSize(){return iGSize;}
};

#endif