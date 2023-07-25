#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "ShaderProgram.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"

class Menu {
public:
	Menu();
	~Menu();

	void init();
	void render();
	void update(int deltaTime);
private:
	void initShaders();

private:
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Texture scene, title, menuA, menuB, menuC, instructions, credits, play;
	ShaderProgram texProgram;
	int id; // 0 TITLE, 1 MENU A, 2 MENU B, 3 MENU C, 4 INSTRUCTIONS, 5 CREDITS, 6 PLAY
	bool bChanging;
};

#endif // _MENU_INCLUDE