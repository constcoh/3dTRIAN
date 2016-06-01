#ifndef _GLOBAL_OPTIONS_H_
#define _GLOBAL_OPTIONS_H_

struct CGOption{
	static bool check;
	static bool awtoredraw;
	static bool checktime;
	static bool gleams;
	static CRITICAL_SECTION cs;
	static int TreadCount;
	static double dEpsLight;
	static double dEpsZBufCompare;
	static double dInfKoefLight;
};

double CGOption::dInfKoefLight=0.1;
int CGOption::TreadCount=2;
bool CGOption::check=true;
bool CGOption::awtoredraw=false;
bool CGOption::checktime=false;
bool CGOption::gleams=true;
CRITICAL_SECTION CGOption::cs;
double CGOption::dEpsLight=0.0003;
double CGOption::dEpsZBufCompare=0.003;

#endif