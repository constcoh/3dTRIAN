#ifndef _EASYSTACK_H_
#define _EASYSTACK_H_

template <typename T>
class CEasyStack{
public:
	struct el{	el* pLast;	T* pVal;
		el(el* pLAST=NULL,T* pVAL=NULL):pLast(pLAST),pVal(pVAL){}
	};
private:
	el* pFirst;
	int iLen;
public:
	CEasyStack():pFirst(NULL),iLen(0){}
	~CEasyStack(){
		el* pTek;
		while(pFirst!=NULL){pTek=pFirst; pFirst=pFirst->pLast; delete pTek;}
		iLen=0;
	}
	int getLen(){return iLen;}
	int push(T* src){
		el *pN=new el(pFirst,src); pFirst=pN; ++iLen;
		return 0;
	}
	int pop(T* (&dest)){
		if(pFirst==NULL) return 1;
		el *pD=pFirst; pFirst=pFirst->pLast; dest=pD->pVal;
		delete pD; --iLen;
		return 0;
	}
	int top(T* (&dest)){
		if(pFirst==NULL) return 1;
		dest=pFirst->pVal;
		return 0;
	}
};

#endif