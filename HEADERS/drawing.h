#ifndef _DRAWING_H_
#define _DRAWING_H_

struct CDrawing{
public:
	static int fnDraw();
	static int fnAmputationFront(const double &f,CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.z>f),			b1=(d.v1.z>f),			b2=(d.v2.z>f);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(f-d.v2.z)/v20.z;	k1=(f-d.v2.z)/v21.z;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(f-d.v2.z)/v20.z;	k1=(f-d.v1.z)/v10.z;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v20.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}
	static int fnAmputationBack(const double &f,CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.z<f),			b1=(d.v1.z<f),			b2=(d.v2.z<f);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;				
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(f-d.v2.z)/v20.z;	k1=(f-d.v2.z)/v21.z;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(f-d.v2.z)/v20.z;	k1=(f-d.v1.z)/v10.z;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v20.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}
	static int fnAmputationXFront(CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.x>1),			b1=(d.v1.x>1),			b2=(d.v2.x>1);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;				
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(1-d.v2.x)/v20.x;	k1=(1-d.v2.x)/v21.x;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(1-d.v2.x)/v20.x;	k1=(1-d.v1.x)/v10.x;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v10.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}
	static int fnAmputationXBack(CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.x<-1),			b1=(d.v1.x<-1),			b2=(d.v2.x<-1);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;				
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(-1-d.v2.x)/v20.x;	k1=(-1-d.v2.x)/v21.x;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(-1-d.v2.x)/v20.x;	k1=(-1-d.v1.x)/v10.x;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v20.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}


	static int fnAmputationYFront(CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.y>1),			b1=(d.v1.y>1),			b2=(d.v2.y>1);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;				
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(1-d.v2.y)/v20.y;	k1=(1-d.v2.y)/v21.y;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(1-d.v2.y)/v20.y;	k1=(1-d.v1.y)/v10.y;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v20.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}


	static int fnAmputationYBack(CTrian3dbu d,CTrian3dbu &otv1,CTrian3dbu &otv2){
		CTrian3dbu ot1,ot2;
		bool b0=(d.v0.y<-1),			b1=(d.v1.y<-1),			b2=(d.v2.y<-1);
		if(CGOption::check){
			std::cout<<"   b0="<<b0<<"   b1="<<b1<<"   b2="<<b2<<'\n';
			d.v0.fnPrint();
			d.v1.fnPrint();
			d.v2.fnPrint();
		}
		if(!b0 && !b1 && !b2){otv1=d; return 1;}
		if(b0 && b1 && b2) return 0;
		if(b0 && b2){swap(b2,b1); swap(d.v2,d.v1); swap(d.vn2,d.vn1); swap(d.vt2,d.vt1);}
		if(b1 && b2){swap(b2,b0); swap(d.v2,d.v0); swap(d.vn2,d.vn0); swap(d.vt2,d.vt0);}
		if(b0 && b1){
			ot1.v2=d.v2;				ot1.vn2=d.vn2;				ot1.vt2=d.vt2;				
			ot1.Img=d.Img;
			POINT3 v20,v21; double k0,k1;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v21.x=d.v1.x-d.v2.x;		v21.y=d.v1.y-d.v2.y;		v21.z=d.v1.z-d.v2.z;
			k0=(-1-d.v2.y)/v20.y;	k1=(-1-d.v2.y)/v21.y;
			v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			ot1.v0.x=ot1.v2.x+v20.x;	ot1.v0.y=ot1.v2.y+v20.y;	ot1.v0.z=ot1.v2.z+v20.z;	
			ot1.v1.x=ot1.v2.x+v21.x;	ot1.v1.y=ot1.v2.y+v21.y;	ot1.v1.z=ot1.v2.z+v21.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v21.x=d.vn1.x-d.vn2.x;		v21.y=d.vn1.y-d.vn2.y;		v21.z=d.vn1.z-d.vn2.z;
			//v20.x*=k0;		v20.y*=k0;		v20.z*=k0;			v21.x*=k1;		v21.y*=k1;		v21.z*=k1;
			//ot1.vn0.x=ot1.vn2.x+v20.x;	ot1.vn0.y=ot1.vn2.y+v20.y;	ot1.vn0.z=ot1.vn2.z+v20.z;	
			//ot1.vn1.x=ot1.vn2.x+v21.x;	ot1.vn1.y=ot1.vn2.y+v21.y;	ot1.vn1.z=ot1.vn2.z+v21.z;	
			//переработка векторов текстур
			v20.x=(double)(d.vt0.x-d.vt2.x);		v20.y=(double)(d.vt0.y-d.vt2.y);
			v21.x=(double)(d.vt1.x-d.vt2.x);		v21.y=(double)(d.vt1.y-d.vt2.y);
			v20.x*=k0;		v20.y*=k0;				v21.x*=k1;		v21.y*=k1;
			ot1.vt0.x=ot1.vt2.x+(int)v20.x;		ot1.vt0.y=ot1.vt2.y+(int)v20.y;	
			ot1.vt1.x=ot1.vt2.x+(int)v21.x;		ot1.vt1.y=ot1.vt2.y+(int)v21.y;	
			otv1=ot1;
			return 1;
		}
		if(b1){swap(b1,b0);	swap(d.v1,d.v0);	swap(d.vn1,d.vn0);	swap(d.vt1,d.vt0);}
		if(b2){swap(b2,b0);	swap(d.v2,d.v0);	swap(d.vn2,d.vn0);	swap(d.vt2,d.vt0);}
		if(b0){
					 ot1.v1=d.v1;					  ot1.vn1=d.vn1;				  ot1.vt1=d.vt1;				
			ot2.v2=ot1.v2=d.v2;			ot2.vn2=ot1.vn2=d.vn2;		ot2.vt2=ot1.vt2=d.vt2;				
			ot2.Img=ot1.Img=d.Img;
			POINT3 v20,v10; double k1,k2;
			//переработка векторов вершин
			v20.x=d.v0.x-d.v2.x;		v20.y=d.v0.y-d.v2.y;		v20.z=d.v0.z-d.v2.z;
			v10.x=d.v0.x-d.v1.x;		v10.y=d.v0.y-d.v1.y;		v10.z=d.v0.z-d.v1.z;
			k2=(-1-d.v2.y)/v20.y;	k1=(-1-d.v1.y)/v10.y;
			v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			ot2.v1.x=ot1.v0.x=ot1.v1.x+v10.x;	ot2.v1.y=ot1.v0.y=ot1.v1.y+v10.y;	ot2.v1.z=ot1.v0.z=ot1.v1.z+v10.z;	
						ot2.v0.x=ot2.v2.x+v20.x;				ot2.v0.y=ot2.v2.y+v20.y;				ot2.v0.z=ot2.v2.z+v20.z;	
			//переработка векторов нормалей
			//v20.x=d.vn0.x-d.vn2.x;		v20.y=d.vn0.y-d.vn2.y;		v20.z=d.vn0.z-d.vn2.z;
			//v10.x=d.vn0.x-d.vn1.x;		v10.y=d.vn0.y-d.vn1.y;		v20.z=d.vn0.z-d.vn1.z;
			//v20.x*=k2;		v20.y*=k2;		v20.z*=k2;			v10.x*=k1;		v10.y*=k1;		v10.z*=k1;
			//ot2.vn1.x=ot1.vn0.x=ot1.vn1.x+v10.x;	ot2.vn1.y=ot1.vn0.y=ot1.vn1.y+v10.y;	ot2.vn2.z=ot1.vn0.z=ot1.vn1.z+v10.z;	
			//			 ot2.vn0.x=ot2.vn2.x+v20.x;				 ot2.vn0.y=ot2.vn2.y+v20.y;				 ot2.vn0.z=ot2.vn2.z+v20.z;	
			//переработка векторов текстур
			v20.x=d.vt0.x-d.vt2.x;				v20.y=d.vt0.y-d.vt2.y;
			v10.x=d.vt0.x-d.vt1.x;				v10.y=d.vt0.y-d.vt1.y;
			v20.x*=k2;		v20.y*=k2;			v10.x*=k1;		v10.y*=k1;
			ot2.vt1.x=ot1.vt0.x=ot1.vt1.x+v10.x;			ot2.vt1.y=ot1.vt0.y=ot1.vt1.y+v10.y;	
						 ot2.vt0.x=ot2.vt2.x+v20.x;						 ot2.vt0.y=ot2.vt2.y+v20.y;	
			otv1=ot1; otv2=ot2;
			return 2;
		}
		return -1;
	}

};

