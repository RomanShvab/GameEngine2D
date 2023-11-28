/**
 * @file GameEngine.h
 *
 * @class GameEngine
 * @brief Klasa obsługująca silnik gry.
 *
 * Klasa zarządza główną pętlą gry, obiektami, oknem oraz widokiem kamery.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Animation.h"
#include "GameInputSuport.h"
#include "GameTriger.h"

class GameEngine {
private:
    sf::RenderWindow* window; ///< Wskaźnik do obiektu okna gry.
    sf::View* camera; ///< Wskaźnik do obiektu widoku kamery.
    std::vector<GameObject*> objects; ///< Wektor przechowujący wskaźniki do obiektów gry.
    sf::Clock clock; ///< Obiekt zegara używany do pomiaru czasu.
    float Time; ///< Aktualny czas gry.

public:
    /**
     * @brief Konstruktor klasy GameEngine.
     * @param screenWidth Szerokość ekranu.
     * @param screenHeight Wysokość ekranu.
     * @param windowTitle Tytuł okna gry.
     */
    GameEngine(int screenWidth, int screenHeight, std::string windowTitle);

    /**
     * @brief Dodaje obiekt do wektora obiektów gry.
     * @param obj Wskaźnik do dodawanego obiektu.
     */
    void addObject(GameObject* obj);

    /**
     * @brief Uruchamia główną pętlę gry.
     */
    void Run();
};
