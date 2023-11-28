#include "GameObject.h"

/**
 * @brief Konstruktor klasy GameObject.
 * @param id Identyfikator obiektu.
 * @param name Nazwa obiektu.
 * @param Type Typ kształtu obiektu.
 */
GameObject::GameObject(int id, std::string name, ShapeType Type)
    : drawable(nullptr),
    id(id),
    name(name) {
    switch (Type) {
    case GameObject::Square:
        drawable = new sf::RectangleShape(sf::Vector2f(1, 1));
        setOutlineThickness(1);
        break;
    case GameObject::Circle:
        drawable = new sf::CircleShape(0.5);
        setOutlineThickness(1);
        break;
    case GameObject::Triangle:
        drawable = new sf::ConvexShape(3);
        setPoint(0, sf::Vector2f(-0.5f, -0.2886f));
        setPoint(1, sf::Vector2f(0.5f, -0.2886f));
        setPoint(2, sf::Vector2f(0.0f, 0.5773f));
        setOutlineThickness(1);
        break;
    case GameObject::Polyhedron:
        drawable = new sf::ConvexShape(0);
        setOutlineThickness(1);
        break;
    case GameObject::Sprite:
        drawable = new sf::Sprite();
        break;
    }
}

/**
 * @brief Ustawia liczbę punktów obiektu.
 * @param count Liczba punktów.
 */
void GameObject::SetPointCount(unsigned int count) {
    if (auto ConvexPtr = dynamic_cast<sf::ConvexShape*>(drawable))
        ConvexPtr->setPointCount(count);
}

/**
 * @brief Ustawia pozycję punktu o określonym indeksie.
 * @param index Indeks punktu.
 * @param position Pozycja punktu.
 */
void GameObject::setPoint(unsigned int index, sf::Vector2f position) {
    if (auto ConvexPtr = dynamic_cast<sf::ConvexShape*>(drawable))
        ConvexPtr->setPoint(index, sf::Vector2f(position.x, -position.y));
}

/**
 * @brief Ustawia pozycję obiektu.
 * @param x Współrzędna x.
 * @param y Współrzędna y.
 */
void GameObject::setPosition(float x, float y) {
    if (auto TransPtr = dynamic_cast<sf::Transformable*>(drawable)) {
        TransPtr->setPosition(x, -y);
    }
}

/**
 * @brief Ustawia rozmiar obiektu.
 * @param width Szerokość.
 * @param height Wysokość.
 */
void GameObject::setSize(float width, float height) {
    if (drawable) {
        if (auto ShapePtr = dynamic_cast<sf::Shape*>(drawable)) {
            ShapePtr->setScale(sf::Vector2f(width, height));
        }
        else if (sf::Sprite* SpritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
            SpritePtr->setScale(width / SpritePtr->getLocalBounds().width, height / SpritePtr->getLocalBounds().height);
        }
    }
    setOrigin();
}

/**
 * @brief Ustawia grubość obrysu obiektu.
 * @param thickness Grubość obrysu.
 */
void GameObject::setOutlineThickness(float thickness) {
    if (sf::Shape* shape = dynamic_cast<sf::Shape*>(drawable)) {
        shape->setOutlineThickness(thickness / 100);
    }
}

/**
 * @brief Ustawia kolor obrysu obiektu.
 * @param color Kolor obrysu.
 */
void GameObject::setOutlineColor(sf::Color color) {
    if (sf::Shape* shape = dynamic_cast<sf::Shape*>(drawable)) {
        shape->setOutlineColor(color);
    }
}

/**
 * @brief Ustawia kolor wypełnienia obiektu.
 * @param color Kolor wypełnienia.
 */
void GameObject::setColor(sf::Color color) {
    if (sf::Shape* shape = dynamic_cast<sf::Shape*>(drawable)) {
        shape->setFillColor(color);
    }
}

/**
 * @brief Ustawia punkt obrotu obiektu.
 * @param x Współrzędna x punktu obrotu.
 * @param y Współrzędna y punktu obrotu.
 */
