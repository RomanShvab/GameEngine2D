/**
 * @file Animation.h
 *
 * @class Animation
 * @brief Klasa reprezentująca animowany obiekt w grze.
 *
 * Klasa dziedziczy po GameObject i dodaje funkcje obsługi animacji, takie jak zmiana klatki animacji, aktualizacja czasu itp.
 */
#pragma once

#include "GameObject.h"

class Animation : public GameObject {
private:
    int imageCount; ///< Liczba klatek animacji.
    int currentImage; ///< Aktualna klatka animacji.
    float totalTime; ///< Całkowity czas trwania animacji.
    float switchTime; ///< Czas trwania jednej klatki animacji.
    sf::IntRect uvRect; ///< Prostokąt tekstury używany do wyciągania odpowiedniej klatki animacji.
    int pixelWidth; ///< Szerokość pojedynczej klatki animacji w pikselach.
    int pixelHeight; ///< Wysokość pojedynczej klatki animacji w pikselach.

public:
    /**
     * @brief Konstruktor klasy Animation.
     * @param id Identyfikator obiektu.
     * @param name Nazwa obiektu.
     * @param imageCount Liczba klatek animacji.
     * @param switchTime Czas trwania jednej klatki animacji.
     * @param pixelWidth Szerokość pojedynczej klatki animacji w pikselach.
     * @param pixelHeight Wysokość pojedynczej klatki animacji w pikselach.
     */
    Animation(int id, std::string name, int imageCount, float switchTime, int pixelWidth, int pixelHeight);

    /**
     * @brief Aktualizuje animację na podstawie upływu czasu.
     * @param deltaTime Czas od ostatniej aktualizacji.
     */
    void Update(float deltaTime);

    /**
     * @brief Ustawia rozmiar animacji.
     * @param width Nowa szerokość animacji.
     * @param height Nowa wysokość animacji.
     */
    void setSize(float width, float height) override;

    /**
     * @brief Ustawia punkt obrotu animacji.
     * @param x Współrzędna x punktu obrotu.
     * @param y Współrzędna y punktu obrotu.
     */
    void setOrigin(float x = 50, float y = 50) override;
};
