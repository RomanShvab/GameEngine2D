/**
 * @file
 * @brief Zawiera definicje klasy GameObject oraz jej pochodnych, Animation, GameInputSuport, GameTriger, Player i Coin.
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>

#include "GameObject.h"
#include "GameInputSuport.h"
#include "Animation.h"
#include "GameEngine.h"

int main() {
	GameEngine Engine(1280, 720, "");
	Engine.Run();

	return 0;
}