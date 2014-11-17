#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



class pointer{
	public:
		float ph;
		int show;
		color*clr;
		int upcount;
		int movecount;
		bool busymoving;
		int havetomove;
		pointer(int s,color*c=NULL);
		void updown();
		void next();
		void moven(int n);
		void make();
};




