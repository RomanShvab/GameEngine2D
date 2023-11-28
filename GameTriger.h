/**
 * @file GameTriger.h
 *
 * @class GameTriger
 * @brief Klasa reprezentująca obiekt wyzwalacza w grze.
 *
 * Klasa dziedziczy po GameObject i umożliwia dodawanie funkcji wyzwalacza, które są wywoływane przy określonych warunkach.
 */
#pragma once

#include "GameObject.h"

class GameTriger : public GameObject {
protected:
    std::vector<std::function<void(GameObject&, GameObject*&, std::vector<GameObject*>*)>> Trigers; ///< Wektor funkcji wyzwalaczy.

public:
    /**
     * @brief Konstruktor klasy GameTriger.
     * @param id Identyfikator obiektu.
     * @param name Nazwa obiektu.
     * @param Type Typ obiektu (ShapeType).
     */
    GameTriger(int id, std::string name, ShapeType Type);

    /**
     * @brief Dodaje funkcję wyzwalacza.
     * @param func Funkcja wyzwalacza.
     */
    void AddTriger(std::function<void(GameObject&, GameObject*&, std::vector<GameObject*>*)> func);

    /**
     * @brief Aktualizuje funkcje wyzwalacza w zależności od warunków.
     * @param obj Wskaźnik do obiektu, który może być używany w funkcjach wyzwalaczy.
     * @param objects Wektor obiektów, który może być używany w funkcjach wyzwalaczy.
     */
    void Update(GameObject*& obj, std::vector<GameObject*>* objects);
};
