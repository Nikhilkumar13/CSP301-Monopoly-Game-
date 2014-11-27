#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

#include "use.h"
#include "obj.cpp"
#include "Chance.h"
#include "Chest.h"
#include "Player.h"
#include "Properties.h"
#include "botPlayer.h"
#include  "help.cpp"

pair <int,int> spin1;
pair <int,int> spin2;
pair <int,int> spin3;

int main_w ,w1;

charkha*c1=NULL,*c2=NULL;//Two Dice..
pointer**p1=NULL;//Array (pointer ) of players.
#include "globalvariables.cpp"

bool starter=true;

camera c(NULL,NULL,new vector(0,0,1));



void init(void){
	cout<<"press 0 ,1 ,2 to move these players,  Press d to roll dice "<<endl;
	//================Console Code==============================================
	 //Initialize Game
    #include "initialize.cpp"

    //=========================================================================================================
	img=new image("img2.bmp");
	c1=new charkha();   // Dice 1
	c2=new charkha();	//Dice 2
	// num_players=3;
    cout<<"Number Of Players->"<<num_players<<endl;
    cout<<"Press S to start the Game"<<endl;
	p1=new pointer*[num_players];
	p1[0]=new pointer(0,new color(1,0,1));
	p1[1]=new pointer(0,new color(1,0,0));
	p1[2]=new pointer(0,new color(0,1,0));
	spin3.first=175;
	spin3.second=0;

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}


void display(void){
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0,0, 0);
	glLoadIdentity ();

	gluLookAt (c.lf.x,c.lf.y,c.lf.z, c.lt.x,c.lt.y,c.lt.z, c.uv.x , c.uv.y, c.uv.z);

	glPushMatrix();
		glRotatef(spin3.first,0,0,1);
		glRotatef(spin3.second,0,1,0);
		makeFloor();
		for(int i=0;i<num_players;i++)
			p1[i]->make();
		glPushMatrix();
			glTranslatef(0,-3.5,0);
			c1->make();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,3.5,0);
			c2->make();
		glPopMatrix();

		glPopMatrix();


	glPopMatrix();
	glutSwapBuffers();
}


void updatePosition(int i)
{
	p1[i]->show+=39;
	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-2.0, 2.0, -2.0, 2.0, 3, 100.0);
   glMatrixMode (GL_MODELVIEW);

}


void rollDice(int a , int b)
{

	 c1->roll(a);
     c2->roll(b);
     glutPostRedisplay();

}

void keyboard (unsigned char key, int x, int y){
	if((!Players[currentPlayerPlaying]->isBot())||starter)
	{
		starter=true;
	if(key==27)
		exit(0);
	else if(key==',')
		spin3.first-=5;
	else if(key=='.')
		spin3.first+=5;
	else if(key=='a')
		spin3.second-=5;
	else if(key=='z')
		spin3.second+=5;
	else if(key=='m')
		p1[0]->moven(5);
    else if(key=='s')
    {
        #include "Gameloop.cpp"

    }
	else if(key=='q')
	{
		declareWinner();
		
	}
	for(int i=0;i<num_players;i++)
		if(key==i+'1')
			p1[i]->show+=39;
	glutPostRedisplay();
}
}

void timer(int n){
	bool m1=c1->next();
	bool m2=c2->next();
	for(int i=0;i<num_players;i++)
	{
		p1[i]->updown();
	}
	
	// p1[0]->next();


	glutPostRedisplay();
	glutTimerFunc(n,timer,n);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   // glutInitWindowSize (1600, 900); 
  glutInitWindowSize (1600, 900); 
   glutInitWindowPosition ( 0,  0);
  main_w= glutCreateWindow ("Monopoly");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
	glutTimerFunc(0,timer,20);
	  // glClearColor(0.137, 0.458, 0.09, 1.0);  //Green
	glClearColor(0.9, 0.04, 0.04, 1.0);  //Red
   glutMainLoop();
   return 0;
}       


