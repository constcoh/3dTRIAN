#ifndef _CAMERA_H_
#define _CAMERA_H_

class CCamera{
public:
	double f,n,a,b,sin_gamma,cos_gamma;
	POINT4 w,u,v,pos;
	double step;
	CMatrix A;
private:
	static CCamera *pCAM;
public:
	CCamera(){w.x=w.y=w.z=0;w.w=1; u.x=u.y=u.z=0;u.w=1; v.x=v.y=v.z=0;v.w=1; pos.x=pos.y=pos.z=0;pos.w=1;}
	int fnPrint(){
		cout<<"CAMERA fnPrint:\n";
		cout<<"   f="<<f<<"\t n="<<n<<"\t a="<<a<<"\t b="<<b<<'\n';
		cout<<"   w.x="<<w.x<<"\t w.y="<<w.y<<"\t w.z="<<w.z<<"\t w.w="<<w.w<<'\n';
		cout<<"   u.x="<<u.x<<"\t u.y="<<u.y<<"\t u.z="<<u.z<<"\t u.w="<<u.w<<'\n';
		cout<<"   v.x="<<v.x<<"\t v.y="<<v.y<<"\t v.z="<<v.z<<"\t v.w="<<v.w<<'\n';
		cout<<"   pos.x="<<pos.x<<"\t pos.y="<<pos.y<<"\t pos.z="<<pos.z<<"\t pos.w="<<pos.w<<'\n';
		cout<<"  Matrix A:\n";
		cout<<'\t'<<A.s1.x<<'\t'<<A.s1.y<<'\t'<<A.s1.z<<'\t'<<A.s1.w<<'\n';
		cout<<'\t'<<A.s2.x<<'\t'<<A.s2.y<<'\t'<<A.s2.z<<'\t'<<A.s2.w<<'\n';
		cout<<'\t'<<A.s3.x<<'\t'<<A.s3.y<<'\t'<<A.s3.z<<'\t'<<A.s3.w<<'\n';
		cout<<'\t'<<A.s4.x<<'\t'<<A.s4.y<<'\t'<<A.s4.z<<'\t'<<A.s4.w<<'\n';
		return 0;
	}
	static CCamera *getCam(){
		if(pCAM==NULL) pCAM=new CCamera;
		return pCAM;
	}
	int fnSetA(){
		memset(&A,0,sizeof(A));
		A.s1.x=cos(b/2)/sin(b/2);		A.s2.y=cos(a/2)/sin(a/2);
		A.s3.z=(f+n)/(f-n); A.s3.w=-1; A.s4.z=2*f*n/(f-n);
		return 0;
	}
	int fnGetMatrixTransform(CMatrix (&Dest)){
		Dest.s1.x=u.x; Dest.s1.y=v.x; Dest.s1.z=w.x; Dest.s1.w=0;
		Dest.s2.x=u.y; Dest.s2.y=v.y; Dest.s2.z=w.y; Dest.s2.w=0;
		Dest.s3.x=u.z; Dest.s3.y=v.z; Dest.s3.z=w.z; Dest.s3.w=0;
		Dest.s4.x=-pos.x*u.x-pos.y*u.y-pos.z*u.z-pos.w*u.w;
		Dest.s4.y=-pos.x*v.x-pos.y*v.y-pos.z*v.z-pos.w*v.w;
		Dest.s4.z=-pos.x*w.x-pos.y*w.y-pos.z*w.z-pos.w*w.w;
		Dest.s4.w=1;
		//Dest=CMatrix::mult(Dest,A);
		return 0;
	}
	int fnLoadTXT(const char *filename){
		std::ifstream in;
		in.open(filename);
		if(in.eof()) return 1;
		in>>f>>n>>a>>b;
		POINT3 w3,v3;
		in>>w3.x>>w3.y>>w3.z;			w.x=w3.x; w.y=w3.y; w.z=w3.z; w.w=0;	//cout<<"   w: ";w.fnPrint();
		in>>v3.x>>v3.y>>v3.z;			v.x=v3.x; v.y=v3.y; v.z=v3.z; v.w=0;	//cout<<"   v: ";v.fnPrint();
		w3=POINT3::fnVProis(v3,w3);	u.x=w3.x; u.y=w3.y; u.z=w3.z; u.w=0;	//cout<<"   u: ";u.fnPrint();
		in>>v3.x>>v3.y>>v3.z;			pos.x=v3.x; pos.y=v3.y; pos.z=v3.z; pos.w=1;
		POINT sz;		in>>sz.x>>sz.y;
		CZBuffer * pZB=CZBuffer::get(); pZB->fnSetSize(sz); pZB->fnSetFog(0);
		in>>step;
		double gamma;
		in>>gamma;
		sin_gamma=sin(gamma);	cos_gamma=cos(gamma);
		in.close();
		fnSetA();
		//fnPrint();
		return 0;
	}
	int fnMoveFront(){pos.x-=step*w.x;	pos.y-=step*w.y;	pos.z-=step*w.z;	return 0;}
	int fnMoveBack() {pos.x+=step*w.x;	pos.y+=step*w.y;	pos.z+=step*w.z;	return 0;}
	int fnMoveLeft() {pos.x-=step*u.x;	pos.y-=step*u.y;	pos.z-=step*u.z;	return 0;}
	int fnMoveRight(){pos.x+=step*u.x;	pos.y+=step*u.y;	pos.z+=step*u.z;	return 0;}
	int fnMoveUp()   {pos.x+=step*v.x;	pos.y+=step*v.y;	pos.z+=step*v.z;	return 0;}
	int fnMoveDown() {pos.x-=step*v.x;	pos.y-=step*v.y;	pos.z-=step*v.z;	return 0;}
	int fnRotateLeft(){
		w.x=w.x*cos_gamma+u.x*sin_gamma;	w.y=w.y*cos_gamma+u.y*sin_gamma;	w.z=w.z*cos_gamma+u.z*sin_gamma;	
		u.x=v.y*w.z-v.z*w.y;					u.y=v.z*w.x-v.x*w.z;					u.z=v.x*w.y-v.y*w.x;					
		return 0;
	}
	int fnRotateRight(){
		w.x=w.x*cos_gamma-u.x*sin_gamma;	w.y=w.y*cos_gamma-u.y*sin_gamma;	w.z=w.z*cos_gamma-u.z*sin_gamma;	
		u.x=v.y*w.z-v.z*w.y;					u.y=v.z*w.x-v.x*w.z;					u.z=v.x*w.y-v.y*w.x;					
		return 0;
	}
};

CCamera *CCamera::pCAM=NULL;

#endif