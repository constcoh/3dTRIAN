#ifndef _OBJREADER_H_
#define _OBJREADER_H_

class CObjReader{
public:
	static int readlight(const char *filename);
	static int readobj(const char *filename);
	static int readmtl(const char *filename);
	static bool isEqual(const char *d1,const char *d2,const int len){
		for(int i=0;i<len;++i) if(d1[i]!=d2[i]) return false;
		return true;
	}
	static bool isEqual(const char *d1,const char *d2){
		int l=strlen(d1),l2=strlen(d2); if(l>l2) l=l2;
		for(int i=0;i<l;++i,++d1,++d2) if(*d1!=*d2) return false;
		return true;

	}
	static int setPointerImgToTrians();
	static int setPImg(CObject *pO,CBaseMaterial *pBM);
};


typedef CEasyStack<CObjectGroup> STOG;

int CObjReader::readobj(const char *filename){
	if(CGOption::check)std::cout<<"fnReadObj: "<<filename<<endl;
	STOG stog;
	CBaseObject* pBaseO=CBaseObject::getBaseObj();
	CObject *tO=NULL; CGroup *tG=(CGroup*)pBaseO->pRoot;
	{//найдём *tO в основной группе по отсутствующему имени 
		CGroup::el *tmpGel=NULL; tG->fnGet_pFirst(tmpGel);
		char *pNameObject=NULL;
		if(tmpGel!=NULL)
		do{
			pNameObject=tmpGel->pObj->szName;
			if(pNameObject==NULL) break;
		}while(tmpGel->pN!=NULL);
		if(pNameObject==NULL) {tO=new CObject; tO->isGroup=false; tG->fnPushObject(tO);}else	tO=(CObject*)tmpGel->pObj;
	}
	//откроем на чтение файл
	std::ifstream in;
	in.open(filename);
	//переменные чтения
	double koef;
	char buf[1024], fc;
	int i,j,k,iIndex;
	char *ptc;
	CGroup *pNG=NULL;
	POINT3 p3; POINT p2; CTrian3d trian; trian.Img=NULL; bool isN,isT;
	CL2d *VT;	CL3d *V,*VN;	CLTrian *TR;
	{CBase *base=CBase::get(); V=&(base->v); VN=&(base->vn); VT=&(base->vt); TR=&(base->trian);}//достаём указатели на с-массивы
	int iSzV=V->fnGetSize(),iSzVN=VN->fnGetSize(),iSzVT=VT->fnGetSize();

	//читаем построчно
	while(!in.eof()){
		in.getline(buf,1023); fc=buf[0]; //std::cout<<"strlen(buf)="<<strlen(buf)<<"\t"<<(int)buf[strlen(buf)]<<'\n';
		//std::cout<<"  buf:"<<buf<<'\n';
		//system("pause");
		switch(fc){
			case('v'):{//новый вектор
				fc=buf[1];
				switch(fc){
					case('\t'):
					case(' '):{//новый 3D вектор
						ptc=buf+2; i=2;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.x=atof(ptc);	while(*ptc!=' '&&*ptc!='\t') ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.y=atof(ptc);	while(*ptc!=' '&&*ptc!='\t') ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.z=atof(ptc);	while(*ptc!=' '&&*ptc!='\t'&&*ptc!=0) ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc;
						if(*ptc!=0){koef=atof(ptc); if(koef!=0){ p3.x/=koef; p3.y/=koef; p3.z/=koef;}}
						//std::cout<<"  V:"<<p3.x<<"\t "<<p3.y<<"\t "<<p3.z<<'\n';
						V->push(p3);
					}break;
					case('t'):{//новый текстурный вектор
						//cout<<"  strlen(buf)="<<strlen(buf)<<" buf="<<buf<<'\n';
						ptc=buf+2; i=2;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.x=atof(ptc);	while(*ptc!=' '&&*ptc!='\t') ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.y=atof(ptc);	while(*ptc!=' '&&*ptc!='\t'&&*ptc!=0) ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc;
						if(*ptc!=0){koef=atof(ptc); if(koef!=0){ p3.x/=koef; p3.y/=koef;}}
						p2.x=(int)p3.x; p2.y=(int)p3.y;
						VT->push(p2);
					}break;
					case('n'):{//новый вектор нормали
						ptc=buf+2; i=2;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.x=atof(ptc);	while(*ptc!=' '&&*ptc!='\t') ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.y=atof(ptc);	while(*ptc!=' '&&*ptc!='\t') ++ptc;
						while(*ptc==' '||*ptc=='\t') ++ptc; p3.z=atof(ptc);	while(*ptc!=' '&&*ptc!='\t'&&*ptc!=0) ++ptc;
						koef=sqrt(p3.x*p3.x+p3.y*p3.y+p3.z*p3.z);if(koef!=0){  p3.x/=koef; p3.y/=koef; p3.z/=koef;}
						//std::cout<<"  VN:"<<p3.x<<"\t "<<p3.y<<"\t "<<p3.z<<'\n';
						VN->push(p3);
					}break;
				}				
			}break;
			case('m'):{//запуск чтения библиотеки текстур
				if(!CObjReader::isEqual("tllib ",buf+1,6)) break;
				ptc=buf+7; i=7; while(*ptc==' ') {++ptc; ++i;} while(*ptc!=' ' && *ptc!=0) ++ptc; *ptc=0;
				CObjReader::readmtl(buf+i);
			}break;
			case('u'):{//найдено указание на название текстуры
				if(!CObjReader::isEqual("semtl ",buf+1,6)) break;
				ptc=buf+7; i=7; while(*ptc==' ') {++ptc; ++i;} while(*ptc!=' ' && *ptc!=0) ++ptc; *ptc=0;
				tO->fnSetMaterial(buf+i);
				//std::cout<<"  "<<buf+i<<"\n";
			}break;
			case('f'):{//начли новае лицо
				//cout<<"face:\n";
				//Первый вектор
				isT=isN=false;
				ptc=buf+1; i=1; while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
				if(*ptc=='/') isT=true; *ptc=0; iIndex=atoi(buf+i); trian.v0=V->gP(iSzV+iIndex-1);
				//cout<<" 1: v="<<iIndex<<'\t';
				if(isT){//читаем текстуру
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
					if(*ptc=='/') isN=true; *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vt0=VT->gP(iSzVT+iIndex-1);}					
					//cout<<" t="<<iIndex<<'\t';
				}
				if(isN){//читаем нормаль
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!=0){++ptc; ++j;} *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vn0=VN->gP(iSzVN+iIndex-1);}
					//cout<<" n="<<iIndex;
				}
				//cout<<'\n';
				//Второй вектор
				isT=isN=false;
				++ptc; i=++j; while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
				if(*ptc=='/') isT=true; *ptc=0; iIndex=atoi(buf+i); trian.v1=V->gP(iSzV+iIndex-1);
				//cout<<" 2: v="<<iIndex<<'\t';
				if(isT){//читаем текстуру
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
					if(*ptc=='/') isN=true; *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vt1=VT->gP(iSzVT+iIndex-1);}					
					//cout<<" t="<<iIndex<<'\t';
				}
				if(isN){//читаем нормаль
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!=0){++ptc; ++j;} *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vn1=VN->gP(iSzVN+iIndex-1);}
					//cout<<" n="<<iIndex;
				}
				//cout<<'\n';
				//Третьий вектор
				isT=isN=false;
				++ptc; i=++j; while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
				if(*ptc=='/') isT=true; *ptc=0; iIndex=atoi(buf+i); trian.v2=V->gP(iSzV+iIndex-1);
				//cout<<" 3: v="<<iIndex<<'\t';
				if(isT){//читаем текстуру
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!='/' && *ptc!=0){++ptc; ++j;}
					if(*ptc=='/') isN=true; *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vt2=VT->gP(iSzVT+iIndex-1);}					
					//cout<<" t="<<iIndex<<'\t';
				}
				if(isN){//читаем нормаль
					++ptc; i=++j;while(*ptc==' '){++ptc; ++i;} j=i; while(*ptc!=' ' && *ptc!=0){++ptc; ++j;} *ptc=0;
					if(j>i){iIndex=atoi(buf+i); trian.vn2=VN->gP(iSzVN+iIndex-1);}
					//cout<<" n="<<iIndex;
				}
				//cout<<'\n';
				//system("pause");
				TR->push(trian); tO->fnPushTrian(TR->gP(TR->fnGetSize()-1));
			}break;
			case('o'):{//новый объект
				i=1; ptc=buf+1; while(*ptc==' ') {++ptc;++i;}
				tO=new CObject; tO->isGroup=false; tO->fnSetName(buf+i);
				cout<<"New Object:"<<buf+i<<'\n';
				tG->fnPushObject(tO);
			}break;
			case('g'):{//новая группа объектов
				i=1; ptc=buf+1; while(*ptc==' ') {++ptc;++i;}
				pNG=new CGroup; pNG->isGroup=true; pNG->fnSetName(buf+i);
				cout<<" New Group:"<<buf+i<<'\n';
				tO=new CObject; tO->isGroup=false;	pNG->fnPushObject(tO);
				tG=(CGroup*)pBaseO->pRoot; tG->fnPushObject(pNG); tG=pNG;
			}break;
		}
	}
	in.close();
	return 0;
}


