#include "Game.h"

Game::Game(const sf::String& player1name, const sf::String& player2name)
        : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stickman Combat", sf::Style::Default),
          player1(player1name, true),
          player2(player2name, false),
          winner(nullptr),
          fight(player1, player2),
          fightBanner(&graphicResources.GetFightBannerTexture(), fightBannerSize, fightBannerPosition),
          winnerBanner(&graphicResources.GetWinnerBannerTexture(), winnerBannerSize, defaultPosition),
          wind(&graphicResources.GetWindTexture(), windSize, WIND_SPEED, WIND_COOLDOWN),
          ground(&graphicResources.GetTransparentTexture(), groundSize, groundPosition),
          leftWall(&graphicResources.GetTransparentTexture(), wallSize, leftWallPosition),
          rightWall(&graphicResources.GetTransparentTexture(), wallSize, rightWallPosition)
{
    audioResources.PlayBackgroundMusic();
    deltaTime = 0.0f;
}

Game::~Game() = default;

void Game::Run() {
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > MAX_SWITCH_TIME)
            deltaTime = MAX_SWITCH_TIME;

        CheckEvents();
        CheckWinner();
        CheckCollisions();
        Update();
        Draw();
        ExitWhenGameFinished();
    }
}

void Game::Update() {
    wind.Update(deltaTime);
    player1.Update(deltaTime);
    player2.Update(deltaTime);
    fight.Update();

    // Show the winner banner only if the game has been won.
    ShowWinner();
}

void Game::CheckCollisions() {
    // Reset the ground state for both players.
    player1.SetIsOnGround(false);
    player2.SetIsOnGround(false);

    sf::Vector2f direction;

    if (ground.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if (ground.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if (leftWall.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if (leftWall.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if (rightWall.GetCollider().CheckCollision(player1.GetCollider(), direction, 1.0f))
        player1.OnCollision(direction);

    if (rightWall.GetCollider().CheckCollision(player2.GetCollider(), direction, 1.0f))
        player2.OnCollision(direction);

    if (player1.GetCollider().CheckCollision(player2.GetCollider(), direction, 0.5f)) {
        player1.OnCollision(-direction);
        player2.OnCollision(direction);
    }
}

void Game::CheckWinner() {
    if (player1.IsWinner())
        winner = &player1;
    else if (player2.IsWinner())
        winner = &player2;
    else
        winner = nullptr;
}

void Game::ExitWhenGameFinished() {
    if (winner && winner->Isfinished())
        window.close();
}

void Game::ShowWinner() {
    if (winner) {
        sf::Vector2f winnerPosition = winner->GetPosition();
        winnerBanner.SetPosition(sf::Vector2f(winnerPosition.x, winnerPosition.y - OFFSET_BANNER));
    }
}

void Game::Draw() {
    window.clear();

    // Draw background
    window.draw(graphicResources.GetScaledBackgroundSprite(window.getSize()));

    // Draw wind and banners
    wind.Draw(window);
    fightBanner.Draw(window);
    if (winner)
        winnerBanner.Draw(window);

    // Draw players
    player1.Draw(window);
    player2.Draw(window);

    window.display();
}

void Game::CheckEvents() {
    sf::Event evnt{};
    while (window.pollEvent(evnt)) {
        switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                    printf("%c", evnt.text.unicode);
                break;
            default:
                break;
        }
    }
}
