#include <math.h>
#include <fstream>
#include <sstream>

float rad(int ang){
	return M_PI*ang/180.0;
}

float deg(float ang){
	return ang*180.0/M_PI;
}


class vector{
	public:
		float x,y,z;
		vector(float x1,float y1,float z1){
			x=x1;y=y1;z=z1;
		}
		vector(){
			x=y=z=0;
		}
		void print(bool newl=true){
			cout<<"("<<x<<","<<y<<","<<z<<")"<<flush;
			if(newl)
				cout<<endl;
		}
};

class color{
	public:
		float r,g,b;
		color(float r1,float g1,float b1){
			r=r1,g=g1,b=b1;
		}
		color(int r1,int g1,int b1,int mod){
			r=r1*1.0/mod;
			g=g1*1.0/mod;
			b=b1*1.0/mod;
		}
};

// if(lfv==NULL)
// 				lf=*(new vector(8,0,20));
// 			else
// 				lf=*lfv;
// 			if(ltv==NULL)
// 				lt=*(new vector(0,0,0));
// 			else
// 				lt=*ltv;
// 			if(uvv==NULL)
// 				uv=*(new vector(0,1,1));
// 			else
// 				uv=*uvv;
// 		}

class camera{
	public:
		vector lf,lt,uv;//Look From,Look Toward,Upper Vector
		camera(vector*lfv,vector*ltv,vector*uvv){
			if(lfv==NULL)
				lf=*(new vector(12,0,20));
			else
				lf=*lfv;
			if(ltv==NULL)
				lt=*(new vector(0,0,0));
			else
				lt=*ltv;
			if(uvv==NULL)
				uv=*(new vector(0,1,1));
			else
				uv=*uvv;
		}
};

class image{
	public:
		int w,h;
		unsigned char *data2;
		image(const char*fn){
			FILE *f;
	//		f=fopen("img2.bmp","rb");
			f=fopen(fn,"rb");
			unsigned char*data1=new unsigned char[54];
			fread(data1,1,54,f);
			int wid=(int)data1[18]+(1<<8)*data1[19]+(1<<16)*data1[20]+(1<<24)*data1[21];
			int hgt=(int)data1[22]+(1<<8)*data1[23]+(1<<16)*data1[24]+(1<<24)*data1[25];
			w=wid;
			h=hgt;
			data2=new unsigned char[3*wid*hgt];
			for(int i=0;i<hgt;i++){
			        fread(data2+(wid*(hgt-i-1)*3),3,wid,f);
			        fread(data1,1,(4-wid%4)%4,f);
			}
		}
};


