
image*img=NULL;
/**
*Function to make cube
*
*/
void makeCube(float w){
	for(int i=0;i<3;i++)
		for(int j=0;j<2;j++){
			glColor3f (1, 1.0, 1);
			if(1==1)
				glBegin(GL_POLYGON);
			else
				glBegin(GL_LINE_LOOP);
			float arr[4][3];
			float arr1[3];
			
			for(int k=0;k<2;k++)
				for(int l=0;l<2;l++){
					int pnt=k*2+l;
					arr1[0]=j?w:-w;
					arr1[1]=k?w:-w;
					arr1[2]=((l+k)%2)?w:-w;
					for(int t=0;t<3;t++)
						arr[pnt][t]=arr1[(i+t)%3];
					glVertex3f (arr[pnt][0],arr[pnt][1],arr[pnt][2]);
				}
			glEnd();
			int count=1+i+j*3;
			for(int k=1;k<=3;k++)
				for(int l=1;l<=3;l+=2){
					if(!count--)
						goto exitloop;
					float pxyz[3];
					for(int t=0;t<3;t++)
						pxyz[t]=(arr[0][t]*k*l + arr[1][t]*(4-k)*l + arr[2][t]*(4-k)*(4-l) + arr[3][t]*k*(4-l))/16;
					glPushMatrix();
						pxyz[(3-i)%3]+=0.0*(j==1?1:-1);
						glTranslatef(pxyz[0],pxyz[1],pxyz[2]);
						glColor3f (1.0, 0.0, 0.0);
						glutWireSphere (0.05,16,20);
					glPopMatrix();
				}
			exitloop:
				1;
		}
}

/**
*Function to makefloor
*/

void makeFloor(void){
	int model=2;
	if(model==1){
		for(int i=-10;i<10;i++)
			for(int j=-10;j<10;j++){
				if((i+j)%2)
					glColor3f (0,0, 1);
				else
					glColor3f (1,0, 0);
				glBegin(GL_POLYGON);
					glVertex3f (i,j,0);
					glVertex3f (i+1,j,0);
					glVertex3f (i+1,j+1,0);
					glVertex3f (i,j+1,0);
				glEnd();
			}
	}
	else if(model==2){
		glBegin(GL_POINTS); //starts drawing of points
		int w=img->w,h=img->h;
		unsigned char*data2=img->data2;
		for(int i=0;i<h;i+=1)
			for(int j=0;j<w;j+=1){
				glColor3f( ((float)data2[3*(i*w+j)+2])/255.0 , ((float)data2[3*(i*w+j)+1])/255.0 , ((float)data2[3*(i*w+j)])/255.0);
				glVertex3f(-10+20.0*i/h,-10+20.0*j/w,0);//lower-left corner
			}
		glEnd();
	}
}


