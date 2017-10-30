
#include "Input.h"
#include "Graphics.h"
#include <stdlib.h>
#include <map>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <GLUT/glut.h>
#else
#include <GL/gl.h> 
#include <GL/glut.h>
#endif

KeyInfo Key;

typedef std::map<int, bool*> KeyMap;
KeyMap keyMap;

void Keyboard(unsigned char key, int x, int y)
{	
	KeyMap::iterator i = keyMap.find((int)key);
	if (i != keyMap.end())
		*keyMap[(int)key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	KeyMap::iterator i = keyMap.find((int)key);
	if (i != keyMap.end())
		*keyMap[(int)key] = false;
}

void Special(int key, int x, int y)
{
	KeyMap::iterator i = keyMap.find((int)key);
	if (i != keyMap.end())
		*keyMap[key] = true;
}

void SpecialUp(int key, int x, int y)
{
	KeyMap::iterator i = keyMap.find((int)key);
	if (i != keyMap.end())
		*keyMap[key] = false;
}

void InitInput()
{
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(Special);
	glutSpecialUpFunc(SpecialUp);
	
	memset(&Key, 0, sizeof(Key));
	keyMap[GLUT_KEY_UP] = &Key.up;
	keyMap[GLUT_KEY_DOWN] = &Key.down;
	keyMap[GLUT_KEY_LEFT] = &Key.left;
	keyMap[GLUT_KEY_RIGHT] = &Key.right;
	keyMap[13] = &Key.enter;
	keyMap[27] = &Key.escape;
}
