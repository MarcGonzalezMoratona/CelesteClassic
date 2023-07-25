#include "Menu.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <GL/glut.h>

Menu::Menu() {
	bground = NULL;	
	currentTime = 0.0f;
	bChanging = false;
	id = 0;
}

Menu::~Menu() {
	if (bground != NULL) delete bground;
}

void Menu::init() {
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(640.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	initShaders();
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	
	// Load textures
	title.loadFromFile("images/title.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuA.loadFromFile("images/MENU_A.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuB.loadFromFile("images/MENU_B.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuC.loadFromFile("images/MENU_C.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	credits.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	scene = title;
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	// MENU SCENE CHANGES
	if (id == 1 && !Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getKey(13)) bChanging = false;
	if (id == 2 && !Game::instance().getSpecialKey(GLUT_KEY_DOWN) && !Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getKey(13)) bChanging = false;
	if (id == 3 && !Game::instance().getSpecialKey(GLUT_KEY_UP) && !Game::instance().getKey(13)) bChanging = false;
	if (id == 4 && !Game::instance().getKey(8)) bChanging = false;
	if (id == 5 && !Game::instance().getKey(8)) bChanging = false;
	if (id == 6) Game::instance().start();
	if (bChanging) return;

	if (id == 0) {
		if (Game::instance().getKey(13)) {
			scene = menuA;
			bChanging = true;
			id = 1;
		}
	} 
	else if (id == 1) {
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			id = 2;
			scene = menuB;
			bChanging = true;
		}
		else if (Game::instance().getKey(13)) {
			id = 6;
			scene = play;
			bChanging = true;
		}
	}
	else if (id == 2) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			id = 1;
			scene = menuA;
			bChanging = true;
		}
		else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN)){
			id = 3;
			scene = menuC;
			bChanging = true;
		}
		else if (Game::instance().getKey(13)) {
			id = 4;
			scene = instructions;
			bChanging = true;
		}
	}
	else if (id == 3) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			id = 2;
			scene = menuB;
			bChanging = true;
		}
		else if (Game::instance().getKey(13)) {
			id = 5;
			scene = credits;
			bChanging = true;
		}
	}
	else if (id == 4) {
		if (Game::instance().getKey(8)) {
			id = 2;
			scene = menuB;
			bChanging = true;
		}
	}
	else if (id == 5) {
		if (Game::instance().getKey(8)) {
			id = 3;
			scene = menuC;
			bChanging = true;
		}
	}
}


void Menu::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview); 
	bground->render(scene);
}


void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
}
