#include "initShaders.h"
#include "vec.h"
#include<math.h>  // Including math functions

using namespace std;

const int numpoints=6;
int counter=0;
float pi=3.141592;
float theta =0;
float R=0.5;

GLuint vaoID, vboID;



void square(){                // Drawing a rectangle
	
	vec2 points_square[numpoints]={
		vec2(0.5,0.0),
		vec2(-0.5,0.0),
		vec2(0.5,0.5),
		vec2(-0.5,0.5),
		vec2(0.5,0.5),
		vec2(-0.5,0.0)
	};

	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points_square),points_square,GL_STATIC_DRAW);
	
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShaders(shaders);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES,0,numpoints);
	glFlush();
}



void triangle(){                // Drawing a triangle
	
	vec2 points_tri[3]={
		vec2(0.5,0.0),
		vec2(-0.5,0.0),
		vec2(0.0,0.5),
		
	};

	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points_tri),points_tri,GL_STATIC_DRAW);
	
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShaders(shaders);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES,0,3);
	glFlush();
}



void hex(){                // Drawing a star, created this as a combination of two triangles
	
	theta=-pi/6;
	
	vec2 points_hex[6];
	
	for (int j=0;j<3;j++)
	{
	  points_hex[j]= vec2 (R*cos(theta+2*j*pi/3),R*sin(theta+2*j*pi/3));// coordinates of one triangle for the star
	};
	
	theta =pi/6;

	for (int j=3;j<6;j++)
	{
	  points_hex[j]= vec2 (R*cos(theta+2*(j-3)*pi/3),R*sin(theta+2*(j-3)*pi/3));
	};
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points_hex),points_hex,GL_STATIC_DRAW);
	
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader2.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShaders(shaders);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES,0,6);
	glFlush();

}




void drawscene(){
  switch(counter%3){// selection of the figure
    case 0:
      glutDisplayFunc(square);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 1:
      glutDisplayFunc(triangle);
      glutPostRedisplay();
    break;
     case 2:
      glutDisplayFunc(hex);
      glutPostRedisplay();
    break;
  }
}



//Interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    counter++;
    drawscene();
  }
}


void idle(void){
  glutPostRedisplay();
}



int main(int argc, char **argv){
	
	glutInit(&argc,argv);
	glutCreateWindow("dots");

	
	glewExperimental=GL_TRUE;
	if(glewInit()){
		fprintf(stderr,"unable to initialize GLEW");
		exit(EXIT_FAILURE);
	}
	
	glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);
 
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);
	
  glutDisplayFunc(drawscene); //display function
  glutMouseFunc(mousepress);
  glutMainLoop();
  return 0;
}