int CObjReader::readmtl(const char *filename){
	std::cout<<"CObjReader::readmtl("<<filename<<")\n";
	char buf1[1024];buf1[0]=0;
	char buf2[1024];buf2[0]=0;

	std::ifstream in;
	in.open(filename);
	CBaseMaterial::el *tmp=NULL;
	CBaseMaterial* pBM=CBaseMaterial::getPBM();
	int j,k,j1,k1;
	while(!in.eof()){ 
		buf1[0]=0;
		in.getline(buf1,1023);
		//std::cout<<"buf1:"<<buf1<<'\n';
		if(buf1[0]=='n'){
			if(buf1[1]!= 'e' || buf1[2]!= 'w' || buf1[3]!= 'm' || buf1[4]!= 't' || buf1[5]!= 'l') continue;
			j1=6; while(buf1[j1]==' ') ++j1; k1=j1; while(buf1[k1]!=' ' && buf1[k1]!=0) ++k1; buf1[k1]=0;
			tmp=new CBaseMaterial::el; tmp->setName(buf1+j1);

			buf2[0]=0;
			while(!in.eof()){
				in.getline(buf2,1023);
				if(CObjReader::isEqual(buf2,"map_Ka",6)){
					j=6; while(buf2[j]==' ') ++j; k=j; while(buf2[k]!=' ' && buf2[k]!=0) ++k; buf2[k]=0;
					tmp->Img.fnLoadBMP(buf2+j);
					cout<<"Ka\n";
				}
				if(CObjReader::isEqual(buf2,"map_Ns",6)){
					j=6; while(buf2[j]==' ') ++j; k=j; while(buf2[k]!=' ' && buf2[k]!=0) ++k; buf2[k]=0;
					tmp->ImgNs.fnLoadBMP(buf2+j);
					cout<<"Ns\n";
				}				
			}
			std::cout<<"  MaterialName:"<<(buf1+j1)<<'\t';
			std::cout<<"   TextureName:"<<(buf2+j)<<'\n';
			//system("pause");
			pBM->fnPushMaterial(tmp);	

		}
	}
	in.close();
	return 0;
}

