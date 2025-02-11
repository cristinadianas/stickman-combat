#include <iostream>
#include <array>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "GameExceptions.h"
#include "Drawable.h"
#include "Indicator.h"
#include "MoveableIndicator.h"
#include "Platform.h"
#include "Player.h"
#include "Fight.h"
#include "Wind.h"
// #include <Helper.h>
// #include "env_fixes.h"


void checkAllCollisions(Player &player1, Player &player2,
                        Platform &ground, Platform &leftWall, Platform &rightWall) {
    // If a collision on the bottom is detected, then IsOnGround will become true
    player1.SetIsOnGround(false);
    player2.SetIsOnGround(false);

    sf::Vector2f direction;

    if(ground.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if(ground.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if(leftWall.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if(leftWall.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if(rightWall.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if(rightWall.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if(player1.GetCollider().CheckCollision(player2.GetCollider(), direction, 0.5f))
    {
        player1.OnCollision(-direction);
        player2.OnCollision(direction);
    }
}

bool checkEndOfGame(Player &player1, Player &player2) {
    if(player1.IsWinner() || player2.IsWinner())
        return true;
    return false;
}

void update(float deltaTime, Player &player1, Player &player2, Fight &fight,
            Wind &wind, MoveableIndicator &winnerBanner) {
    wind.Update(deltaTime);
    player1.Update(deltaTime);
    player2.Update(deltaTime);
    fight.Update();

    if(checkEndOfGame(player1, player2)) {
        sf::Vector2f winnerPosition;
        if (player1.IsWinner())
            winnerPosition = player1.GetPosition();
        else if (player2.IsWinner())
            winnerPosition = player2.GetPosition();

        winnerBanner.SetPosition(sf::Vector2f(winnerPosition.x, winnerPosition.y - OFFSET_BANNER));
    }
}

void draw(sf::RenderWindow &window, const sf::Sprite &background, bool endOfGame,
          const Drawable &player1, const Drawable &player2,
          const Drawable &fightBanner, const Wind &wind,
          const MoveableIndicator &winnerBanner) {
    window.clear();

    window.draw(background);

    wind.Draw(window);
    fightBanner.Draw(window);
    if(endOfGame)
        winnerBanner.Draw(window);

    player1.Draw(window);
    player1.DrawHealthBar(window);

    player2.Draw(window);
    player2.DrawHealthBar(window);

    window.display();
}

int main() {
    try {
        // Render the window in which the game will take place
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stickman Combat", sf::Style::Default);

        // Load all the textures
        sf::Texture playerTexture;
        if (!playerTexture.loadFromFile("../textures/player_texture.png"))
            throw TextureLoadException("../textures/player_texture.png");

        sf::Texture transparentTexture;
        if (!transparentTexture.loadFromFile("../textures/transparent_texture.png"))
            throw TextureLoadException("../textures/transparent_texture.png");

        sf::Texture heartTexture;
        if (!heartTexture.loadFromFile("../textures/heart_texture.png"))
            throw TextureLoadException("../textures/heart_texture.png");

        sf::Texture fightBannerTexture;
        if (!fightBannerTexture.loadFromFile("../textures/fight_banner_texture.png"))
            throw TextureLoadException("../textures/fight_banner_texture.png");

        sf::Texture windTexture;
        if(!windTexture.loadFromFile("../textures/wind_texture.png"))
            throw TextureLoadException("../textures/fight_banner_texture.png");

        sf::Texture winnerBannerTexture;
        if (!winnerBannerTexture.loadFromFile("../textures/winner_texture.png"))
            throw TextureLoadException("../textures/winner_texture.png");

        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("../textures/background.png"))
            throw TextureLoadException("../textures/background.png");

        sf::Sprite background(backgroundTexture);

        // Fit background correctly into window
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        float ScaleX = (float) windowSize.x / (float) textureSize.x;
        float ScaleY = (float) windowSize.y / (float) textureSize.y;
        background.setTexture(backgroundTexture);
        background.setScale(ScaleX, ScaleY);

        // Set up background music
        sf::Music backgroundMusic;
        if(!backgroundMusic.openFromFile("../sounds/bg_music.wav"))
            throw SoundException("../sounds/bg_music.wav");
        backgroundMusic.play();
        backgroundMusic.setLoop(true);

        // Initialize all game parametres
        Player player1(player1Name,
                       &playerTexture, imageCountPlayer, SWITCHTIME_PLAYER,
                       SPEED, JUMP_HEIGHT, player1SpawnPosition,
                       NR_HEARTS, healthBar1Position);
        Player player2(player2Name,
                       &playerTexture, imageCountPlayer, SWITCHTIME_PLAYER,
                       SPEED, JUMP_HEIGHT, player2SpawnPosition,
                       NR_HEARTS, healthBar2Position,
                       false, false,
                       sf::Keyboard::U, sf::Keyboard::J, sf::Keyboard::H, sf::Keyboard::K,
                       sf::Keyboard::I);

        player1.InitializeHealthBar(&heartTexture);
        player2.InitializeHealthBar(&heartTexture);

        Fight fight(player1, player2);

        Indicator fightBanner(&fightBannerTexture, fightBannerSize, fightBannerPosition);

        Wind wind(&windTexture, windSize, WIND_SPEED, WIND_COOLDOWN);

        MoveableIndicator winnerBanner(&winnerBannerTexture, winnerBannerSize, defaultPosition);

        Platform ground(&transparentTexture,
                        sf::Vector2f(WINDOW_WIDTH, GROUND_HEIGHT),
                        sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - (GROUND_HEIGHT / 2.0f)));
        Platform leftWall(&transparentTexture,
                          sf::Vector2f(0.1f, WINDOW_HEIGHT),
                          sf::Vector2f(0.0f, WINDOW_HEIGHT / 2.0f));
        Platform rightWall(&transparentTexture,
                           sf::Vector2f(0.1f, WINDOW_HEIGHT),
                           sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f));

        float deltaTime = 0.0f;
        sf::Clock clock;

        // Game loop
        while (window.isOpen()) {
            deltaTime = clock.restart().asSeconds();
            if (deltaTime > MAX_SWITCH_TIME)
                deltaTime = MAX_SWITCH_TIME;

            sf::Event evnt{};
            while (window.pollEvent(evnt)) {
                switch (evnt.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::TextEntered:
                        if (evnt.text.unicode < 128) printf("%c", evnt.text.unicode);
                        break;
                    default:
                        break;
                }
            }

            checkAllCollisions(player1, player2, ground, leftWall, rightWall);
            update(deltaTime, player1, player2, fight, wind, winnerBanner);
            draw(window, background, checkEndOfGame(player1, player2),
                 player1, player2,
                 fightBanner, wind, winnerBanner);

            if (player1.GameFinished() || player2.GameFinished())
                window.close();

        }

        return 0;
    }

    catch (const GameException &e) {
        std::cerr << "Game Exception: " << e.what() << "\n";
        return -1;
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -1;
    }
}

