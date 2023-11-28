#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>

 /**
  * @brief Klasa reprezentująca obiekt w grze.
  */
class GameObject {
protected:
    std::string name; /**< Nazwa obiektu. */
    int id; /**< Identyfikator obiektu. */
    sf::Drawable* drawable; /**< Wskaźnik na obiekt rysowalny. */
    sf::Texture texture; /**< Tekstura obiektu. */

public:
    /**
     * @brief Enumeracja określająca różne kształty obiektu.
     */
    enum ShapeType {
        Square, /**< Kwadrat. */
        Circle, /**< Okrąg. */
        Triangle, /**< Trójkąt. */
        Polyhedron, /**< Wielościan (niezaimplementowany). */
        Sprite /**< Sprite. */
    };

    /**
     * @brief Konstruktor klasy GameObject.
     * @param id Identyfikator obiektu.
     * @param name Nazwa obiektu.
     * @param Type Typ kształtu obiektu.
     */
    GameObject(int id, std::string name, ShapeType Type);

    /**
     * @brief Ustawia liczbę punktów obiektu.
     * @param count Liczba punktów.
     */
    void SetPointCount(unsigned int count);

    /**
     * @brief Ustawia pozycję punktu o określonym indeksie.
     * @param index Indeks punktu.
     * @param position Pozycja punktu.
     */
    void setPoint(unsigned int index, sf::Vector2f position);

    /**
     * @brief Ustawia pozycję obiektu.
     * @param x Współrzędna x.
     * @param y Współrzędna y.
     */
    void setPosition(float x, float y);

    /**
     * @brief Ustawia rozmiar obiektu.
     * @param width Szerokość.
     * @param height Wysokość.
     */
    virtual void setSize(float width, float height);

    /**
     * @brief Ustawia grubość obrysu obiektu.
     * @param thickness Grubość obrysu.
     */
    void setOutlineThickness(float thickness);

    /**
     * @brief Ustawia kolor obrysu obiektu.
     * @param color Kolor obrysu.
     */
    void setOutlineColor(sf::Color color);

    /**
     * @brief Ustawia kolor wypełnienia obiektu.
     * @param color Kolor wypełnienia.
     */
    void setColor(sf::Color color);

    /**
     * @brief Ustawia punkt obrotu obiektu.
     * @param x Współrzędna x punktu obrotu.
     * @param y Współrzędna y punktu obrotu.
     */
    virtual void setOrigin(float x = 50, float y = 50);

    /**
     * @brief Ładuje teksturę z pliku i ustawia ją na obiekcie.
     * @param LoadFromFile Ścieżka do pliku z teksturą.
     */
    void setTexture(const std::string LoadFromFile);

    /**
     * @brief Przesuwa obiekt o określone wartości współrzędnych.
     * @param x Przesunięcie względem osi x.
     * @param y Przesunięcie względem osi y.
     */
    void Move(float x, float y);

    /**
     * @brief Obraca obiekt o określony kąt.
     * @param degree Kąt obrotu w stopniach.
     */
    void Rotate(float degree);

    /**
     * @brief Zwraca globalne granice obiektu.
     * @return Obiekt sf::FloatRect reprezentujący granice obiektu.
     */
    sf::FloatRect GetGlobalBounds();

    /**
     * @brief Sprawdza, czy obiekt przecina się z innym obiektem.
     * @param obj Drugi obiekt do sprawdzenia kolizji.
     * @return Wartość logiczna informująca o tym, czy obiekty się przecinają.
     */
    bool Intersects(GameObject& obj);

    /**
     * @brief Rysuje obiekt na oknie.
     * @param window Referencja do okna, na którym rysować.
     */
    void DrawObject(sf::RenderWindow& window);

    /**
     * @brief Destruktor klasy GameObject.
     */
    ~GameObject();
};