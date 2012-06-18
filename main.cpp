#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>

float sumbux=0.0, sumbuy=0.0, sumbuz=0.0;
float sudut=0.0f;
float vektorx=0.0f, vektorz=-1.0f;
float x=0.0f, z=5.0f;
float pindahx =0.0, pindahy=0.0, pindahz=0.0;
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, putary=0, angle=0.0; //Rotasi Sudut
float inner, outer; int garisv,garish; //Variabel Torus

const float clockR    = 0.5f,
            clockVol  = 1.0f,

            angle1min = M_PI / 30.0f,

            minStart  = 0.9f,
            minEnd    = 1.0f,

            stepStart = 0.8f,
            stepEnd   = 1.0f;

float angleHour = 0,
      angleMin  = 0,
      angleSec  = 0;

      
//FUNGSI JAM      
void newLine(float rStart, float rEnd, float angle){
  float c = cos(angle), s = sin(angle);
  glVertex2f( clockR*rStart*c, clockR*rStart*s);
  glVertex2f( clockR*rEnd*c, clockR*rEnd*s);
}

void jam (void)
{
     glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

  glBegin(GL_LINES);
    for(int i=0; i<60; i++){
      if(i%5){ // normal minute
        if(i%5 == 1)
          glColor3f(1.0f, 1.0f, 1.0f);
        newLine(minStart, minEnd, i*angle1min);
      }else{
        glColor3f(1.0f, 0.0f, 0.0f);
        newLine(stepStart, stepEnd, i*angle1min);
      }
    }
  glEnd();

  glLineWidth(3.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.8f, -angleMin+M_PI/2);
  glEnd();

  glLineWidth(1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.8f, -angleSec+M_PI/2);
  glEnd();
}

void TimerFunction(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);

  angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+
              angleMin/12.0f;

  glutPostRedisplay();
  glutTimerFunc(33,TimerFunction, 1);
}

//AKHIR FUNGSI JAM

void bangun (int w, int h)
{
     if (h == 0)
		h = 1;
	float rasio =  w * 1.0 / h;
     
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();
     glViewport (0,0, w, h);
     gluPerspective(70.0f, rasio, 0.3f, 100.0f);
     glMatrixMode(GL_MODELVIEW);
     glOrtho(0.0,2.0,0.0,2.0,-2.0,2.0);
}

void init (void)
{
     GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
     GLfloat mat_shininess[] = {50.0};
     GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
     GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
     GLfloat lmodel_ambient[] = {0.1, 0.1, 0.1, 1.0}; 
     
     glClearColor (0.0, 0.0, 0.0, 0.0);
     glShadeModel (GL_SMOOTH);
     
     //SHADING
     glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT,GL_SHININESS, mat_shininess);
     glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
     
     
     glEnable(GL_DEPTH_TEST);
      
}

//Garis Koordinat
void koordinatx(void)
{
     glBegin(GL_LINE_STRIP);
     glVertex2f(-4,0);
     glVertex2f(-2.6,0);
     glEnd();
}

void koordinaty(void)
{
     glBegin(GL_LINE_STRIP);
     glVertex2f(0,3);
     glVertex2f(0,-3);
     glEnd();
}

void koordinatz(void)
{
     glBegin(GL_LINE_STRIP);
     glVertex2f(0,0);
     glVertex2f(5.4,3);
     glEnd();
}
// Akhir Garis Koordinat

//kerucut

void cone (float diameter, float tinggi, int garisv, int garish)
{
     glutSolidCone(diameter,tinggi,garisv,garish);
}

void wirecone (float diameter, float tinggi, int garisv, int garish)
{
     glutWireCone(diameter,tinggi,garisv,garish);
}

//BANGUN
void kubus (void)
{
     glutWireCube(0.5);
}
void kubussolid (void)
{
     glutSolidCube(0.5);
}

void bola ()
{
     glutWireSphere(0.5,10,10);
}
void bolasolid (float diameter, int garisv, int garish)
{
     glutSolidSphere(diameter,garisv,garish);
}

void torus(float inner, float outer, int garisv, int garish)
{
     glutWireTorus(inner,outer,garisv,garish);
}

void torussolid(float inner, float outer, int garisv, int garish)
{
     glutSolidTorus(inner,outer,garisv,garish);
}

void icosahedron()
{
     glutWireIcosahedron();
}

void dodecahedron()
{
     glutWireDodecahedron();
}

void dodecahedronsolid()
{
     glutSolidDodecahedron();
}

void kotak ()
{
     glBegin(GL_QUADS);
     glVertex2f(0.1,0.2);
     glVertex2f(0.2,0.2);
     glVertex2f(0.2,0.1);
     glVertex2f(0.1,0.1);
     glEnd();
}
void jendela ()
{
     
}

//AKHIR BANGUN

//CAMERA
void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);
    glRotatef(yrot,0.0,1.0,0.0);
    glTranslated(-xpos,-ypos,-zpos);
}

