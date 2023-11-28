#include "GameEngine.h"

/**
 * @brief Funkcja wykonująca ruch w prawo.
 * @param obj Wskaźnik do obiektu, który ma wykonać ruch.
 */
void MoveRight(GameObject* obj) {
    obj->Move(0.1, 0);
}

/**
 * @brief Funkcja wykonująca ruch w lewo.
 * @param obj Wskaźnik do obiektu, który ma wykonać ruch.
 */
void MoveLeft(GameObject* obj) {
    obj->Move(-0.1, 0);
}

/**
 * @brief Funkcja wykonująca ruch w górę.
 * @param obj Wskaźnik do obiektu, który ma wykonać ruch.
 */
void MoveUp(GameObject* obj) {
    obj->Move(0, 0.1);
}

/**
 * @brief Funkcja wykonująca ruch w dół.
 * @param obj Wskaźnik do obiektu, który ma wykonać ruch.
 */
void MoveDown(GameObject* obj) {
    obj->Move(0, -0.1);
}

/**
 * @brief Funkcja usuwająca obiekt, gdy zachodzi kolizja.
 * @param first Pierwszy obiekt.
 * @param second Wskaźnik do drugiego obiektu.
 * @param objects Wektor przechowujący wskaźniki do obiektów.
 */
void Delete(GameObject& first, GameObject*& second, std::vector<GameObject*>* objects)
{
    if (first.Intersects(*second))
    {
        for (auto obj = objects->begin(); obj != objects->end();)
        {
            if (*obj == second)
            {
                (void)objects->erase(obj);
                delete second;
                second = nullptr;
                return;
            }
            else {
                ++obj;
            }
        }
    }
}

/**
  * @brief Przykładowa klasa reprezentująca Gracza
  */
class Player : public Animation, public GameInputSuport, public GameTriger {
private:
    int Score;
public:
    Player() : 
        Animation(0, "Player", 4, 0.1, 16, 23), 
        GameInputSuport(0, "Player", GameObject::Sprite), 
        GameTriger(0, "Player", GameObject::Sprite), 
        Score(0) {}

    void IncreaseScore(int val)
    {
        Score += val;
    }

    int GetScore()
    {
        return Score;
    }
};

/**
  * @brief Przykładowa klasa reprezentująca Gracza
  */
class Coin : public Animation
{
public:
    Coin(int coinId) : Animation(coinId, "Coin", 4, 0.1, 6, 7) {}

};

/**
 * @brief Funkcja uruchamiająca główną pętlę gry.
 */
void GameEngine::Run() {
    // Utwórz obiekt tła gry.
    GameObject* BackGround = new GameObject(7, "BG", GameObject::Sprite);
    BackGround->setTexture("Background.png");
    BackGround->setSize(1280, 720);
    BackGround->setPosition(-524, 279);
    addObject(BackGround);

    // Utwórz wektor monet.
    std::vector<Coin*> Coins;
    Coins.emplace_back(new Coin(1));
    Coins.emplace_back(new Coin(2));
    Coins.emplace_back(new Coin(3));
    Coins.emplace_back(new Coin(4));
    Coins[0]->setPosition(180, 270);
    Coins[1]->setPosition(-180, 270);
    Coins[2]->setPosition(180, -270);
    Coins[3]->setPosition(-180, -270);

    // Ustaw tekstury i rozmiary monet.
    for (auto& coins : Coins)
    {
        coins->setTexture("Sprite-0001.png");
        coins->setSize(30, 35);
        addObject(coins);
    }

    GameObject* CoinPtr;

    // Utwórz obiekt gracza.
    Player* Hero = new Player();
    Hero->Animation::setTexture("Sprite-0002.png");
    Hero->Animation::setSize(80, 115);
    Hero->GameInputSuport::AddFunction(MoveRight, sf::Keyboard::D);
    Hero->GameInputSuport::AddFunction(MoveUp, sf::Keyboard::W);
    Hero->GameInputSuport::AddFunction(MoveDown, sf::Keyboard::S);
    Hero->GameInputSuport::AddFunction(MoveLeft, sf::Keyboard::A);
    Hero->GameTriger::AddTriger(Delete);
    Hero->GameTriger::setTexture("Sprite-0002.png");
    Hero->GameTriger::setSize(80, 115);
    addObject(static_cast<GameObject*>(static_cast<Animation*>(Hero)));

    // Utwórz obiekty do wyświetlania liczby punktów.
    GameObject* Number1 = new GameObject(5, "Num1", GameObject::Sprite);
    GameObject* Number10 = new GameObject(6, "Num10", GameObject::Sprite);
    Number1->setTexture("0.png");
    Number1->setPosition(-575, 345);
    Number1->setSize(40, 40);
    addObject(Number1);
    Number10->setTexture("0.png");
    Number10->setPosition(-615, 345);
    Number10->setSize(40, 40);
    addObject(Number10);

    // Tablica z teksturami cyfr.
    std::string NumTextures[10];
    NumTextures[0] = "0.png";
    NumTextures[1] = "1.png";
    NumTextures[2] = "2.png";
    NumTextures[3] = "3.png";
    NumTextures[4] = "4.png";
    NumTextures[5] = "5.png";
    NumTextures[6] = "6.png";
    NumTextures[7] = "7.png";
    NumTextures[8] = "8.png";
    NumTextures[9] = "9.png";

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        Time = clock.restart().asSeconds();

        Hero->Animation::Update(Time);
        Hero->GameInputSuport::Update(static_cast<GameObject*>(static_cast<Animation*>(Hero)));
        Hero->GameInputSuport::Update(static_cast<GameObject*>(static_cast<GameTriger*>(Hero)));

        // Aktualizuj monety i sprawdź kolizje.
        for (auto coins = Coins.begin(); coins != Coins.end();)
        {
            CoinPtr = *coins;
            Hero->GameTriger::Update(CoinPtr, &objects);
            if (CoinPtr != nullptr)
            {
                (*coins)->Update(Time);
                ++coins;
            }
            else {
                coins = Coins.erase(coins);
                Hero->IncreaseScore(1);
                Number10->setTexture(NumTextures[Hero->GetScore() % 100 - Hero->GetScore() % 10]);
                Number1->setTexture(NumTextures[Hero->GetScore() % 10]);
            }
        }

        window->clear();
        for (auto& obj : objects) {
            obj->DrawObject(*window);
        }
        window->display();
    }
}