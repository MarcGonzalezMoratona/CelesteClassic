#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include <vector>
#include <irrklang.h>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime, int level);
	void render(int level);

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setInitialPosition(int X, int Y);
	bool spriteCollision(Sprite* s1, Sprite* s2, bool isWall);
	bool platformCollision(Sprite* s1, Sprite* s2);
	bool cloudCollision(Sprite *s1, Sprite *s2);
	void resetLevel();
	void setStrawberryDispl(glm::dvec2 strawberryDispl);
	void setBalloonDispl(glm::dvec2 strawberryDispl);

	int getScore();

private:
	bool bJumping, bClimbing, bClimbJumping, bDashing, bGrabbing, bWallBroken, bStrawberryCollected, strawberryUp, balloonUp, bSpringJump;
	glm::ivec2 tileMapDispl, posPlayer;
	glm::dvec2 strawberryDispl, balloonDispl;
	int jumpAngle, climbJumpAngle, dashAngle, startY, initialX, initialY, dashDirection, dashY, cloudDispl;
	int strawberries;
	vector<int> platformFrames;
	vector<bool> bBalloonsCollected;
	Texture spritesheet, tilesheet;
	Sprite *sprite, *strawberry, *springLeft, *springRight, *balloon[2], * rope[2], * wall, * wing[2], * platforms[12], * cloud[10];
	TileMap *map;
	bool bGodMode, bSlowMode, bDashMode, bChanging;

	irrklang::ISoundEngine* engine;
	irrklang::ISound* strawberrysfx;
};


#endif // _PLAYER_INCLUDE


