
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

// Built-in GLUT fonts
struct Fonts
{
	void *fixed;
	void *helvetica;
	void *timesNewRoman;
};
typedef struct Fonts Fonts;
extern Fonts Font;

// Colours
struct Colour
{
	float r;
	float g;
	float b;
	float a;
	
	Colour();
	Colour(float r, float g, float b, float a = 1);
	operator float*() const;
	Colour operator= (const Colour &other);
	bool operator== (const Colour &other);
};

// Function callback types for update and render events
typedef void (*UpdateFunc)(double);
typedef void (*RenderFunc)(void);

// Initialization
void InitWindow(int width, int height, const std::string &caption, const Colour &colour);
void RunApp(int fps, UpdateFunc update, RenderFunc render);

// Window dimensions
int GetWindowWidth();
int GetWindowHeight();

// Render
void RenderRectangle(int x, int y, int w, int h, const Colour &colour);
void RenderRectangle(int x, int y, int w, int h, const Colour &colour, const Colour &border);
void RenderText(int x, int y, void *font, const std::string &text, const Colour &colour);

#endif
