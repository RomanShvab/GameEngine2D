#include "Animation.h"

/**
 * @brief Konstruktor klasy Animation.
 * @param id Identyfikator obiektu.
 * @param name Nazwa obiektu.
 * @param imageCount Liczba klatek animacji.
 * @param switchTime Czas trwania jednej klatki animacji.
 * @param pixelWidth Szerokość pojedynczej klatki animacji w pikselach.
 * @param pixelHeight Wysokość pojedynczej klatki animacji w pikselach.
 */
Animation::Animation(int id, std::string name, int imageCount, float switchTime, int pixelWidth, int pixelHeight)
    : GameObject(id, name, GameObject::Sprite),
    imageCount(imageCount),
    currentImage(0),
    switchTime(switchTime),
    totalTime(0.0f),
    uvRect(0, 0, pixelWidth, pixelHeight),
    pixelWidth(pixelWidth),
    pixelHeight(pixelHeight) {}

/**
 * @brief Aktualizuje animację na podstawie upływu czasu.
 * @param deltaTime Czas od ostatniej aktualizacji.
 */
void Animation::Update(float deltaTime) {
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage++;

        if (currentImage >= imageCount) {
            currentImage = 0;
        }
    }

    uvRect.left = currentImage * uvRect.width;

    if (auto SpritePtr = dynamic_cast<sf::Sprite*>(drawable))
        SpritePtr->setTextureRect(uvRect);
}

/**
 * @brief Ustawia rozmiar animacji.
 * @param width Nowa szerokość animacji.
 * @param height Nowa wysokość animacji.
 */
void Animation::setSize(float width, float height) {
    if (drawable) {
        if (sf::Sprite* SpritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
            SpritePtr->setScale(width / SpritePtr->getLocalBounds().width * imageCount, height / SpritePtr->getLocalBounds().height);
        }
    }
    setOrigin();
}

/**
 * @brief Ustawia punkt obrotu animacji.
 * @param x Współrzędna x punktu obrotu.
 * @param y Współrzędna y punktu obrotu.
 */
void Animation::setOrigin(float x, float y) {
    if (auto SpritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
        SpritePtr->setOrigin(SpritePtr->getGlobalBounds().width / 20 / imageCount, SpritePtr->getGlobalBounds().height / 20);
    }
}
