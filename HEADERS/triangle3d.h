#ifndef _TRIANGLE3D_H_
#define _TRIANGLE3D_H_

struct POINTD{
	double x,y;
	POINTD & operator=(const POINT &d){x=(double)d.x; y=(double)d.y; return *this;}
	static int fnPrintI(const POINT &d){cout<<"   x:"<<d.x<<"\t y:"<<d.y<<'\n'; return 0;}
};

struct POINT4;

struct POINT3{double x,y,z;
	static POINT3 fnVProis(const POINT3 &arg1,const POINT3 &arg2){
		POINT3 otv;
		otv.x=arg1.y*arg2.z-arg1.z*arg2.y;
		otv.y=arg1.z*arg2.x-arg1.x*arg2.z;
		otv.z=arg1.x*arg2.y-arg1.y*arg2.x;
		return otv;
	}
	static double fnSProis(const POINT3 &arg1,const POINT3 &arg2){
		return arg1.x*arg2.x+arg1.y*arg2.y+arg1.z*arg2.z;
	}
	int fnPrint(){
		cout<<"    x:"<<this->x<<"\t y:"<<this->y<<"\t z:"<<this->z<<'\n';
		return 0;
	}
	POINT3 operator+(const POINT3 &arg){
		POINT3 otv;
		otv.x=x+arg.x;	otv.y=y+arg.y;	otv.z=z+arg.z;
		return otv;
	}
	POINT3 operator+=(const POINT3 &arg){
		x+=arg.x;	y+=arg.y;	z+=arg.z;
		return *this;
	}

	POINT3 operator-(const POINT3 &arg){
		POINT3 otv;
		otv.x=x-arg.x;	otv.y=y-arg.y;	otv.z=z-arg.z;
		return otv;
	}
	POINT3 operator-=(const POINT3 &arg){
		x-=arg.x;	y-=arg.y;	z-=arg.z;
		return *this;
	}
	POINT3 fnMult(const double &arg){
		POINT3 otv;
		otv.x=x*arg;	otv.y=y*arg;	otv.z=z*arg;
		return otv;
	}
	POINT3 fnMultIt(const double &arg){
		x*=arg;	y*=arg;	z*=arg;
		return *this;
	}
	POINT3& operator=(const POINT4& d);
	POINT3 fnNormal(){
		double len=sqrt(x*x+y*y+z*z);
		x/=len;	y/=len;	z/=len;	
		return *this;
	}
	double fnLen(){
		return sqrt(x*x+y*y+z*z);
	}
};
struct POINT4{double x,y,z,w;
	int fnPrint(){
		cout<<"    x:"<<this->x<<"\t y:"<<this->y<<"\t z:"<<this->z<<"\t w:"<<this->w<<'\n';
		return 0;
	}
	int fnDoNormal(){
		if(w!=0) {x/=w; y/=w; z/=w; w=1;}
		return 0;
	}
	POINT4(const POINT4 &d){memcpy(this,&d,sizeof(POINT4));}
	POINT4(){memset(this,0,sizeof(POINT4));}
	POINT4(const double &dx,const double &dy,const double &dz,const double &dw){x=dx; y=dy; z=dz; w=dw;}	
	POINT4& operator=(const POINT3 &d){x=d.x; y=d.y; z=d.z; w=1;   return *this;}
	void setP4(POINT4& d){x=d.x; y=d.y; z=d.z; w=d.w; return;};
};
POINT3& POINT3::operator=(const POINT4& d){x=d.x; y=d.y; z=d.z; return *this;}

struct CMatrix{
	POINT4 s1,s2,s3,s4;
	static CMatrix mult(const CMatrix &m1,const CMatrix &m2){
		CMatrix otv;
		otv.s1.x=m1.s1.x*m2.s1.x+m1.s1.y*m2.s2.x+m1.s1.z*m2.s3.x+m1.s1.w*m2.s4.x;
		otv.s1.y=m1.s1.x*m2.s1.y+m1.s1.y*m2.s2.y+m1.s1.z*m2.s3.y+m1.s1.w*m2.s4.y;
		otv.s1.z=m1.s1.x*m2.s1.z+m1.s1.y*m2.s2.z+m1.s1.z*m2.s3.z+m1.s1.w*m2.s4.z;
		otv.s1.w=m1.s1.x*m2.s1.w+m1.s1.y*m2.s2.w+m1.s1.z*m2.s3.w+m1.s1.w*m2.s4.w;
		otv.s2.x=m1.s2.x*m2.s1.x+m1.s2.y*m2.s2.x+m1.s2.z*m2.s3.x+m1.s2.w*m2.s4.x;
		otv.s2.y=m1.s2.x*m2.s1.y+m1.s2.y*m2.s2.y+m1.s2.z*m2.s3.y+m1.s2.w*m2.s4.y;
		otv.s2.z=m1.s2.x*m2.s1.z+m1.s2.y*m2.s2.z+m1.s2.z*m2.s3.z+m1.s2.w*m2.s4.z;
		otv.s2.w=m1.s2.x*m2.s1.w+m1.s2.y*m2.s2.w+m1.s2.z*m2.s3.w+m1.s2.w*m2.s4.w;
		otv.s3.x=m1.s3.x*m2.s1.x+m1.s3.y*m2.s2.x+m1.s3.z*m2.s3.x+m1.s3.w*m2.s4.x;
		otv.s3.y=m1.s3.x*m2.s1.y+m1.s3.y*m2.s2.y+m1.s3.z*m2.s3.y+m1.s3.w*m2.s4.y;
		otv.s3.z=m1.s3.x*m2.s1.z+m1.s3.y*m2.s2.z+m1.s3.z*m2.s3.z+m1.s3.w*m2.s4.z;
		otv.s3.w=m1.s3.x*m2.s1.w+m1.s3.y*m2.s2.w+m1.s3.z*m2.s3.w+m1.s3.w*m2.s4.w;
		otv.s4.x=m1.s4.x*m2.s1.x+m1.s4.y*m2.s2.x+m1.s4.z*m2.s3.x+m1.s4.w*m2.s4.x;
		otv.s4.y=m1.s4.x*m2.s1.y+m1.s4.y*m2.s2.y+m1.s4.z*m2.s3.y+m1.s4.w*m2.s4.y;
		otv.s4.z=m1.s4.x*m2.s1.z+m1.s4.y*m2.s2.z+m1.s4.z*m2.s3.z+m1.s4.w*m2.s4.z;
		otv.s4.w=m1.s4.x*m2.s1.w+m1.s4.y*m2.s2.w+m1.s4.z*m2.s3.w+m1.s4.w*m2.s4.w;
		return otv;
	}
	CMatrix &operator=(const CMatrix &m){	memcpy(this,&m,sizeof(CMatrix));	return *this;	}
	CMatrix(const CMatrix &m){		memcpy(this,&m,sizeof(CMatrix));}
	CMatrix(){memset(this,0,sizeof(CMatrix));}

