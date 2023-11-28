#include "GameEngine.h"

/**
 * @brief Konstruktor klasy GameEngine.
 * @param screenWidth Szerokość ekranu.
 * @param screenHeight Wysokość ekranu.
 * @param windowTitle Tytuł okna gry.
 */
GameEngine::GameEngine(int screenWidth, int screenHeight, std::string windowTitle)
    : Time(0.0)
{
    window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), windowTitle);
    camera = new sf::View(sf::FloatRect(0, 0, screenWidth, screenHeight));
    camera->setCenter(sf::Vector2f(0, 0));
    window->setView(*camera);
}

/**
 * @brief Dodaje obiekt do wektora obiektów gry.
 * @param obj Wskaźnik do dodawanego obiektu.
 */
void GameEngine::addObject(GameObject* obj) {
    objects.push_back(obj);
}