void display (void)
{
     const double waktu = glutGet (GLUT_ELAPSED_TIME) / 1000.0;
     const double lama1 = 50*waktu, lama2 = 10*waktu, lama3 = waktu/10, lama4=10*waktu;
     GLdouble eqn[4] = {0.0, 0.0, 1.0, 0.0};
     GLdouble eqn2[4] = {1.0, 0.0, 0.0, 0.0};  
     GLdouble eqn3[4] = {0.0, 1.0, 0.0, 0.0};   
     GLfloat mat_transparent[] = { 0.1, 0.8, 0.8, 0.6 };
     GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };
     GLfloat mat_solid[] = { 0.75, 0.75, 0.0, 1.0 };
     GLfloat mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
     //GLfloat light_position[] = {0.0, 0.0, 1.0, 1.0};
          
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glClearColor(0.7,0.7,1.0,0.5);
     
     glLoadIdentity();
     
     //Setting Kamera
     gluLookAt(x, 0.0, z, x+vektorx, 0.0, z+vektorz, 0.0, 1.0, 0.0);
     camera();
     glEnable(GL_TEXTURE_2D);
     glEnable(GL_COLOR_MATERIAL);
     //glColorMaterial(GL_FRONT,GL_SPECULAR);
     glPushMatrix();
      //CLIP untuk Y < 0
     glClipPlane(GL_CLIP_PLANE0,eqn);
     glEnable(GL_CLIP_PLANE0);
     
     //CLIP untuk X < 0
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glPopMatrix();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     
     glPushMatrix();
     glTranslatef(0.0,0.0,-2.0);
     koordinatx();
     glPopMatrix();
     //koordinaty();
     //koordinatz();
     
     //penangkal Petir
     glPushMatrix();
     
     glColor3f(0.0,0.0,0.0);
     glTranslatef(-0.36,0.80,-1.76);
     glScalef(0.05,0.5,0.05);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone (0.5,0.7,30,6);
     glPopMatrix();
  
     
     
     //TANAH
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.0,0.0,0.0);
     glTranslatef(0.0,-1.0,-1);
     glScalef(19.0,0.05,20.0);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     kubussolid();
     
     glPopMatrix();
     //AKHIR TANAH
     
      //trotoar 1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.4,0.7,1.0);
     glTranslatef(0.008,-0.98,-0.26);
     glScalef(0.27,0.02,4.7);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
         //trotoar 2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.632,-0.98,-1.0);
     glScalef(0.27,0.02,4.7);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //trotoar 00
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.5,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 01
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.45,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 02
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.40,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 03
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.35,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 04
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.30,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 05
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.25,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 06
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.20,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 07
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.15,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //trotoar 08
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(0.10,-0.98,0.0);
     glScalef(0.05,0.02,0.25);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //GEDUNG 1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.7,0.4,0.4);
     glTranslatef(1.0,-0.5,-0.8);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.2,2.0,3.9);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     for(int i=0; i<=8; i++)
     {
             for(int j=0; j<6; j++)
             {
      glPushMatrix();
      glTranslatef(0.0,-(j/10.0)*1.5,-(i/10.0)*2.0); 
      
            
     //jendela 1.1
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(1.0,-0.1,0.0);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
     //jendela 1.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(1.0,-0.1,0.03);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
           //jendela 1.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(1.0,-0.1,-0.03);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
      //jendela 1.2.1 (depan)
     for(int i=0; i<=2; i++)
     {
          for(int j=0; j<6; j++)
     {
     glPushMatrix();
     glTranslatef((i/10.0)*2.0,-(j/10.0)*1.5,0.0); 
     glPushMatrix();
     glTranslatef(0.81,0.0,-4.0);
     glScalef(1.0,1.0,3.2);
     glRotatef(-90,0.0,1.0,0.0);        
     //jendela 2.1
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(1.0,-0.1,0.0);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
          //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(1.0,-0.1,0.03);
     glScalef(1.24,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(1.0,-0.1,-0.03);
     glScalef(1.24,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
     //AKHIR JENDELA (DEPAN
     
     //JENDELA GEDUNG 2
     for(int i=0; i<=3; i++)
     {
             for(int j=0; j<4; j++)
             {
      glPushMatrix();
      glTranslatef(0.0,-(j/10.0)*1.5,-(i/10.0)*2.0); 
    
     //jendela 2.1
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
     //jendela gedung double
      for(int i=0; i<=3; i++)
     {
             for(int j=0; j<9; j++)
             {
      glPushMatrix();
      glTranslatef(0.0,-(j/10.0)*1.5,-(i/10.0)*1.75); 
     //jendela 2.1
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(-1.699,0.43,-0.5);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-1.699,0.43,-0.53);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-1.699,0.43,-0.47);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
     //jendela gedung double 2
      for(int i=0; i<=1; i++)
     {
             for(int j=0; j<9; j++)
             {
      glPushMatrix();
      glTranslatef(0.0,-(j/10.0)*1.5,-(i/10.0)*1.255); 
     //jendela 2.1
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(-1.699,0.43,-1.55);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-1.699,0.43,-1.58);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-1.699,0.43,-1.507);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
     //jendela 2.2.1 (depan)
     for(int i=0; i<=2; i++)
     {
          for(int j=0; j<4; j++)
     {
     glPushMatrix();
     glTranslatef((i/10.0)*2.0,-(j/10.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(1.0,1.0,1.32);
     glTranslatef(0.25,0.0,0.74);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.0,0.0,0.8);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.23,0.2,0.25);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
     }
     }
     
     //GEDUNG 2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.7,0.5);
     glTranslatef(-0.36,-0.68,0.5);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.2,1.3,1.6);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
       //GEDUNG 2.1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,0.8,0.5);
     glTranslatef(-0.36,-0.74,0.0);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.2,1.0,1.0);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
        //GEDUNG 2.2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.5,1.0,0.567);
     glTranslatef(-0.36,-0.80,-0.42);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.2,0.85,0.72);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     
     //GEDUNG 2.3
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.5,0.9,0.1);
     glTranslatef(-0.36,-0.63,-1.0);
     glScalef(1.2,1.5,1.6);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
      //GEDUNG 3
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.5,0.8,1.0);
     glTranslatef(-1.7,-0.25,-0.77);
     glScalef(1.2,3.0,1.5);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //GEDUNG 3.2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.5,0.8,1.0);
     glTranslatef(-1.7,-0.25,-1.6);
     glScalef(1.2,3.0,0.6);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //GEDUNG 3 jembatan 1
     glPushMatrix();
     glColor3f(0.3,0.3,0.3);
     glTranslatef(-1.72,-0.25,-1.4);
     glScalef(0.4,0.4,1.0);
     kubussolid();
     glPopMatrix();
     
          //GEDUNG 3 jembatan 2
     glPushMatrix();
     glColor3f(0.3,0.3,0.3);
     glTranslatef(-1.72,0.3,-1.4);
     glScalef(0.4,0.4,1.0);
     kubussolid();
     glPopMatrix();
     
      //GEDUNG 3.1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.3,0.3);
     glTranslatef(-1.88,-0.49,-0.3);
     glScalef(0.5,2.0,0.4);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //GEDUNG 4
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(-1.7,-0.45,0.5);
     glScalef(1.2,2.2,2.0);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //JENDELA
     for (int i=0; i<=5; i++)
     {
     glPushMatrix();
     glColor3f(0.6,0.7,0.4);
     glTranslatef(-1.7,-(i/12.0)*2.0,0.5);
     glScalef(1.5,0.15,2.1);
     kubussolid();
     glPopMatrix();
     }
     //AKHIR JENDELA
     
     //AKHIR GEDUNG 4
     
     //GEDUNG 5
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(-0.36,-0.7,-1.75);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(1.2,1.2,1.2);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //GEDUNG 5.1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(-0.36,-0.15,-1.75);
     glScalef(1.0,2.0,1.0);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //JENDELA
     for (int i=0; i<=5; i++)
     {
     glPushMatrix();
     glColor3f(0.4,0.4,0.7);
     glTranslatef((-i/13.0)-0.16,-0.02,-1.75);
     glScalef(0.07,1.2,1.03);
     kubussolid();
     glPopMatrix();
     }
     
     //AKHIR GEDUNG 5.2
     
          //GEDUNG 5.2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.0,1.0,1.0);
     glTranslatef(-0.36,-0.12,-1.75);
     //glTranslatef(pindahx,pindahy,pindahz);
     glScalef(0.8,3.5,0.8);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //JENDELA
     for (int i=0; i<=4; i++)
     {
     glPushMatrix();
     glColor3f(0.4,0.4,0.7);
     glTranslatef((-i/13.0)-0.20,0.55,-1.75);
     glScalef(0.07,0.7,0.85);
     kubussolid();
     glPopMatrix();
     }
     
     //JAM BIGBANG
     glPushMatrix();
     glColor3f(0.7,0.7,0.7);
     glTranslatef(-0.36,0.55,-1.53);
     glScalef(0.3,0.3,0.01);
     bolasolid(0.5,20,20);
     glPopMatrix();
     
     //JAM
     glPushMatrix();
     glTranslatef(-0.35,0.55,-1.52);
     glScalef(0.3,0.3,0.3);
     jam();
     glPopMatrix();
     //JAM
     
     //AKHIR JAM BIGBANG
     
     //TAMAN KOTA
     glPushMatrix();
     glScalef(1.0,1.0,3.0);
     glTranslatef(0.0,-0.37,0.7);
     glRotatef(90.0,1.0,0.0,0.0);
     glPushMatrix();
     glTranslatef(-1.04,-0.63,0.6);
     glScalef(0.35,0.6,0.15);
     glColor3f(1.0,0.4,0.1);
     kubussolid();
     glPopMatrix();
     
     //TAMAN KOTA STENGAH LINGKARAN
     glPushMatrix();
     glColor3f(0.5,0.5,0.5);
     
     glTranslatef(-1.04,-0.51,0.6);
     glScalef(0.21,0.1,0.15);
     glClipPlane(GL_CLIP_PLANE0,eqn);
     glEnable(GL_CLIP_PLANE0);
     glColor3f(1.0,0.4,0.1);
     bolasolid(0.5,20,20);
     glPopMatrix();
     
     //TAMAN KOTA SETENGAH LINGKARAN
     glPushMatrix();
     glTranslatef(-1.04,-0.75,0.60);
     glScalef(0.21,0.1,0.15);
     glRotatef(180.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE0,eqn);
     glEnable(GL_CLIP_PLANE0);
     glColor3f(1.0,0.4,0.1);
     bolasolid(0.5,20,20);
     glDisable(GL_CLIP_PLANE0);
     glPopMatrix();
     glPopMatrix();
     
     //RUMPUT TAMAN
     glPushMatrix();
     glTranslatef(-1.03,-0.93,0.23);
     glScalef(0.28,0.1,1.3);
     glColor3f(0.3,0.9,0.1);
     kubussolid();
     glPopMatrix(); 
     glPopMatrix();
              
     //AKHIR TAMAN
     
    
     //atap lobby
     glPushMatrix();
     glTranslatef(1.0,-0.82,0.2);
     glScalef(0.3,0.1,0.4);
     glRotatef(0.0,-80.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE0,eqn);
     glEnable(GL_CLIP_PLANE0);
     glColor3f(1.0,0.4,0.1);
     bolasolid(0.5,20,20);
     glDisable(GL_CLIP_PLANE0);
     glPopMatrix();
     glPopMatrix();
     
     //lantai lobby
     glPushMatrix();
     glColor3f(0.5,0.5,0.35);
     glTranslatef(1.0,-0.98,0.25);
     glScalef(0.5,0.03,0.4);
     kubussolid();
     glPopMatrix();
     
       //tiang lobby 1 gedung 1
     glPushMatrix();
     glColor3f(0.9,0.9,0.9);
     glTranslatef(0.9,-0.9,0.3);
     glScalef(0.05,0.35,0.05);
     kubussolid();
     glPopMatrix();
     
     //tiang lobby 2 gedung 1
     glPushMatrix();
     glColor3f(0.9,0.9,0.9);
     glTranslatef(1.1,-0.9,0.3);
     glScalef(0.05,0.35,0.05);
     kubussolid();
     glPopMatrix();
     
     //pintu lobby gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(1.01,-0.9,0.19);
     glScalef(0.27,0.3,0.05);
     kubussolid();
     glPopMatrix();
     
       //pagar gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(1.68,-0.96,-0.49);
     glScalef(0.03,0.2,4.7);
     kubussolid();
     glPopMatrix();
     
          //pagar gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(0.71,-0.96,0.43);
     glScalef(0.03,0.2,1.0);
     kubussolid();
     glPopMatrix();
     
     //pagar gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(0.8,-0.96,0.68);
     glScalef(0.35,0.2,0.03);
     kubussolid();
     glPopMatrix();
     
     //pagar gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(1.4,-0.96,0.68);
     glScalef(1.15,0.2,0.03);
     kubussolid();
     glPopMatrix();
     
          //pagar gedung 1
     glPushMatrix();
     glColor3f(0.8,0.2,0.4);
     glTranslatef(1.46,-0.96,-1.67);
     glScalef(0.88,0.2,0.03);
     kubussolid();
     glPopMatrix();
     
     //mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.8,0.2,0.4);
     glTranslatef(1.9,-0.77,1.47);
     glScalef(1.2,0.8,1.2);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
     //AKHIR JAM BIGBANG
    // AKHIR GEDUNG 5.2
     
     //GEDUNG DIAPIT TABUNG
     for (float i=0; i<7; i++)
     {
     glPushMatrix();
     glTranslatef(-0.2,0.0+(i/5),0.4);
     glRotatef(-90.0,0.0,1.0,0.0);
     //tabung
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glPushMatrix();
     glColor3f(1.2,1.6,0.1);
     glTranslatef(-2.0,-0.94,-2.5);
     glScalef(3.0,5.0,6.0);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.01,0.03,50,50);
     glPopMatrix();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     
         //gedung diapit tabung
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(1.2,1.6,0.1);
     glTranslatef(-1.7,-0.94,-2.5);
     glScalef(1.2,0.2,0.5);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
          //tabung2
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glPushMatrix();
     glColor3f(1.2,1.6,0.1);
     glTranslatef(-1.4,-0.94,-2.5);
     glScalef(3.0,5.0,6.0);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.01,0.03,50,50);
     glPopMatrix();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     
          //tabung2
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glPushMatrix();
     glColor3f(1.0,1.0,0.6);
     glTranslatef(-2.0,-0.842,-2.5);
     glScalef(3.0,5.0,6.0);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.01,0.03,50,50);
     glPopMatrix();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     
         //gedung diapit tabung2
     glPushMatrix();
     glColor3f(1.0,1.0,0.6);
     glTranslatef(-1.7,-0.842,-2.5);
     glScalef(1.2,0.2,0.5);
     kubussolid();
     glPopMatrix();
     
          //tabung22
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glPushMatrix();
     glColor3f(1.0,1.0,0.6);
     glTranslatef(-1.4,-0.842,-2.5);
     glScalef(3.0,5.0,6.0);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.01,0.03,50,50);
     glPopMatrix();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     }
     //AKHIR GEDUNG DIAPIT TABUNG
     
     //GEDUNG X
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(-1.7,0.1,0.7);
     glScalef(0.5,0.35,0.5);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,0.5,0.5);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //atap mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(1.9,-0.58,1.46);
     glScalef(0.5,0.35,0.5);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,1.0,0.6);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //atap mesjid tiang
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(1.555,-0.16,1.85);
     glScalef(0.085,0.13,0.085);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,1.0,0.6);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
      //atap mesjid tiang 2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(1.553,-0.16,1.1);
     glScalef(0.085,0.13,0.085);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,1.0,0.6);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //atap mesjid tiang 3
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(2.2327,-0.16,1.1);
     glScalef(0.085,0.13,0.085);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,1.0,0.6);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
          //atap mesjid tiang 4
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(2.2327,-0.16,1.85);
     glScalef(0.085,0.13,0.085);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,1.0,0.6);
     bolasolid(0.5,20,20);
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     
      //tiang 1 mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.5,0.2);
     glTranslatef(1.55,-0.55,1.85);
     glScalef(0.15,1.65,0.15);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
     //tiang 2 mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.5,0.2);
     glTranslatef(2.23,-0.55,1.85);
     glScalef(0.15,1.65,0.15);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
     //tiang 3 mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.5,0.2);
     glTranslatef(2.23,-0.55,1.10);
     glScalef(0.15,1.65,0.15);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
        //tiang 4 mesjid
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.3,0.5,0.2);
     glTranslatef(1.55,-0.55,1.10);
     glScalef(0.15,1.65,0.15);
     kubussolid();
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glPopMatrix();
     
     
     //jendela mesjid (depan)
     for(int i=0; i<=4; i++)
     {
          for(int j=0; j<2; j++)
     {
     glPushMatrix();
     glTranslatef((i/10.0)*1.2,-(j/10.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(0.18,0.85,0.75);
     glTranslatef(10.0,-0.4,2.317);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //JENDELA SAMPING
     glPushMatrix();
     glScalef(0.93,1.0,1.0);
     glTranslatef(0.15,0.0,3.5);
     for (float i=0; i<4; i++)
     {
         for (int j=0; j<2; j++)
         {
     glPushMatrix();
     glScalef(1.1,1.0,1.1);
     glTranslatef(0.25,-(j/10.0)*1.5,(-i/10.0)*1.3);
     glRotatef(90.0,0.0,1.0,0.0);
     glPushMatrix();
     glScalef(0.18,0.85,0.75);
     glTranslatef(10.0,-0.4,2.317);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
     }
     }
     glPopMatrix();
     //AKHIR JENDELA SAMPING

     //atap 5.1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(-0.36,0.7,-1.75);
     glScalef(0.3,0.25,0.3);
     glRotatef(90.0,0.0,0.0,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn2);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(1.0,0.5,0.5);
     bola();
     //torussolid(0.1,0.1,20,20);
     glDisable(GL_CLIP_PLANE1);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     
     //BILLBOARD 1
     glPushMatrix();
     //glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glColor3f(0.5,0.5,1.0);
     glTranslatef(1.0,0.1,0.15);
     glScalef(3.0,0.25,0.1);
     glRotatef(90,0.0,1.0,0.0);
     torussolid(0.1,0.4,20,20);
     //glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //ATAP
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     //glRotatef(90.0,1.0,0.0,0.0);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     //AKHIR GEDUNG
     
     //GEDUNG BERTINGKAT TANGGA
     glPushMatrix();
     glTranslatef(-3.0,-0.5,1.5);
     glScalef(1.0,2.0,5.0);
     //GEDUNG 1
     for(float i=0; i<5; i++)
     {
     glColor3f(0.5,0.5,0.6);
     glPushMatrix();
     glTranslatef(0.0,i*0.125,-(i*0.075));
     glScalef(1.0,(i+2)/2,0.15);
     kubussolid();
     glColor3f(0.0,0.0,0.0);
     kubus();
     glPopMatrix();
     }
     glPopMatrix();
     
     //JENDELA 1
     for (float i=0; i<=4; i++)
     {
         for (float j=0; j<8; j++)
         {
     glPushMatrix();
     glTranslatef(-2.8-(i/10),-0.08-(j/10),0.75);
     glScalef(0.15,0.2,3.755);
     glColor3f(0.7,0.5,0.7);
     kubussolid();
     glColor3f(1.0,1.0,1.0);
     glScalef(1.01,1.01,1.01);
     kubus();
     glPopMatrix();
     }
     }
     //AKHIR JENDELA 1
     
     //JENDELA 2
     for (float i=0; i<=4; i++)
     {
         for (float j=0; j<4; j++)
         {
     glPushMatrix();
     glTranslatef(-2.8-(i/10),0.4-(j/10),0.565);
     glScalef(0.15,0.2,3.05);
     glColor3f(0.7,0.5,0.7);
     kubussolid();
     glColor3f(1.0,1.0,1.0);
     glScalef(1.01,1.01,1.01);
     kubus();
     glPopMatrix();
     }
     }
     //AKHIR JENDELA 2
     
     //JENDELA 3
     for (float i=0; i<=4; i++)
     {
         for (float j=0; j<4; j++)
         {
     glPushMatrix();
     glTranslatef(-2.8-(i/10),0.9-(j/10),0.378);
     glScalef(0.15,0.2,2.285);
     glColor3f(0.7,0.5,0.7);
     kubussolid();
     glColor3f(1.0,1.0,1.0);
     glScalef(1.01,1.01,1.01);
     kubus();
     glPopMatrix();
     }
     }
     //AKHIR JENDELA 3
     //JENDELA 4
     for (float i=0; i<=4; i++)
     {
         for (float j=0; j<4; j++)
         {
     glPushMatrix();
     glTranslatef(-2.8-(i/10),1.4-(j/10),0.18);
     glScalef(0.15,0.2,1.55);
     glColor3f(0.7,0.5,0.7);
     kubussolid();
     glColor3f(1.0,1.0,1.0);
     glScalef(1.01,1.01,1.01);
     kubus();
     glPopMatrix();
     }
     }
     //AKHIR JENDELA 4
     
      //JENDELA 4
     for (float i=0; i<=4; i++)
     {
         for (float j=0; j<4; j++)
         {
     glPushMatrix();
     glTranslatef(-2.8-(i/10),1.9-(j/10),0.0);
     glScalef(0.15,0.2,0.8);
     glColor3f(0.7,0.5,0.7);
     kubussolid();
     glColor3f(1.0,1.0,1.0);
     glScalef(1.01,1.01,1.01);
     kubus();
     glPopMatrix();
     }
     }
     //AKHIR JENDELA 4
     //AKHIR GEDUNG BERTINGKAT
     
     //MENARA EIFEL
     glPushMatrix();
     glTranslatef(3.5,0.3,-4.0);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     
     //Eifel Tingkat 1
     glPushMatrix();
     glRotatef(45.0,0.0,1.0,0.0);
     
     glPushMatrix();
     glColor3f(0.7,0.6,0.4);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.5,3.0,4,1);
     glColor3f(0.0,0.0,0.0);
     wirecone(0.5,3.0,4,1);
     glPopMatrix();
  
     //Eifel Tingkat 2
     glPushMatrix();
     glColor3f(0.7,0.6,0.4);
     glScalef(1.0,2.2,1.0);
     glTranslatef(0.0,-0.3,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.7,1,4,1);
     glColor3f(0.0,0.0,0.0);
     wirecone(0.7,1,4,1);
     glPopMatrix();
     
     //Eifel Tingkat 3
     glPushMatrix();
     glColor3f(0.7,0.6,0.4);
     glScalef(1.0,2.2,1.0);
     glTranslatef(0.0,-0.6,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(1.0,1.0,4,1);
     glPopMatrix();
     
     
      //Eifel Tingkat Bontot
     glPushMatrix();
     glColor3f(0.7,0.6,0.4);
     glTranslatef(0.0,2.6,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.1,0.3,4,1);
     glPopMatrix();
     
     glPopMatrix();
     
     
     //Kaki Eifel
     glPushMatrix();
     glScalef(1.6,1.6,1.6);
     glTranslatef(0,-0.9,0.0);
     glClipPlane(GL_CLIP_PLANE1,eqn3);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.0,0.0,0.0);
     bolasolid(0.52,20,20);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     //AKHIR KAKI EIFEL
     glPopMatrix();
     //AKHIR MENARA EIFEL
     
     
     
     //AKHIR EIFEL
     
     //PAGODA
     
     glPushMatrix();
     glTranslatef(2.4,-0.8,0.2);
     glScalef(0.5,0.5,0.5);
     
     //Kotak 1
     glPushMatrix();
     glTranslatef(0.0,-0.2,0.0);
     glScalef(2.5,0.8,2.5);
     glColor3f(0.9,0.8,0.8);
     kubussolid();
     glPopMatrix();
     
     //GENTENG 1
     glPushMatrix();
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.6,0.0,0.0);
     cone(1.3,0.8,4,4);
     glPopMatrix();
     //AKHIR GENTENG
     
     //Kotak 2
     glPushMatrix();
     glTranslatef(0.0,0.4,0.0);
     glScalef(2.2,0.8,2.2);
     glColor3f(0.9,0.8,0.8);
     kubussolid();
     glPopMatrix();
     
     //GENTENG 2
     glPushMatrix();
     glScalef(0.9,0.9,0.9);
     glTranslatef(0.0,0.5,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.6,0.0,0.0);
     cone(1.3,0.8,4,4);
     glPopMatrix();
     //AKHIR GENTENG
     
     //Kotak 3
     glPushMatrix();
     glTranslatef(0.0,0.8,0.0);
     glScalef(1.9,0.8,1.9);
     glColor3f(0.9,0.8,0.8);
     kubussolid();
     glPopMatrix();
     
     //GENTENG 3
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(0.0,1.06,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.6,0.0,0.0);
     cone(1.3,0.8,4,4);
     glPopMatrix();
     //AKHIR GENTENG
     
      //Kotak 4
     glPushMatrix();
     glTranslatef(0.0,1.08,0.0);
     glScalef(1.7,0.8,1.7);
     glColor3f(0.9,0.8,0.8);
     kubussolid();
     glPopMatrix();
     
     //GENTENG 4
     glPushMatrix();
     glScalef(0.7,0.6,0.7);
     glTranslatef(0.0,2.06,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.6,0.0,0.0);
     cone(1.3,0.8,4,4);
     glPopMatrix();
     
     glPopMatrix();
     //AKHIR GENTENG
     //AKHIR PAGODA
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     
     //LAMPU LALU LINTAS
     glPushMatrix();
     glTranslatef(0.33,-0.7,0.0);
     glScalef(0.2,0.2,0.2);
     
     glPushMatrix();
     glScalef(2.0,1.5,1.0);
     glClipPlane(GL_CLIP_PLANE1,eqn3);
     glEnable(GL_CLIP_PLANE1);
     torussolid(0.04,0.8,20,30);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     
     //TIANG 1
     glPushMatrix();
     glTranslatef(1.59,-0.8,0.0);
     glScalef(0.2,5.0,0.2);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.2,0.2,20,20);
     glPopMatrix();
     //TIANG 1
     
     //TIANG 2
     glPushMatrix();
     glTranslatef(-1.59,-0.8,0.0);
     glScalef(0.2,5.0,0.2);
     glRotatef(90.0,1.0,0.0,0.0);
     torussolid(0.2,0.2,20,20);
     glPopMatrix();
     //TIANG 2
     
     //BILLBOARD
     glPushMatrix();
     glTranslatef(0.0,0.3,0.0);
     glScalef(4.0,1.0,0.5);
     glColor3f(0.3,0.3,0.3);
     kubussolid();
     glPopMatrix();
     //AKHIR BILLBOARD
     
     //GANTUNGAN
     glPushMatrix();
     glTranslatef(0.6,0.6,0.0);
     glScalef(0.2,2.0,0.2);
     kubussolid();
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-0.6,0.6,0.0);
     glScalef(0.2,2.0,0.2);
     kubussolid();
     glPopMatrix();
     //AKHIR GANTUNGAN
     glPopMatrix();
     
     //LAMPU MERAH
     glPushMatrix();
     glTranslatef(0.2,-0.64,0.0);
     glScalef(0.08,0.08,0.08);
     glColor3f(1.0,0.0,0.0);
     bolasolid(0.5,30,30);
     glPopMatrix();
     //AKHIR LAMPU MERAH
     
     //LAMPU KUNING
     glPushMatrix();
     glTranslatef(0.33,-0.64,0.0);
     glScalef(0.08,0.08,0.08);
     glColor3f(0.8,0.8,0.0);
     bolasolid(0.5,30,30);
     glPopMatrix();
     //AKHIR LAMPU KUNING
     
     //LAMPU HIJAU
     glPushMatrix();
     glTranslatef(0.45,-0.64,0.0);
     glScalef(0.08,0.08,0.08);
     glColor3f(0.0,1.0,0.0);
     bolasolid(0.5,30,30);
     glPopMatrix();
     //AKHIR LAMPU HIJAU
     
     //AKHIR LAMPU LALU LINTAS
     
     
     //MONAS
     glPushMatrix();
     glTranslatef(-3.5,-0.45,-4.5);
     
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     
     //TUGU 1
     glPushMatrix();
     glRotatef(45.0,0.0,1.0,0.0);
     
     glPushMatrix();
     glClipPlane(GL_CLIP_PLANE1,eqn3);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.5,0.5,0.5);
     glScalef(0.65,1.0,0.65);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.5,3.0,4,1);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
  
  
     //Monas Tingkat 2
     glPushMatrix();
     glRotatef(180.0,1.0,0.0,0);
     glColor3f(0.5,0.5,0.5);
     glScalef(1.5,0.6,1.5);
     glTranslatef(0.0,-0.2,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.7,1,4,1);
     glPopMatrix();
     
     
     
      //OBOR
     glPushMatrix();
     glColor3f(1.3,0.2,0.4);
     glTranslatef(0.0,2.66,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     cone(0.1,0.3,4,1);
     glPopMatrix();
     
     glPopMatrix();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     
     //KOTAK
     for (float i=0; i<5; i++)
     {
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,-0.36+(-i/25),0.0);
     glScalef(2.5+(i/5),0.1,2.5+(i/5));
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     }
     //AKHIR KOTAK
     
     //KOTAK penutup
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,0.1,0.0);
     glScalef(3.0,0.15,3.0);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     //AKHIR KOTAK
    
    //KOTAK5
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,2.7,0.0);
     glScalef(0.35,0.1,0.35);
     kubussolid();
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,2.65,0.0);
     glScalef(0.37,0.11,0.37);
     kubussolid(); 
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     //AKHIR KOTAK
     glPopMatrix();
     //AKHIR MONAS
     
  //KACA MINIATUR
     
     
     glPushMatrix();
     //glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
     //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
     glColor3f(0.1,0.1,0.8);
     //glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
      //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
      glEnable(GL_BLEND);
      glDepthMask(GL_TRUE);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
      glTranslatef(0.0,1.2,-0.6);
      glScalef(18.0,9.5,22.0);
     kubussolid(); 
     glDisable(GL_BLEND);
     glPopMatrix();
     //KACA MINIATUR
     
     
   //BALON GAS
   glPushMatrix();
   glRotatef(lama2,0.0,1.0,0.0);glTranslatef(-2,0.0,0.0);
   glPushMatrix();
   glTranslatef(0.0,2.0,0.0);glRotatef(lama1,0.0,1.0,0.2);
     glPushMatrix();
     glColor3f(0.0,0.2,0.4);
     glTranslatef(0.0,1.0,0.0);
     //BOLA ATAS
     glPushMatrix();
     glClipPlane(GL_CLIP_PLANE1,eqn3);
     glEnable(GL_CLIP_PLANE1);
     glScalef(1.0,1.2,1.0);
     glRotatef(90.0,1.0,0.0,0);
     bolasolid(0.499,20,20);
     glColor3f(0.1,0.1,0.1);
     bola();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     //AKHIR BOLA ATAS
     
     //KERUCUT
     glPushMatrix();
     glColor3f(0.1,0.1,0.1);
     glRotatef(90.0,1.0,0.0,0.0);
     wirecone(0.5,1.0,20,20);
     glColor3f(0.0,0.2,0.4);
     cone(0.499,1.0,20,20);
     glPopMatrix();
     //AKHIR KERUCUT
     glPopMatrix();
     
     //LINGKAR BAWAH
     glPushMatrix();
     glColor3f(0.5,0.5,0.0);
     glTranslatef(0.0,0.2,0.0);
     glScalef(0.15,0.1,0.15);
     glRotatef(90.0,1.0,0.0,0.0);
     torus(0.5,0.6,20,20);
     glPopMatrix();
     //AKHIR LINGKAR BAWAH
         
     //TALI
     glPushMatrix();
     glTranslatef(0.0,0.0,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glScalef(0.5,0.5,0.5);
     glColor3f(0.0,0.0,0.0);
     wirecone(0.5,1.0,4,4);
     glPopMatrix();
     //AKHIR TALI
     
     //RUANG
     glPushMatrix();
     glTranslatef(0.0,-0.18,0.0);
     glScalef(0.7,0.7,0.7);
     glColor3f(0.5,0.5,0.0);
     kubussolid();
     glColor3f(0.0,0.0,0.0);
     kubus();
     glPopMatrix();
     //AKHIR RUANG
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
     //AKHIR BALON GAS
     
     glPushMatrix();
     glTranslatef(0.8,-0.8,1.3);
     glPushMatrix();
     glTranslatef(pindahx,pindahz,pindahy);
     glRotatef(putary,0.0,1.0,0.0);
     glPushMatrix();
     glScalef(0.2,0.2,0.2);
     glRotatef(90.0,0.0,1.0,0.0);
     
     //BADAN MOBIL
     glPushMatrix();
     glTranslatef(0.0,-0.135,0.0);
     glScalef(3.0,1.47,2.0);
     glColor3f(0.2,0.5,0.5);
     kubussolid();
     glColor3f(0.8,0.8,0.8);
     kubus();
     glPopMatrix();
     //AKHIR BADAN MOBIL
     
     //KAP MOBIL
     glPushMatrix();
     glTranslatef(-1.13,-0.25,0.0);
     glScalef(1.5,1.0,2.0);
     glColor3f(0.0,0.0,0.0);
     kubussolid();
     glPopMatrix();
     //AKHIR KAP MOBIL
     
     //JENDELA DEPAN
     
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);
     glPushMatrix();glColor3f(0.2,0.0,1.0);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
      glEnable(GL_BLEND);
      glDepthMask(GL_TRUE);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
     glTranslatef(-0.75,0.0,0.0);
     glScalef(0.8,0.7,2.0);
     glRotatef(45,0.0,0.0,1.0);
     
     kubussolid(); 
     glDisable(GL_BLEND);
     glPopMatrix();
     //AKHIR JENDELA
     
         
     //RODA KIRI DEPAN
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(-1.4,-0.6,0.65); 
     glColor3f(0.5,0.5,0.5);
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KIRI DEPAN
     
     //RODA KANAN DEPAN
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(-1.4,-0.6,-0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KANAN DEPAN
     
     //RODA KIRI BELAKANG
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(0.4,-0.6,0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KIRI BELAKANG
     
     //RODA KANAN BELAKANG
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(0.4,-0.6,-0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KANAN BELAKANG
     
     //RODA CADANGAN
     glPushMatrix();
     glTranslatef(0.85,-0.15,0.0);
     glRotatef(90.0,0.0,1.0,0.0);
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA CADANGAN
     
     //LAMPU KIRI
     glPushMatrix();
     glTranslatef(-1.5,-0.25,0.3);
     glScalef(0.1,0.2,0.2);
     glColor3f(0.8,0.8,0.8);
     bolasolid(0.5,20,20);
     glPopMatrix();
     //AKHIR LAMPU KIRI
     
     //LAMPU KANAN
     glPushMatrix();
     glTranslatef(-1.5,-0.25,-0.3);
     glScalef(0.1,0.2,0.2);
     glColor3f(0.8,0.8,0.8);
     bolasolid(0.5,20,20);
     glPopMatrix();
     //AKHIR LAMPU KANAN
     glPopMatrix();
     glPopMatrix();
     glPopMatrix();
     
     //MOBIL BANYAK
     for (float i=0;i<2; i++)
     {
         for (float j=0; j<4; j++)
         {
     glPushMatrix();
     glTranslatef(0.2+(i/5),-0.92,-0.2-(j/3));
     glRotatef(90.0,0.0,1.0,0.0);
     glScalef(0.1,0.1,0.1);
     //BADAN MOBIL
     glPushMatrix();
     glTranslatef(0.0,-0.135,0.0);
     glScalef(3.0,1.47,2.0);
     glColor3f(0.4+((i/5)/(j/8)),0.4+(j/5),0.4+(i/10));
     kubussolid();
     glColor3f(0.8,0.8,0.8);
     kubus();
     glPopMatrix();
     //AKHIR BADAN MOBIL
     
     //KAP MOBIL
     glPushMatrix();
     glTranslatef(-1.13,-0.25,0.0);
     glScalef(1.5,1.0,2.0);
     glColor3f(0.4,0.4+(j/9),0.4+(i/10));
     kubussolid();
     glPopMatrix();
     //AKHIR KAP MOBIL
     
     //JENDELA DEPAN
     
      glPushMatrix();
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_solid);glColor3f(0.1,0.1,1.0);
     //glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent);
      glEnable(GL_BLEND);
      glDepthMask(GL_TRUE);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);
     glTranslatef(-0.75,0.0,0.0);
     glScalef(0.8,0.7,2.0);
     glRotatef(45,0.0,0.0,1.0); 
     kubussolid(); 
     glDisable(GL_BLEND);
     glPopMatrix();
     //AKHIR JENDELA
      
     //RODA KIRI DEPAN
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(-1.4,-0.6,0.65); 
     glColor3f(0.5,0.5,0.5);
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KIRI DEPAN
     
     //RODA KANAN DEPAN
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(-1.4,-0.6,-0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KANAN DEPAN
     
     //RODA KIRI BELAKANG
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(0.4,-0.6,0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KIRI BELAKANG
     
     //RODA KANAN BELAKANG
     glPushMatrix();
     glScalef(0.8,0.8,0.8);
     glTranslatef(0.4,-0.6,-0.65); 
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA KANAN BELAKANG
     
     //RODA CADANGAN
     glPushMatrix();
     glTranslatef(0.85,-0.15,0.0);
     glRotatef(90.0,0.0,1.0,0.0);
     torussolid(0.1,0.2,20,20);
     glPopMatrix();
     //AKHIR RODA CADANGAN
     
     //LAMPU KIRI
     glPushMatrix();
     glTranslatef(-1.5,-0.25,0.3);
     glScalef(0.1,0.2,0.2);
     glColor3f(0.8,0.8,0.8);
     bolasolid(0.5,20,20);
     glPopMatrix();
     //AKHIR LAMPU KIRI
     
     //LAMPU KANAN
     glPushMatrix();
     glTranslatef(-1.5,-0.25,-0.3);
     glScalef(0.1,0.2,0.2);
     glColor3f(0.8,0.8,0.8);
     bolasolid(0.5,20,20);
     glPopMatrix();
     //AKHIR LAMPU KANAN
     glPopMatrix();
     glPopMatrix();
     }
     }
     //AKHIR MOBIL BANYAK
     
     
     //AWAL PARABOLA
     glPushMatrix();
     glTranslatef(1.0,0.1,0.0);
     glScalef(0.5,0.5,0.5);
     glPushMatrix();
     glRotatef(lama4,0.0,1.0,0.0);
     //PARABOLA
     glPushMatrix();
     glTranslatef(-0.1,0.65,0.0);
     glRotatef(-145.0,0.0,0.0,1.0);
     glScalef(1.0,0.4,1.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glClipPlane(GL_CLIP_PLANE1,eqn);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.8,0.8,0.8);
     bola();
     glScalef(0.98,0.98,0.98);
     glColor4f(0.5,0.5,0.2,0.6);
     bolasolid(0.5,20,20);
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-0.12,0.66,0.0);
     glRotatef(-145.0,0.0,0.0,1.0);
     glScalef(1.0,0.4,1.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glClipPlane(GL_CLIP_PLANE1,eqn);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.8,0.8,0.8);
     bola();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     //AKHIR PARABOLA
     glPopMatrix();
     
     //TIANG PARABOLA
     glPushMatrix();
     glScalef(0.2,2.0,0.2);
     kubussolid();
     glPopMatrix();
     //AKHIR TIANG PARABOLA
     glPopMatrix();
     
     //AWAL PARABOLA
     glPushMatrix();
     glTranslatef(-1.6,0.5,-0.7);
     glScalef(0.5,0.5,0.5);
     glPushMatrix();
     glRotatef(lama4,0.0,1.0,0.0);
     //PARABOLA
     glPushMatrix();
     glTranslatef(-0.1,0.65,0.0);
     glRotatef(-145.0,0.0,0.0,1.0);
     glScalef(1.0,0.4,1.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glClipPlane(GL_CLIP_PLANE1,eqn);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.8,0.8,0.8);
     bola();
     glScalef(0.98,0.98,0.98);
     glColor4f(0.5,0.5,0.2,0.6);
     bolasolid(0.5,20,20);
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     
     glPushMatrix();
     glTranslatef(-0.12,0.66,0.0);
     glRotatef(-145.0,0.0,0.0,1.0);
     glScalef(1.0,0.4,1.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glClipPlane(GL_CLIP_PLANE1,eqn);
     glEnable(GL_CLIP_PLANE1);
     glColor3f(0.8,0.8,0.8);
     bola();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     //AKHIR PARABOLA
     glPopMatrix();
     
     //TIANG PARABOLA
     glPushMatrix();
     glScalef(0.2,2.0,0.2);
     kubussolid();
     glPopMatrix();
     //AKHIR TIANG PARABOLA
     glPopMatrix();
     
  
     //GEDUNG SATE
     glPushMatrix();
     glScalef(0.7,0.6,0.5);
     glTranslatef(0.0,-0.0,-7.5);
     
     for(int i=0; i<=6; i++)
     {
          for(int j=0; j<3; j++)
     {
     glPushMatrix();
     glTranslatef((i/6.0)*1.2,-(j/7.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(0.18,1.75,1.9);
     glTranslatef(-11.0,-0.1,0.35);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //jendela kanan
     for(int i=0; i<=6; i++)
     {
          for(int j=0; j<3; j++)
     {
     glPushMatrix();
     glTranslatef((i/6.0)*1.2,-(j/7.0)*1.5,0.0); 
     glPushMatrix();   
     glScalef(0.18,1.75,1.9);
     glTranslatef(6.0,-0.1,0.35);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //jendela kanan
     for(int i=0; i<=5; i++)
     {
          for(int j=0; j<2; j++)
     {
     glPushMatrix();
     glTranslatef((i/6.0)*1.2,-(j/7.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(0.18,1.6,1.7);
     glTranslatef(-9.5,0.4,0.35);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //jendela kanan
     for(int i=0; i<=5; i++)
     {
          for(int j=0; j<2; j++)
     {
     glPushMatrix();
     glTranslatef((i/6.0)*1.2,-(j/7.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(0.18,1.6,1.7);
     glTranslatef(5.5,0.4,0.35);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //jendela kanan
     for(int i=0; i<=5; i++)
     {
          for(int j=0; j<2; j++)
     {
     glPushMatrix();
     glTranslatef((i/6.0)*1.2,-(j/7.0)*1.5,0.0); 
     glPushMatrix();
     glScalef(0.18,1.6,1.7);
     glTranslatef(5.5,0.4,0.35);
     glRotatef(-90.0,0.0,1.0,0.0);
     glPushMatrix();
     glColor3f(0.2,0.2,0.2);
     glTranslatef(-0.36,-0.44,0.8);
     glScalef(1.62,0.43,1.24);
     kubussolid();
     glPopMatrix();
          
     //jendela 2.1.1
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.83);
     glScalef(1.66,0.27,1.0);
     kubussolid();
     glPopMatrix();
     
     //jendela 2.1.2
     glPushMatrix();
     glColor3f(0.7,1.0,0.9);
     glTranslatef(-0.36,-0.44,0.77);
     glScalef(1.26,0.17,0.07);
     kubussolid();
     glPopMatrix();
     glPopMatrix(); 
     glPopMatrix();
     }
     }
     
     //ATAP LANTAI 2 KANAN
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(1.5,0.174,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(1.0,0.36,4,7);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
      //atap ujung kiri
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(-1.5,0.174,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(1.0,0.36,4,7);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     //atap panjang
     glPushMatrix();
     glClipPlane(GL_CLIP_PLANE1,eqn);
     glEnable(GL_CLIP_PLANE1);
     glTranslatef(0.0,0.18,0.0);
     glScalef(6.0,1.0,2.0);
     glRotatef(45.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     kubussolid();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     
      //lagit-langit
     glPushMatrix();
     glTranslatef(0.0,0.15,0.0);
     glScalef(8.8,0.12,2.7);
     glColor3f(0.4,0.0,0.0);
     kubussolid();
     glPopMatrix();
     
     //badan gedung sate
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,-0.25,0.0);
     glScalef(8.0,1.7,2.5);
     glColor3f(0.9,0.8,0.9);
     //glRotatef(45.0,1.0,0.0,0.0);
     kubussolid();
     glDisable(GL_CLIP_PLANE0);
     glDisable(GL_CLIP_PLANE1);
     glPopMatrix();
     // akhir gedung lantai 2
     
     //lantai1
     //atap ujung kanan
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(1.5,-0.66,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(1.3,0.36,4,7);
     glPopMatrix();
     
      //atap ujung kiri
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(-1.5,-0.66,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(1.3,0.36,4,7);
     glPopMatrix();
     
      //lagit-langit kiri
     glPushMatrix();
     glTranslatef(-1.5,-0.69,0.0);
     glScalef(3.63,0.12,3.68);
     glColor3f(0.4,0.0,0.0);
     kubussolid();
     glPopMatrix();
     
     //lagit-langit kanan
     glPushMatrix();
     glTranslatef(1.5,-0.69,0.0);
     glScalef(3.63,0.12,3.68);
     glColor3f(0.4,0.0,0.0);
     kubussolid();
     glPopMatrix();
     
     //badan gedung sate kiri
     glPushMatrix();
     glTranslatef(-1.42,-1.19,0.0);
     glScalef(3.3,1.9,3.0);
     glColor3f(0.9,0.8,0.9);
     kubussolid();
     glPopMatrix();
     // akhir gedung lantai 1
     
       //badan gedung sate kanan
     glPushMatrix();
     glTranslatef(1.42,-1.19,0.0);
     glScalef(3.3,1.9,3.0);
     glColor3f(0.9,0.8,0.9);
     kubussolid();
     glPopMatrix();
     // akhir gedung lantai 1
     
     //badan gedung sate tengah
     glPushMatrix();
     glTranslatef(0.0,-0.47,0.0);
     glScalef(2.38,4.8,3.0);
     glColor3f(0.9,0.8,0.9);
     kubussolid();
     glPopMatrix();
     // akhir gedung lantai 1
     
      //badan gedung lantai 3
     glPushMatrix();
     glTranslatef(0.0,0.85,0.0);
     glScalef(1.8,0.6,1.8);
     glColor3f(0.9,0.8,0.9);
     kubussolid();
     glPopMatrix();
     // akhir gedung lantai 1
     
     //genteng atas 1
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,1.0,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(0.8,0.36,4,7);
     glPopMatrix();
          
     //genteng atas 2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,1.15,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(0.7,0.36,4,7);
     glPopMatrix();
     
     //genteng atas 2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,1.3,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(0.6,0.36,4,7);
     glPopMatrix();
     
     //genteng lantai bawah tengah
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,-1.0,0.5);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(1.0,0.3,4,7);
     glPopMatrix();
     
     //genteng lantai bawah tengah
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,1.6,0.0);
     glRotatef(45.0,0.0,1.0,0.0);
     glRotatef(-90.0,1.0,0.0,0.0);
     glColor3f(0.4,0.0,0.0);
     cone(0.05,0.5,3,7);
     glPopMatrix();
     
     
     //langit2 gedung lantai 1 tengah
     glPushMatrix();
     glTranslatef(0.0,-1.035,0.75);
     glScalef(2.8,0.15,1.8);
     glColor3f(0.4,0.0,0.0);
     kubussolid();
     glPopMatrix();
          // akhir gedung lantai 1
     
     //jendela
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,-0.3,0.02);
     glScalef(0.7,1.0,3.0);
     glColor3f(0.0,0.8,0.9);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     kubussolid();
     glPopMatrix();
     
     //jendela2
     glPushMatrix();
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glTranslatef(0.0,-0.05,0.01);
     glRotatef(45,0,0,1);
     glScalef(0.5,0.5,3.0);
     glColor3f(0.0,0.8,0.8);
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     kubussolid();
     glPopMatrix();
     
     
     // akhir gedung lantai 1
     
     
     //badan gedung lantai 1 tengah
     glPushMatrix();
     glTranslatef(0.0,-1.335,0.75);
     glScalef(2.0,1.3,1.0);
     glColor3f(0.9,0.8,0.9);
     kubussolid();
     glPopMatrix();
     // akhir gedung lantai 1
     
     
     
     glDisable(GL_LIGHTING);
     glDisable(GL_LIGHT0);
     glPopMatrix();
     
     glFlush();
     glutSwapBuffers();
     angle++;
     


}

//FUNGSI KEYBOARD
void keyboard (unsigned char key, int x, int y)
{
     float detik = 1000.0;
     const double time = glutGet(GLUT_ELAPSED_TIME) / detik;
     
     switch (key){
            case 'w':
            case 'W':
                 xrot += 1;
              if (xrot >360) 
              xrot -= 360;
            break;
            case 's':
            case 'S':
                  xrot -= 1;
              if (xrot < -360) 
              xrot += 360;
            break;
            case 'a':
            case 'A':
                 yrot += 1;
              if (yrot >360) 
              yrot -= 360;
            break;
            case 'd':
            case 'D':
                 yrot -= 1;
              if (yrot < -360)
              yrot += 360;
            //case 'q':
            //case 'Q':
            break;
            case 'f':
            case 'F':
                 putary -= 90;
              if (putary < -360)
              putary += 360;
            break;
            case 'h':
            case 'H':
                 putary += 90;
              if (putary >360) 
              putary -= 360;
            break;
            case 27:
                  //glutLeaveGameMode();
                 exit (0);
                }
     
}

void mouse(int klik, int state, int xx, int yy)
{
     
     switch(klik){
                  case GLUT_LEFT_BUTTON:
                       
                       if((putary==-270)||(putary==90))
                       {
                       pindahx  +=0.1f;
                       }
                       if((putary==180)||(putary==-180))
                       {
                       pindahy  -=0.1f;
                       }
                       if((putary==-90)||(putary==270))
                       {
                       pindahx  -=0.1f;
                       }
                       if((putary==0) || (putary==360) || (putary==-360))
                       {
                       pindahy  +=0.1f;
                       }
                  }
}

void ketik(int key, int xx, int yy)
{
     int mod;
     float fraksi = 0.1f;
          switch(key){
         case GLUT_KEY_F1:
              mod = glutGetModifiers();
              if(mod == (GLUT_ACTIVE_ALT)){
                     sumbux=1.0;
                     sumbuy=0.0;
                     sumbuz=0.0;
                     }
              break;
         case GLUT_KEY_F2:
              sumbux=0.0;
              sumbuy=1.0;
              sumbuz=0.0;
              break;
         case GLUT_KEY_F3:
              sumbux=0.0;
              sumbuy=0.0;
              sumbuz=1.0;
              break;
         case GLUT_KEY_LEFT:
              sudut -=0.01f;
              vektorx = sin(sudut);
              vektorz = -cos(sudut);
              break;
         case GLUT_KEY_RIGHT:
              sudut += 0.01f;
			  vektorx = sin(sudut);
			  vektorz = -cos(sudut);
			break;
         case GLUT_KEY_UP:
              x += vektorx * fraksi;
			  z += vektorz * fraksi;
			break;
         case GLUT_KEY_DOWN:
              x -= vektorx * fraksi;
			  z -= vektorz * fraksi;
         break; 
         case GLUT_KEY_PAGE_UP:
              xrot += 1;
              if (xrot >360) 
              xrot -= 360;
         break;
         case GLUT_KEY_PAGE_DOWN:
              xrot -= 1;
              if (xrot < -360) 
              xrot += 360;
         break;
         case GLUT_KEY_HOME:
              yrot -= 1;
              if (yrot < -360)
              yrot += 360;
         break;
         case GLUT_KEY_END:
              yrot += 1;
              if (yrot >360) 
              yrot -= 360;
         }
              
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //glutGameModeString( "1024×768:32@75" ); //the settings for fullscreen mode
    //glutEnterGameMode(); //set glut to fullscreen using the settings in the line above
    glutInitWindowSize(1010,690);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Program Tugas Besar");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(bangun);
    glutTimerFunc(33, TimerFunction, 1);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(ketik);
    glutMouseFunc(mouse);
    
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    return 0;
}