CTrian3dbu mTr[64];
int CDrawing::fnDraw(){
	double time;
	if(CGOption::checktime) time=GetTickCount();
	int count=1;
	CLTrian *pVT=&(CBase::get()->trian);
	CCamera *pCam=CCamera::getCam();
	int szVT=pVT->fnGetSize();
	int teksz=0,tekdeg=512,tekdegi=0;
	CTrian3d *trian=pVT->gP(0);
	double camF=-pCam->f, camN=-pCam->n;
	double ctgX=pCam->A.s1.x,ctgY=pCam->A.s2.y;

	POINT3 pos3; pos3.x=pCam->pos.x; pos3.y=pCam->pos.y; pos3.z=pCam->pos.z;
	POINT3 &vn0=mTr[0].vn0,&vn1=mTr[0].vn1,&vn2=mTr[0].vn2,	&v0=mTr[0].v0,&v1=mTr[0].v1,&v2=mTr[0].v2;
	POINT &vt0=mTr[0].vt0,&vt1=mTr[0].vt1,&vt2=mTr[0].vt2;
	CMatrix mTransform,mh;
	pCam->fnGetMatrixTransform(mTransform);
	if(CGOption::check){
		pCam->fnPrint();
		cout<<"   mTransform:\n";mTransform.fnPrint();
		cout<<"   A:\n";pCam->A.fnPrint();
	}
	//mh=CMatrix::mult(mTransform,pCam->A);
	//cout<<"   mh:\n";mh.fnPrint();

	//cout<<"   u: "<<pCam->u.fnPrint(); cout<<'\n';
	//cout<<"   v: "<<pCam->v.fnPrint(); cout<<'\n';
	//cout<<"   w: "<<pCam->w.fnPrint(); cout<<'\n';

	//рисуем в z-буфере туман
	{
		CZBuffer *pZB=CZBuffer::get();
		pZB->fnSetFog(0);
	}

	for(;teksz<szVT;++teksz,++tekdegi,++trian){
		if(CGOption::checktime)	cout<<"st:"<<(GetTickCount()-time )<<'\n';
		if(tekdegi==tekdeg){//в trian сменился столбец
			tekdeg*=2; tekdegi=0; trian=pVT->gP(teksz);
		}
		if(CGOption::check){
			cout<<"  teksz="<<1+teksz<<'\n';
			cout<<"   Img:"<<trian->Img<<'\n';
		}
		//заполняем параметры треугольника
		vn0=*(trian->vn0);	vn1=*(trian->vn1);	vn2=*(trian->vn2);
		vt0=*(trian->vt0);	vt1=*(trian->vt1);	vt2=*(trian->vt2);
		v0=*(trian->v0);		v1=*(trian->v1);		v2=*(trian->v2);
		if(CGOption::check){
			cout<<"   vt0:"<<vt0.x<<' '<<vt0.y<<'\n';
			cout<<"   vt1:"<<vt1.x<<' '<<vt1.y<<'\n';
			cout<<"   vt2:"<<vt2.x<<' '<<vt2.y<<'\n';
		}
		mTr[0].Img=trian->Img;
		//проверка на ориентир
		{
			POINT3 vn,v01,v02,vp0;
			vn.x=(vn0.x+vn1.x+vn2.x)/3;			vn.y=(vn0.y+vn1.y+vn2.y)/3;			vn.z=(vn0.z+vn1.z+vn2.z)/3;
			v01.x=v1.x-v0.x;							v01.y=v1.y-v0.y;							v01.z=v1.z-v0.z;							
			v02.x=v2.x-v0.x;							v02.y=v2.y-v0.y;							v02.z=v2.z-v0.z;							
			vp0.x=v0.x-pos3.x;						vp0.y=v0.y-pos3.y;						vp0.z=v0.z-pos3.z;						
			POINT3 norm; norm=POINT3::fnVProis(v01,v02);
			double pr1=POINT3::fnSProis(pos3,norm);//скалярные произведения pos с vn и n
			double pr2=POINT3::fnSProis(vp0,vn);
			//cout<<"   vp0:";vp0.fnPrint();
			//cout<<"    vn:"; vn.fnPrint();

			if(pr2>=0) continue;
			if(CGOption::check){
			cout<<"   is see\n";
			}
			//cout<<"   v0:";v0.fnPrint();	cout<<"   v1:";v1.fnPrint();	cout<<"   v2:";v2.fnPrint();	
		}
		//перевод в координады камеры
		{
			POINT4 v04,v14,v24;
			v04=v0; v04=mTransform.fnMultRight(v04); v04.fnDoNormal(); v0=v04;
			v14=v1; v14=mTransform.fnMultRight(v14); v14.fnDoNormal(); v1=v14;
			v24=v2; v24=mTransform.fnMultRight(v24); v24.fnDoNormal(); v2=v24;
			//cout<<"   camN="<<camN<<'\n';
		}
		if(CGOption::checktime)	cout<<"st Amputation:"<<(GetTickCount()-time )<<'\n';
		//отсечение по оси z
		{
			count=fnAmputationFront(camN,mTr[0],mTr[0],mTr[1]); if(CGOption::check) cout<<"   count="<<count<<'\n'; if(count<=0) continue;//- передняя стенка всё отсекла
			int r,dest2=count;
			for(int i=0;i<count;++i){
				//cout<<"   mTr["<<i<<"].v0:";mTr[i].v0.fnPrint();
				//cout<<"   mTr["<<i<<"].v1:";mTr[i].v1.fnPrint();
				//cout<<"   mTr["<<i<<"].v2:";mTr[i].v2.fnPrint();
				
				r=fnAmputationBack(camF,mTr[i],mTr[i],mTr[dest2]);
				if(r==0){ for(int k=i;k<dest2-1;++k) mTr[k]=mTr[k+1]; --dest2; --i; --count;}
				if(r==2) ++dest2;
			}
			count=dest2;
			if(CGOption::check){
				cout<<"   count="<<count<<'\n';
				for(int i=0;i<count;++i){cout<<"face "<<i<<":\n"; mTr[i].v0.fnPrint(); mTr[i].v1.fnPrint(); mTr[i].v2.fnPrint();}
			}
		}
		//перевод в трубку и преобразование по оси Oz
		if(CGOption::check) cout<<"TRUBE and AMPUTATION z:\n";
		{
			CTrian3dbu *tek=&(mTr[0]); 
			double a=2/(camN-camF),b=(-camF-camN)/(camN-camF);
			for(int i=0;i<count;++i,++tek){
				tek->v0.x=-(tek->v0.x)*ctgX/(tek->v0.z);		tek->v0.y=-(tek->v0.y)*ctgY/(tek->v0.z);		tek->v0.z=a*(tek->v0.z)+b;
				tek->v1.x=-(tek->v1.x)*ctgX/(tek->v1.z);		tek->v1.y=-(tek->v1.y)*ctgY/(tek->v1.z);		tek->v1.z=a*(tek->v1.z)+b;
				tek->v2.x=-(tek->v2.x)*ctgX/(tek->v2.z);		tek->v2.y=-(tek->v2.y)*ctgY/(tek->v2.z);		tek->v2.z=a*(tek->v2.z)+b;
			}
			if(CGOption::check){
				cout<<"   count="<<count<<'\n';
				for(int i=0;i<count;++i){cout<<"face "<<i<<":\n"; mTr[i].v0.fnPrint(); mTr[i].v1.fnPrint(); mTr[i].v2.fnPrint();}
			}
		}
		//отсечение по осям x и y
		if(CGOption::check) cout<<"AMPUTATION x, y:\n";
		{
			int r,dest2=count;
			//x==1
			for(int i=0;i<count;++i){
				//cout<<"   mTr["<<i<<"].v0:";mTr[i].v0.fnPrint();
				//cout<<"   mTr["<<i<<"].v1:";mTr[i].v1.fnPrint();
				//cout<<"   mTr["<<i<<"].v2:";mTr[i].v2.fnPrint();
				
				r=fnAmputationXFront(mTr[i],mTr[i],mTr[dest2]);
				if(r==0){ for(int k=i;k<dest2-1;++k) mTr[k]=mTr[k+1]; --dest2; --i; --count;}				if(r==2) ++dest2;
			}
			count=dest2;
			//x==-1
			for(int i=0;i<count;++i){
				r=fnAmputationXBack(mTr[i],mTr[i],mTr[dest2]);
				if(r==0){ for(int k=i;k<dest2-1;++k) mTr[k]=mTr[k+1]; --dest2; --i; --count;}				if(r==2) ++dest2;
			}
			count=dest2;
			//y==1
			for(int i=0;i<count;++i){
				r=fnAmputationYFront(mTr[i],mTr[i],mTr[dest2]);
				if(r==0){ for(int k=i;k<dest2-1;++k) mTr[k]=mTr[k+1]; --dest2; --i; --count;}				if(r==2) ++dest2;
			}
			count=dest2;
			//y==-1
			for(int i=0;i<count;++i){
				r=fnAmputationYBack(mTr[i],mTr[i],mTr[dest2]);
				if(r==0){ for(int k=i;k<dest2-1;++k) mTr[k]=mTr[k+1]; --dest2; --i; --count;}				if(r==2) ++dest2;
			}
			count=dest2;
			if(CGOption::check){
				cout<<"  fnAmputationYBack\n";
				cout<<"   count="<<count<<'\n';
				for(int i=0;i<count;++i){cout<<"face "<<i<<":\n"; 
					mTr[i].v0.fnPrint(); mTr[i].v1.fnPrint(); mTr[i].v2.fnPrint();
					POINTD::fnPrintI(mTr[i].vt0);	POINTD::fnPrintI(mTr[i].vt1);	POINTD::fnPrintI(mTr[i].vt2);
				}
				system("pause");
			}
		}
		if(CGOption::checktime)	cout<<"st Drawing z-buffer:"<<(GetTickCount()-time )<<'\n';
		//рисуем в z-буфере
		if(CGOption::check) cout<<"zbuffer:\n";
		{
			CZBuffer *pZB=CZBuffer::get();
			CTrian3dibu TrI;
			POINT hsz;	pZB->fnGet_sz(hsz); hsz.x=hsz.x>>1; hsz.y=hsz.y>>1;
			for(int i=0;i<count;++i){
				if(CGOption::check){
					cout<<"   face "<<i<<":\n"; mTr[i].v0.fnPrint(); mTr[i].v1.fnPrint(); mTr[i].v2.fnPrint();
					cout<<"    Img:"<<mTr[i].Img<<'\n';
					cout<<"   vt0:"<<mTr[i].vt0.x<<' '<<mTr[i].vt0.y<<'\n';
					cout<<"   vt1:"<<mTr[i].vt1.x<<' '<<mTr[i].vt1.y<<'\n';
					cout<<"   vt2:"<<mTr[i].vt2.x<<' '<<mTr[i].vt2.y<<'\n';
					system("pause");
				}
				TrI.set(mTr[i],hsz);	pZB->fnDrawTrian2D(TrI);		
			}
		}
		if(CGOption::checktime)	cout<<"fin:"<<(GetTickCount()-time )<<'\n';
	}

	if(CGOption::gleams)	CGleams::fnDrawGleams();
	
	return 0;
}


#endif