#include "GameTriger.h"

/**
 * @brief Konstruktor klasy GameTriger.
 * @param id Identyfikator obiektu.
 * @param name Nazwa obiektu.
 * @param Type Typ obiektu (ShapeType).
 */
GameTriger::GameTriger(int id, std::string name, ShapeType Type)
    : GameObject(id, name, Type) {}

/**
 * @brief Dodaje funkcję wyzwalacza.
 * @param func Funkcja wyzwalacza.
 */
void GameTriger::AddTriger(std::function<void(GameObject&, GameObject*&, std::vector<GameObject*>*)> func) {
    Trigers.push_back(std::move(func));
}

/**
 * @brief Aktualizuje funkcje wyzwalacza w zależności od warunków.
 * @param obj Wskaźnik do obiektu, który może być używany w funkcjach wyzwalaczy.
 * @param objects Wektor obiektów, który może być używany w funkcjach wyzwalaczy.
 */
void GameTriger::Update(GameObject*& obj, std::vector<GameObject*>* objects) {
    for (const auto& trig : Trigers)
        trig(*this, obj, objects);
}
