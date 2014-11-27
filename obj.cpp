class charkha{
	public:
		int rot,ro;
		bool isbusy;
		charkha(){
			isbusy=false;
			rot=0;
			ro=100;
		}
		void make(){
			glPushMatrix();
				glRotatef(rot,0,0,1);
				float r=3.0;
				for(int j=0;j<1;j++){
				glBegin(GL_POLYGON);
				glColor3f(01,1,1);
				for(int i=0;i<=360;i+=60){
					glVertex3f( r*cos(rad(i)), r*sin(rad(i)), j*2 );
				}
				glEnd();
				}
				for(int i=0;i<=360;i+=60){


					
					// for(int j=0;j<(i/60);j++){
					// 	glPushMatrix();
					// 		glColor3f(1,0,0);
					// 		glTranslatef(  (j*r/12.0+r/4)*cos(rad(i+30)) , (j*r/12.0+r/4)*sin(rad(i+30)) , 2 );
					// 		glutSolidCube(0.1);
					// 	glPopMatrix();
					// }



					if(  ((i/60)%2) )
						glColor3f(0,1,0);
					else
						glColor3f(1,0,1);
					glBegin(GL_POLYGON);
						glVertex3f( r*cos(rad(i)),  r*sin(rad(i)) , 2 );
						glVertex3f( r*cos(rad(i+60)), r*sin(rad(i+60)) , 2);
						glVertex3f( r*cos(rad(i+60)), r*sin(rad(i+60)) , 0);
						glVertex3f( r*cos(rad(i)), r*sin(rad(i)), 0 );
					glEnd();
					float sx=r*cos(rad(i));
					float sy=r*sin(rad(i));
					float dx=r*cos(rad(i+60))-sx;
					float dy=r*sin(rad(i+60))-sy;
					for(int p=1;p<=(i/60);p++){
						glPushMatrix();
							glColor3f(0,0,0);
							glTranslatef( sx+p*dx/8 , sy+p*dy/8 , 1 );
							glutSolidCube(0.1);
						glPopMatrix();
					}

				}
			glPopMatrix();
		}
		bool next(){
			if(rot < 30+60*(14-ro)){
				rot+=10;
				return true;
			}
			else{
				isbusy=false;
				return false;
			}
		}
		bool roll(int outp){
			if(!isbusy){
				isbusy=true;
				rot=0;
				ro=outp;
			}
		}
};



class pointer{
	public:
		float ph;
		int show;
		color*clr;
		int upcount;
		int movecount;
		bool busymoving;
		int havetomove;
		pointer(int s,color*c=NULL){
			busymoving=false;
			upcount=0;
			movecount=0;
			havetomove=0;
			ph=1;
			show=s;
			if(c==NULL)
				clr=new color(1,1,1);
			else

				clr=c;
		}
		void updown(){// Pointer is going up and down, when nothing is happenping
			if(upcount % (1<<2) == 0)//Use 1 in place of 2, to do faster uplifing and downgoing
				ph=(ph==1?1.3:1);
			upcount=( (upcount+1)%(1<<30));
		}
		void next(){
			if(havetomove>0){
				if(movecount % (1<<3) == 0){
					show++;
					havetomove--;
				}
				movecount=( (movecount+1)%(1<<30));
			}
			else
				busymoving=false;
		}
		void moven(int n){//put the player to n step ahead
			if(!busymoving){
				havetomove=n;
				busymoving=true;
			}
		}
		void make(){
			bool getonce=true;
			glColor3f(clr->r,clr->g,clr->b);
			for(int j=0;j<4;j++)
			for(int i=-5;i<=5;i+=1){
				int num;
				if(j==0)
					num= (5+i);
				else if(j==1)
					num= (30-5-i);
				else if(j==3)
					num= (10+5+i) ;
				else if(j==2)
					num= (40-5-i) ;
				if(j>2 && (num==10||num==20||num==30))
					continue;
				num%=40;
				glPushMatrix();
					if(j<2)
						glTranslatef(1.7*i,8*(j%2?1:-1),0);
					else
						glTranslatef(8*(j%2?1:-1),i*1.7,0);
					if(show%40==num && getonce){
						getonce=false;
						glPushMatrix();
							glTranslatef(0,0,ph);
							glScalef(1,1,5);
							glutSolidCube(0.5);
						glPopMatrix();
					}
					glScalef(1,1,0);
				glPopMatrix();
			}

		}
};


