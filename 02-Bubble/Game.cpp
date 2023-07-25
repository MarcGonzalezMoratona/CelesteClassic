#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>

using namespace std;

void Game::init()
{
	// DEBUG CONSOLE
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	// start the sound engine with default parameters
	engine = irrklang::createIrrKlangDevice();

	if (!engine)
		return; // error starting up the engine

	  // play some sound stream, looped
	titlemusic = engine->play2D("music/title.mp3", true, false, true);

	// INIT VARIABLES
	bPlay = true;
	winner = false;
	id = 0;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	menu.init();
}

void Game::start() {
	startsfx = engine->play2D("sfx/start.mp3", false, false, true);
	titlemusic->stop();
	titlemusic->drop();
	while (!startsfx->isFinished()) {}
	stagemusic = engine->play2D("music/stages.mp3", true, false, true);
	scene.init();
	id = 6;
}

void Game::win() {
	winner = true;
}

bool Game::getWinner() {
	return winner;
}

bool Game::update(int deltaTime)
{
	if(id==0) menu.update(deltaTime);
	else if (id == 6) scene.update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (id == 0) menu.render();
	else if (id == 6) scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) { // Escape code
		engine->drop();
		if (startsfx) startsfx->drop();
		if (titlemusic) titlemusic->drop();
		if (stagemusic) stagemusic->drop();
		bPlay = false;
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}


