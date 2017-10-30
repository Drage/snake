
#include "Graphics.h"
#include "Time.h"
#include "Input.h"
#include <cmath>

#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <GLUT/glut.h>
#else
#include <GL/gl.h> 
#include <GL/glut.h>
#endif

Fonts Font = 
{
	GLUT_BITMAP_8_BY_13,
	GLUT_BITMAP_HELVETICA_10,
	GLUT_BITMAP_TIMES_ROMAN_10
};

Colour::Colour()
{
	r = 0;
	g = 0;
	b = 0;
	a = 1;
}

Colour::Colour(float r, float g, float b, float a)
{
	if (r > 1) r /= 255.0f;
	if (g > 1) g /= 255.0f;
	if (b > 1) b /= 255.0f;
	if (a > 1) a /= 255.0f;
	
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Colour::operator float*() const
{
	static float colourArray[4];
	colourArray[0] = r;
	colourArray[1] = g;
	colourArray[2] = b;
	colourArray[3] = a;
	return colourArray;
}

Colour Colour::operator= (const Colour &other)
{
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
}

bool Colour::operator== (const Colour &other)
{
	float epsilon = std::numeric_limits<float>::epsilon();
	return (abs(r - other.r) < epsilon && abs(g - other.g) < epsilon && abs(b - other.b) < epsilon && abs(a - other.a) < epsilon);
}


UpdateFunc UpdateCallback;
RenderFunc RenderCallback;

Timer frameTimer;

void DisplayEvent()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderCallback();
	glutSwapBuffers();
}

void UpdateEvent(int fps)
{
	glutTimerFunc(1000 / fps, UpdateEvent, fps);
	UpdateCallback(frameTimer.ElapsedSeconds());
	frameTimer.Reset();
	DisplayEvent();
}

void InitWindow(int width, int height, const std::string &caption, const Colour &colour)
{	
	int argc = 0;
	char *argv = NULL;

	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(caption.c_str());
	
	glClearColor(colour.r, colour.g, colour.b, 1);
	
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
	glOrtho(0, GetWindowWidth(), 0, GetWindowHeight(), -1, 1);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	
	InitInput();
}

void RunApp(int fps, UpdateFunc update, RenderFunc render)
{
	UpdateCallback = update;
	RenderCallback = render;
	
	glutDisplayFunc(DisplayEvent);
	glutTimerFunc(1000 / fps, UpdateEvent, fps);
	frameTimer.Start();
	glutMainLoop();
}

int GetWindowWidth()
{
	return glutGet(GLUT_WINDOW_WIDTH);
}

int GetWindowHeight()
{
	return glutGet(GLUT_WINDOW_HEIGHT);
}

void RenderRectangle(int x, int y, int w, int h, const Colour &colour)
{
	glColor3fv(colour);
	glBegin(GL_QUADS);
	glVertex2s(x, y);
	glVertex2s(x + w, y);
	glVertex2s(x + w, y + h);
	glVertex2s(x, y + h);
	glEnd();
}

void RenderRectangle(int x, int y, int w, int h, const Colour &colour, const Colour &border)
{
	glBegin(GL_QUADS);
	glColor3fv(border);
	glVertex2s(x, y);
	glVertex2s(x + w, y);
	glVertex2s(x + w, y + h);
	glVertex2s(x, y + h);
	glColor3fv(colour);
	glVertex2s(x+1, y+1);
	glVertex2s(x+1 + w-2, y+1);
	glVertex2s(x+1 + w-2, y+1 + h-2);
	glVertex2s(x+1, y+1 + h-2);
	glEnd();
}


void RenderText(int x, int y, void *font, const std::string &text, const Colour &colour) 
{ 
	glColor3fv(colour);
    glRasterPos2f((float)x, (float)y);
	int i;
    for (i = 0; i < text.length(); i++)
        glutBitmapCharacter(font, text[i]);
}
