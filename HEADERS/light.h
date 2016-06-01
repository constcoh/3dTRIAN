#ifndef _HIGHT_H_
#define _HIGHT_H_

class CLight{
public:
	static double Ia;
public:
	int type;
	POINT4 w,u,v,pos;
	POINT sz;
	double f,n,a,b;
	CCamera cam[6];
	CZLight zbuf[6]; 
	double Il, K;
	double Ir,Ig,Ib,Rst2;
};

double CLight::Ia=0;

#endif