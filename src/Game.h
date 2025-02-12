#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "GameExceptions.h"
#include "DrawableObject.h"
#include "Indicator.h"
#include "MoveableIndicator.h"
#include "Platform.h"
#include "Player.h"
#include "Fight.h"
#include "Wind.h"
#include "SnowballEnemy.h"
#include "GraphicResourcesManager.h"
#include "AudioResourcesManager.h"
#include "GameObjectFactory.h"

class Game {
public:
    // Singleton: Returns a reference to the single Game instance
    static Game& getInstance(const sf::String& player1name_, const sf::String& player2name_);

    // Main game loop
    void Run();

    // Delete copy constructor and copy assignment operator.
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    // Constructor and destructor
    Game(const sf::String& player1name, const sf::String& player2name);
    ~Game();

    // Updates all the entities
    void Update();

    // Checks collisions between all the entities
    void SolveCollisions();

    // Checks for a winner and updates it
    void CheckWinner();

    // When the winning player finished its sounds, closes the window
    void ResetGame();

    // Draws a banner on top of the winner
    void ShowWinner();

    // Draws the screen
    void Draw();

    // Checks events
    void CheckEvents();

private:
    sf::RenderWindow window;
    GraphicResourcesManager graphicResources;
    AudioResourcesManager audioResources;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    Player *winner;
    Player *loser;

    std::unique_ptr<Fight> fight;

    std::unique_ptr<SnowballEnemy> snowballEnemy;

    std::unique_ptr<Indicator> fightBanner;
    std::unique_ptr<MoveableIndicator> winnerBanner;

    std::unique_ptr<Wind> wind;

    std::unique_ptr<Platform> ground;
    std::unique_ptr<Platform> leftWall;
    std::unique_ptr<Platform> rightWall;

    sf::Clock clock;
    float deltaTime;
};

#endif // OOP_GAME_H
