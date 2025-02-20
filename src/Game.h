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
#include "Singleton.h"

class Game : public Singleton<Game> {
public:
    // Singleton: Returns a reference to the single Game instance
    static Game& getInstance();

    // Main game loop
    void Run();

    // Delete copy constructor and copy assignment operator.
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

private:
    // Constructor and destructor
    Game();
    ~Game();

    // Print game information
    void PrintGameInfo() const;

    // Updates all the entities
    void Update();

    // Handles collisions between the players and the platform
    static void HandlePlatformCollisions(Player* player, const std::vector<Collider*>& platforms, float push);

    // Solves collisions between all the entities
    void SolveCollisions();

    // Checks for a winner and updates it
    void CheckWinner();

    // When the winning player finished its sounds, closes the window
    void ResetGame();

    // Draws a banner on top of the winner
    void ShowWinner();

    // Returns true if the game has been won
    bool GameWon() const;

    // Returns true if the game has been won and
    // the dying sound has finished playing
    bool GameFinished() const;

    // Draws the screen
    void Draw();

    // Checks events
    void CheckEvents();

private:
    friend class Singleton<Game>;

    sf::RenderWindow window;
    GraphicResourcesManager graphicResources;
    AudioResourcesManager audioResources;

    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    Player *winner;
    Player *loser;

    Fight *fight;

    std::unique_ptr<SnowballEnemy> snowballEnemy;

    std::unique_ptr<Wind> wind;

    std::unique_ptr<Platform> ground;
    std::unique_ptr<Platform> leftWall;
    std::unique_ptr<Platform> rightWall;
    // [0] fightBanner, [1] winnerBanner, [2] replayBanner
    std::vector<std::unique_ptr<Indicator>> indicators;

    sf::Clock clock;
    float deltaTime;
};

#endif // OOP_GAME_H