int CObjReader::setPointerImgToTrians(){
	cout<<"CObjReader::setPImg()\n";
	CBaseMaterial *pBM=CBaseMaterial::getPBM();
	CObjectGroup * pOG;
	CEasyStack<CByPassObj> st;
	CBaseObject *baseobject=CBaseObject::getBaseObj();
	CByPassObj *tek=new CByPassObj((CGroup*)baseobject->pRoot),*ntek=NULL; tek->tek->fnGet_pFirst(tek->child);
	while(tek->child!=NULL || tek->last!=NULL){
		
		std::cout<<"  :";if(tek->tek->szName!=NULL) std::cout<<tek->tek->szName;cout<<":";
		if(tek->child!=NULL){//просматириваем потомка
			std::cout<<"child:";
		//		system("pause");
			pOG=tek->child->pObj;
		//		system("pause");
			if(pOG->isGroup){//в потомке записана группа
				std::cout<<"group:";
				ntek=new CByPassObj((CGroup *)pOG,NULL,tek); ntek->tek->fnGet_pFirst(ntek->child);
				st.push(tek); tek->child=tek->child->pN; tek=ntek;
				if(tek->tek->szName!=NULL) cout<<tek->tek->szName; cout<<":\n";
				continue;
			}else{//в потомке записан объект
				std::cout<<"object:";
				CObjReader::setPImg((CObject*)(pOG),pBM); tek->child=tek->child->pN;
				continue;
			}
		}else{//потомков больше нет, смотрим на родителя
			std::cout<<":";
			if(tek->last!=NULL){
				std::cout<<"parent:";
				ntek=tek; tek=tek->last; delete ntek;
				if(tek->tek->szName!=NULL) cout<<tek->tek->szName; cout<<":\n";
				continue;
			}
		}
	}
	delete tek;
	return 0;
}

int CObjReader::setPImg(CObject *pO,CBaseMaterial *pBM){
	char *pTekName=NULL; pO->fnGetPMaterial(pTekName);
	cout<<"See object:";if(pO->szName!=NULL) cout<<pO->szName;cout<<":texture=";if(pTekName!=NULL) cout<<pTekName; cout<<":\n";
	if(pTekName==NULL) return 1;
	CImage *M=NULL,*MNs=NULL;
	{//ищем указатель на текстуру
		CBaseMaterial::el *pEl; pBM->fnGet_pFirst(pEl);
		while(pEl!=NULL){
			std::cout<<"  Txt:";if(pEl->szName!=NULL) cout<<pEl->szName; cout<<'\n';
			if(CObjReader::isEqual(pEl->szName,pTekName)){	M=&(pEl->Img);	MNs=&(pEl->ImgNs); }
			pEl=pEl->pN;
		}
	}
	if(M!=NULL){//проставляем указатель на текстуру для лиц
		CObject::el *pEl; pO->fnGet_pFirst(pEl);
		for(;pEl!=NULL;pEl=pEl->pN) {pEl->trian->Img=M; pEl->trian->ImgNs=MNs;}
	}else{//текстура не найдена
		std::cout<<"  Could not find texture:"; if(pTekName!=NULL) std::cout<<pTekName;std::cout<<'\n';
	}
	return 0;
}

