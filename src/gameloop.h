#include "map.h"
#pragma once

struct GameLoop {
public:
	void Draw();
	void Update();
	void Input();
private:
	SpiralMap spiralMap;
	SpiralConfig config;
public:
	GameLoop();
};
