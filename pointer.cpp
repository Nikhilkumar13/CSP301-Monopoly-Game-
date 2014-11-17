#include "pointer.h"

		void pointer::pointer(int s,color*c=NULL){
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
		void pointer::updown(){// Pointer is going up and down, when nothing is happening
			if(upcount % (1<<2) == 0)//Use 1 in place of 2, to do faster uplifing and downgoing
				ph=(ph==1?1.3:1);
			upcount=( (upcount+1)%(1<<30));
		}
		void pointer::next(){
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
		void pointer::moven(int n){//put the player to n step ahed
			if(!busymoving){
				havetomove=n;
				busymoving=true;
			}
		}
		void pointer::make(){
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