int CObjReader::readlight(const char *filename){
	const double standart_a=1.57059;
	std::cout<<"CObjReader::readlight("<<filename<<")\n";
	//char buf1[1024];buf1[0]=0;
	//char buf2[1024];buf2[0]=0;

	CLLight *pLI=&(CBase::get()->light);

	std::ifstream in;
	in.open(filename);
	if(in.eof()) return 1;
	int N;

	in>>CLight::Ia;
	in>>N;
	std::cout<<"  N:"<<N<<'\n';
	CLight *light=NULL;
	for(int k=0;k<N;++k){
		//чтение информации из файла
		cout<<"  k:"<<k<<'\n';
		light=new CLight;
		in>>light->type;
		in>>light->pos.x>>light->pos.y>>light->pos.z;
		in>>light->f>>light->n>>light->sz.x>>light->sz.y;
		light->b=light->a=standart_a;
		std::cout<<"  type:"<<light->type<<'\n';
		if(light->type==1){
			in>>light->w.x>>light->w.y>>light->w.z;	light->w.w=0;
			in>>light->v.x>>light->v.y>>light->v.z;	light->v.w=0;			
			light->u.x=light->v.y*light->w.z-light->v.z*light->w.y;
			light->u.y=light->v.z*light->w.x-light->v.x*light->w.z;
			light->u.z=light->v.x*light->w.y-light->v.y*light->w.x;
			light->u.w=0;
			in>>light->a>>light->b;
		}
		in>>light->Il>>light->K;
		in>>light->Ir>>light->Ig>>light->Ib>>light->Rst2;
		//настраиваем камеры
		CCamera* pCam=light->cam;
		CZLight* pZbuf=light->zbuf;
		if(light->type==0){//точечный источник света
			for(int i=0;i<6;++i,++pCam,++pZbuf) {
				pCam->f=light->f;	pCam->n=light->n;	pCam->a=light->a;	pCam->b=light->b;	
				pCam->pos=light->pos;
				pZbuf->fnSetSize(light->sz);	pZbuf->fnSetFog(0);
				//не нужно думать о step(длина одного шага) и gamma(угол одного поворота)
			}
			std::cout<<"  !";
			//установим направления матриц: w, v, u
			{
				pZbuf=light->zbuf; pCam=light->cam;
				POINT4 xp(1,0,0,0), xm(-1,0,0,0), yp(0,1,0,0), ym(0,-1,0,0), zp(0,0,1,0), zm(0,0,-1,0);
				//x>0
				pCam->w.setP4(xm);	pCam->v.setP4(yp);	pCam->u.setP4(zp);	++pCam;
				//x<0
				pCam->w.setP4(xp);	pCam->v.setP4(yp);	pCam->u.setP4(zm);	++pCam;
				//y>0
				pCam->w.setP4(ym);	pCam->v.setP4(xm);	pCam->u.setP4(zp);	++pCam;
				//y<0
				pCam->w.setP4(yp);	pCam->v.setP4(xp);	pCam->u.setP4(zp);	++pCam;
				//z>0
				pCam->w.setP4(zm);	pCam->v.setP4(yp);	pCam->u.setP4(xm);	++pCam;
				//z<0
				pCam->w.setP4(zp);	pCam->v.setP4(yp);	pCam->u.setP4(xp);	++pCam;
			}
			std::cout<<"!\n";
			//установим в камерах матрицы трансформации A
			pCam=light->cam;
			for(int i=0;i<6;++pCam,++i) pCam->fnSetA();
		}else if(light->type==1){// направленный источник света
			pCam->f=light->f;	pCam->n=light->n;	pCam->a=light->a;	pCam->b=light->b;	
			pCam->pos=light->pos;
			pZbuf->fnSetSize(light->sz);	pZbuf->fnSetFog(0);
			pCam->w.setP4(light->w);	pCam->v.setP4(light->v);	pCam->u.setP4(light->u);
			pCam->fnSetA();
		}
		pLI->push(light);
	}//for(int k=0;k<N;++k)

	in.close();
	return 0;
}


#endif