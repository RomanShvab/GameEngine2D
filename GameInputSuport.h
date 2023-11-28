/**
 * @file GameInputSuport.h
 *
 * @class GameInputSuport
 * @brief Klasa obsługująca wejście w grze.
 *
 * Klasa dziedziczy po GameObject i umożliwia dodawanie funkcji obsługi wejścia,
 * takich jak reakcje na klawisze klawiatury lub przyciski myszy.
 */
#pragma once

#include "GameObject.h"

class GameInputSuport : public GameObject {
protected:
    std::map<sf::Keyboard::Key, std::function<void(GameObject*)>> keyboardFunctions; ///< Mapa funkcji obsługi klawiatury.
    std::map<sf::Mouse::Button, std::function<void(GameObject*)>> mouseFunctions; ///< Mapa funkcji obsługi myszy.

public:
    /**
     * @brief Konstruktor klasy GameInputSuport.
     * @param id Identyfikator obiektu.
     * @param name Nazwa obiektu.
     * @param Type Typ obiektu (ShapeType).
     */
    GameInputSuport(int id, std::string name, ShapeType Type);

    /**
     * @brief Dodaje funkcję obsługi klawiatury dla danego klawisza.
     * @param func Funkcja obsługi.
     * @param key Klawisz klawiatury.
     */
    void AddFunction(std::function<void(GameObject*)> func, sf::Keyboard::Key key);

    /**
     * @brief Dodaje funkcję obsługi myszy dla danego przycisku.
     * @param func Funkcja obsługi.
     * @param key Przycisk myszy.
     */
    void AddFunction(std::function<void(GameObject*)> func, sf::Mouse::Button key);

    /**
     * @brief Aktualizuje funkcje obsługi w zależności od stanu klawiatury i myszy.
     * @param obj Wskaźnik do obiektu, na którym mają być wykonane funkcje obsługi.
     */
    void Update(GameObject* obj);

    /**
     * @brief Destruktor klasy GameInputSuport.
     */
    ~GameInputSuport();
};
