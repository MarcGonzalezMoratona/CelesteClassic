#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "TexturedQuad.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map;
	TileMap *background;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	glm::mat4 modelview;
	glm::vec3 mapposition;
	int level;
	bool nextLevel;
	TexturedQuad* bground;
	Texture credits;
};


#endif // _SCENE_INCLUDE

