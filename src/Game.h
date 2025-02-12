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
#include "GraphicResourcesManager.h"
#include "AudioResourcesManager.h"

class Game {
public:
    // Constructor and destructor
    Game(const sf::String& player1name, const sf::String& player2name);
    ~Game();

    // Main game loop
    void Run();

private:

    // Updates all the entities
    void Update();

    // Checks collisions between all the entities
    void CheckCollisions();

    // Checks for a winner and updates it
    void CheckWinner();

    // When the winning player finished its sounds, closes the window
    void ExitWhenGameFinished();

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

    Player player1;
    Player player2;
    Player* winner;
    Fight fight;

    Indicator fightBanner;
    MoveableIndicator winnerBanner;

    Wind wind;

    Platform ground;
    Platform leftWall;
    Platform rightWall;

    sf::Clock clock;
    float deltaTime;
};

#endif // OOP_GAME_H
