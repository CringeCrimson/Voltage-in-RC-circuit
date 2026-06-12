#include<stdio.h>
#include<math.h>
double current_D(double v,double R, double C, double t){
	if(R<=0||C<=0||t<0){
		return 0.0;
	}else{
		double a=v/R;
		double tau=R*C;
		double c=a*exp(-t/tau);
		return -c;
	}
}

double Vr(double v,double R, double C, double t){
	if(R<=0||C<=0||t<0){
		return 0.0;
	}else{
		double a=v/R;
		double tau=R*C;
		double V=v*exp(-t/tau);
		return V;
	}
}
