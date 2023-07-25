#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 100
#define SCREEN_Y 25

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 12


Scene::Scene()
{
	map = NULL;
	player = NULL;
	bground = NULL;

}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (bground != NULL)
		delete bground;
}


void Scene::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	initShaders();
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	background = TileMap::createTileMap("levels/background.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player->setStrawberryDispl(glm::fvec2(0, 0));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	level = 1;
	nextLevel = false;


}


void Scene::update(int deltaTime)
{
	if (Game::instance().getWinner()) {
		credits.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	if (map->goNextLevel()) nextLevel = true;
	else nextLevel = false;
	currentTime += deltaTime;
	if (Game::instance().getKey('1')) {
		level = 1;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize());
		player->setStrawberryDispl(glm::fvec2(0, 0));
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('2') || (nextLevel && level == 1)) {
		level = 2;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 32 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 32 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('3') || (nextLevel && level == 2)) {
		level = 3;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 48 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 48 * map->getTileSize());
		player->setStrawberryDispl(glm::fvec2(0, 0));
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('4') || (nextLevel && level == 3)) {
		level = 4;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 66 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 66 * map->getTileSize());
		player->setStrawberryDispl(glm::fvec2(0, 0));
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('5') || (nextLevel && level == 4)) {
		level = 5;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 84 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 84 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('6') || (nextLevel && level == 5)) {
		level = 6;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 102 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 102 * map->getTileSize());
		player->resetLevel();
		player->setBalloonDispl(glm::fvec2(0, 0));
		nextLevel = false;
	}
	if (Game::instance().getKey('7') || (nextLevel && level == 6)) {
		level = 7;
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), 120 * map->getTileSize()));
		player->setInitialPosition((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), 120 * map->getTileSize());
		player->setStrawberryDispl(glm::fvec2(0, 0));
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('8') || (nextLevel && level == 7)) {
		level = 8;
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 138 * map->getTileSize()));
		player->setInitialPosition(INIT_PLAYER_X_TILES * map->getTileSize(), 138 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('9') || (nextLevel && level == 8)) {
		level = 9;
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), 156 * map->getTileSize()));
		player->setInitialPosition((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), 156 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('0') || (nextLevel && level == 9)) {
		level = 10;
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), 174 * map->getTileSize()));
		player->setInitialPosition((INIT_PLAYER_X_TILES + 1) * map->getTileSize(), 174 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	if (Game::instance().getKey('f') || (nextLevel && level == 10)) {
		level = 11;
		int score = player->getScore();
		player->setPosition(glm::vec2((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), 192 * map->getTileSize()));
		player->setInitialPosition((INIT_PLAYER_X_TILES + 2) * map->getTileSize(), 192 * map->getTileSize());
		player->resetLevel();
		nextLevel = false;
	}
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0, -432 * (level - 1), 0));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	player->update(deltaTime, level);
}

void Scene::render()
{
	if (Game::instance().getWinner()) {
		glm::mat4 modelview;
		texProgram.use();
		texProgram.setUniformMatrix4f("projection", projection);
		texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
		texProgram.setUniformMatrix4f("modelview", modelview);
		bground->render(credits);
	}
	else {
		background->render();
		map->render();
		player->render(level);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



