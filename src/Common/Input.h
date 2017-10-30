
#ifndef INPUT_H
#define INPUT_H

// Current keyboard state
struct KeyInfo
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool enter;
	bool escape;
};
typedef struct KeyInfo KeyInfo;
extern KeyInfo Key;

void InitInput();

#endif