	POINT4& fnMultRight(const POINT4 &arg){
		POINT4 otv;
		otv.x=arg.x*s1.x+arg.y*s2.x+arg.z*s3.x+arg.w*s4.x;
		otv.y=arg.x*s1.y+arg.y*s2.y+arg.z*s3.y+arg.w*s4.y;
		otv.z=arg.x*s1.z+arg.y*s2.z+arg.z*s3.z+arg.w*s4.z;
		otv.w=arg.x*s1.w+arg.y*s2.w+arg.z*s3.w+arg.w*s4.w;
		return otv;
	}
	int fnPrint(){
		cout<<"    s1: "<<s1.x<<"\t "<<s1.y<<"\t "<<s1.z<<"\t "<<s1.w<<'\n';
		cout<<"    s2: "<<s2.x<<"\t "<<s2.y<<"\t "<<s2.z<<"\t "<<s2.w<<'\n';
		cout<<"    s3: "<<s3.x<<"\t "<<s3.y<<"\t "<<s3.z<<"\t "<<s3.w<<'\n';
		cout<<"    s4: "<<s4.x<<"\t "<<s4.y<<"\t "<<s4.z<<"\t "<<s4.w<<'\n';

		return 0;
	}
};



struct CTrian3d{
	POINT3 *v0,*v1,*v2;
	POINT *vt0,*vt1,*vt2;
	POINT3 *vn0,*vn1,*vn2;
	CImage *Img,*ImgNs;
	CTrian3d():Img(NULL),ImgNs(NULL){}
};
struct CTrian3dbu{
	POINT3 v0,v1,v2;
	POINT vt0,vt1,vt2;
	POINT3 vn0,vn1,vn2;
	CImage *Img;
	CTrian3dbu():Img(NULL){}
	int fnPrint(){
		std::cout<<"CTrian3dbu:\n";
		std::cout<<"v0: "<<v0.x<<"\t "<<v0.y<<"\t "<<v0.z<<'\n';
		std::cout<<"v1: "<<v1.x<<"\t "<<v1.y<<"\t "<<v1.z<<'\n';
		std::cout<<"v2: "<<v2.x<<"\t "<<v2.y<<"\t "<<v2.z<<'\n';
		std::cout<<"vt0: "<<vt0.x<<"\t "<<vt0.y<<'\n';
		std::cout<<"vt1: "<<vt1.x<<"\t "<<vt1.y<<'\n';
		std::cout<<"vt2: "<<vt2.x<<"\t "<<vt2.y<<'\n';
		return 0;
	}
};
struct CTrian3dibu{
	POINT v0,v1,v2;
	POINT vt0,vt1,vt2;
	double g0,g1,g2;
	CImage *Img;
	CTrian3dibu():Img(NULL){}
	int set(const CTrian3dbu &d,const POINT hsz){
		POINT sz; sz.x=hsz.x<<1; sz.y=hsz.y<<1;
		v0.x=(LONG)(hsz.x*d.v0.x)+hsz.x;	if(v0.x==sz.x) v0.x=sz.x-1;	v0.y=(LONG)(hsz.y*d.v0.y)+hsz.y;	if(v0.y==sz.y) v0.y=sz.y-1;	g0=d.v0.z;
		v1.x=(LONG)(hsz.x*d.v1.x)+hsz.x;	if(v1.x==sz.x) v1.x=sz.x-1;	v1.y=(LONG)(hsz.y*d.v1.y)+hsz.y;	if(v1.y==sz.y) v1.y=sz.y-1;	g1=d.v1.z;
		v2.x=(LONG)(hsz.x*d.v2.x)+hsz.x;	if(v2.x==sz.x) v2.x=sz.x-1;	v2.y=(LONG)(hsz.y*d.v2.y)+hsz.y;	if(v2.y==sz.y) v2.y=sz.y-1;	g2=d.v2.z;
		vt0=d.vt0;						vt1=d.vt1;						vt2=d.vt2;
		Img=d.Img;
		return 0;
	}
};



#endif