#include "GameInputSuport.h"

/**
 * @brief Konstruktor klasy GameInputSuport.
 * @param id Identyfikator obiektu.
 * @param name Nazwa obiektu.
 * @param Type Typ obiektu (ShapeType).
 */
GameInputSuport::GameInputSuport(int id, std::string name, ShapeType Type)
	: GameObject(id, name, Type) {}

/**
 * @brief Dodaje funkcję obsługi klawiatury dla danego klawisza.
 * @param func Funkcja obsługi.
 * @param key Klawisz klawiatury.
 */
void GameInputSuport::AddFunction(std::function<void(GameObject*)> func, sf::Keyboard::Key key) {
	keyboardFunctions[key] = func;
}

/**
 * @brief Dodaje funkcję obsługi myszy dla danego przycisku.
 * @param func Funkcja obsługi.
 * @param key Przycisk myszy.
 */
void GameInputSuport::AddFunction(std::function<void(GameObject*)> func, sf::Mouse::Button key) {
	mouseFunctions[key] = func;
}

/**
 * @brief Aktualizuje funkcje obsługi w zależności od stanu klawiatury i myszy.
 * @param obj Wskaźnik do obiektu, na którym mają być wykonane funkcje obsługi.
 */
void GameInputSuport::Update(GameObject* obj) {
	for (const auto& func : mouseFunctions)
		if (sf::Mouse::isButtonPressed(func.first))
			func.second(obj);
	for (const auto& func : keyboardFunctions)
		if (sf::Keyboard::isKeyPressed(func.first))
			func.second(obj);
}

/**
 * @brief Destruktor klasy GameInputSuport.
 */
GameInputSuport::~GameInputSuport()
{
	mouseFunctions.clear();
	keyboardFunctions.clear();
}