void GameObject::setOrigin(float x, float y) {
    if (auto TransPtr = dynamic_cast<sf::Transformable*>(drawable)) {
        TransPtr->setOrigin(x / 100, y / 100);
    }
    if (auto SpritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
        SpritePtr->setOrigin(SpritePtr->getGlobalBounds().width / 20, SpritePtr->getGlobalBounds().height / 20);
    }
}

/**
 * @brief Ładuje teksturę z pliku i ustawia ją na obiekcie.
 * @param LoadFromFile Ścieżka do pliku z teksturą.
 */
void GameObject::setTexture(const std::string LoadFromFile) {
    texture.loadFromFile(LoadFromFile);
    if (drawable) {
        if (sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(drawable)) {
            sprite->setTexture(texture);
        }
        else if (sf::Shape* shape = dynamic_cast<sf::Shape*>(drawable)) {
            sf::Sprite* newSprite = new sf::Sprite(texture);
            newSprite->setPosition(shape->getPosition());
            newSprite->setRotation(shape->getRotation());
            newSprite->setScale(shape->getScale());
            newSprite->setOrigin(shape->getOrigin());
            drawable = newSprite;
        }
    }
}

/**
 * @brief Przesuwa obiekt o określone wartości współrzędnych.
 * @param x Przesunięcie względem osi x.
 * @param y Przesunięcie względem osi y.
 */
void GameObject::Move(float x, float y) {
    if (auto TransPtr = dynamic_cast<sf::Transformable*>(drawable))
        TransPtr->move(sf::Vector2f(x, -y));
}

/**
 * @brief Obraca obiekt o określony kąt.
 * @param degree Kąt obrotu w stopniach.
 */
void GameObject::Rotate(float degree) {
    if (auto TransPtr = dynamic_cast<sf::Transformable*>(drawable))
        TransPtr->rotate(degree);
}

/**
 * @brief Zwraca globalne granice obiektu.
 * @return Obiekt sf::FloatRect reprezentujący granice obiektu.
 */
sf::FloatRect GameObject::GetGlobalBounds() {
    if (auto spritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
        return spritePtr->getGlobalBounds();
    }
    else if (auto shapePtr = dynamic_cast<sf::Shape*>(drawable)) {
        return shapePtr->getGlobalBounds();
    }
    return sf::FloatRect();
}

/**
 * @brief Sprawdza, czy obiekt przecina się z innym obiektem.
 * @param obj Drugi obiekt do sprawdzenia kolizji.
 * @return Wartość logiczna informująca o tym, czy obiekty się przecinają.
 */
bool GameObject::Intersects(GameObject& obj) {
    if (&obj == nullptr || drawable == nullptr)
        return false;
    if (auto intersectsSpritePtr = dynamic_cast<sf::Sprite*>(drawable)) {
        if (auto objSpritePtr = dynamic_cast<sf::Sprite*>(obj.drawable)) {
            return intersectsSpritePtr->getGlobalBounds().intersects(objSpritePtr->getGlobalBounds());
        }
        else if (auto objShapePtr = dynamic_cast<sf::Shape*>(obj.drawable)) {
            return intersectsSpritePtr->getGlobalBounds().intersects(objShapePtr->getGlobalBounds());
        }
    }
    else if (auto intersectsShapePtr = dynamic_cast<sf::Shape*>(drawable)) {
        if (auto objSpritePtr = dynamic_cast<sf::Sprite*>(obj.drawable)) {
            return intersectsShapePtr->getGlobalBounds().intersects(objSpritePtr->getGlobalBounds());
        }
        else if (auto objShapePtr = dynamic_cast<sf::Shape*>(obj.drawable)) {
            return intersectsShapePtr->getGlobalBounds().intersects(objShapePtr->getGlobalBounds());
        }
    }
    return false;
}

/**
 * @brief Rysuje obiekt na oknie.
 * @param window Referencja do okna, na którym rysować.
 */
void GameObject::DrawObject(sf::RenderWindow& window) {
    window.draw(*drawable);
}

/**
 * @brief Destruktor klasy GameObject.
 */
GameObject::~GameObject() {
}
