#include "Game.h"
#include <iostream>

Game& Game::getInstance(const sf::String& player1name, const sf::String& player2name) {
    static Game instance(player1name, player2name);
    return instance;
}

Game::Game(const sf::String& player1name_, const sf::String& player2name_)
        : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stickman Combat", sf::Style::Default),
          winner(nullptr),
          loser(nullptr),
          snowballEnemy(GameObjectFactory::CreateSnowballEnemy(&graphicResources.GetSnowballTexture())),
          fightBanner(GameObjectFactory::CreateIndicator(&graphicResources.GetFightBannerTexture(),
                                                         fightBannerSize, fightBannerPosition)),
          winnerBanner(GameObjectFactory::CreateMoveableIndicator(&graphicResources.GetWinnerBannerTexture(),
                                                                  winnerBannerSize, defaultPosition)),
          wind(GameObjectFactory::CreateWind(&graphicResources.GetWindTexture(),
                                             windSize, WIND_SPEED, WIND_COOLDOWN)),
          ground(GameObjectFactory::CreatePlatform(&graphicResources.GetTransparentTexture(),
                                                   groundSize, groundPosition)),
          leftWall(GameObjectFactory::CreatePlatform(&graphicResources.GetTransparentTexture(),
                                                     wallSize, leftWallPosition)),
          rightWall(GameObjectFactory::CreatePlatform(&graphicResources.GetTransparentTexture(),
                                                      wallSize, rightWallPosition)),
          replayBanner(GameObjectFactory::CreateIndicator(&graphicResources.GetReplayBannerTexture(),
                                                          replayBannerSize, replayBannerPosition))
{
    try {
        player1 = GameObjectFactory::CreatePlayer(player1name_, true);
        player2 = GameObjectFactory::CreatePlayer(player2name_, false);
    }
    catch (const std::runtime_error &e) {
        std::cerr << "Error creating players" << e.what() << "\n";
        window.close();
    }

    fight = std::make_unique<Fight>(*player1, *player2);

    audioResources.PlayBackgroundMusic();
    deltaTime = 0.0f;
}

Game::~Game() {
    Player::ClearPlayers();
}

void Game::Run() {
    std::cout << *fight;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > MAX_SWITCH_TIME)
            deltaTime = MAX_SWITCH_TIME;

        CheckWinner();
        CheckEvents();
        SolveCollisions();
        Update();
        Draw();
    }
}

void Game::Update() {
    wind->Update(deltaTime);
    player1->Update(deltaTime);
    player2->Update(deltaTime);
    fight->Update();
    snowballEnemy->Update(deltaTime);
    snowballEnemy->CheckPlayerHit(*player1);
    snowballEnemy->CheckPlayerHit(*player2);

    if(winner) {
        ShowWinner();
        snowballEnemy->setRespawn(false);
    }
}

void Game::SolveCollisions() {
    // Reset the ground state for both players.
    player1->SetIsOnGround(false);
    player2->SetIsOnGround(false);

    sf::Vector2f direction;

    if (ground->GetCollider().CheckCollision(player1->GetCollider(),direction, true, 1.0f))
        player1->OnCollision(direction);

    if (ground->GetCollider().CheckCollision(player2->GetCollider(), direction, true,  1.0f))
        player2->OnCollision(direction);

    if (leftWall->GetCollider().CheckCollision(player1->GetCollider(), direction, true, 1.0f))
        player1->OnCollision(direction);

    if (leftWall->GetCollider().CheckCollision(player2->GetCollider(), direction, true, 1.0f))
        player2->OnCollision(direction);

    if (rightWall->GetCollider().CheckCollision(player1->GetCollider(), direction, true, 1.0f))
        player1->OnCollision(direction);

    if (rightWall->GetCollider().CheckCollision(player2->GetCollider(), direction, true, 1.0f))
        player2->OnCollision(direction);

    if (player1->GetCollider().CheckCollision(player2->GetCollider(), direction, true, 0.5f)) {
        player1->OnCollision(-direction);
        player2->OnCollision(direction);
    }
}

void Game::CheckWinner() {
    if (player1->IsWinner()) {
        winner = player1.get();
        loser = player2.get();
    }
    else if (player2->IsWinner()) {
        winner = player2.get();
        loser = player1.get();
    }
    else {
        winner = nullptr;
        loser = nullptr;
    }
}

void Game::ResetGame() {
    winner = nullptr;
    loser = nullptr;
    player1->ResetPlayer();
    player2->ResetPlayer();
    snowballEnemy->setRespawn(true);
}

void Game::ShowWinner() {
    sf::Vector2f winnerPosition = winner->GetPosition();
    winnerBanner->SetPosition(sf::Vector2f(winnerPosition.x, winnerPosition.y - OFFSET_BANNER));
}

bool Game::GameWon() const {
    if(winner)
        return true;
    return false;
}

bool Game::GameFinished() const {
    if(loser && loser->Isfinished())
        return true;
    return false;
}

void Game::Draw() {
    window.clear();

    // Draw background
    window.draw(graphicResources.GetScaledBackgroundSprite(window.getSize()));

    // Draw wind and banners
    wind->Draw(window);
    fightBanner->Draw(window);
    if (GameFinished())
        replayBanner->Draw(window);

    // Draw enemy snowballs
    if(!GameWon())
        snowballEnemy->Draw(window);

    // Draw players
    player1->Draw(window);
    player2->Draw(window);
    if(GameFinished())
        winnerBanner->Draw(window);

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
            case sf::Event::KeyPressed:
                if(evnt.key.code == sf::Keyboard::Escape)
                    window.close();
                if(evnt.key.code == sf::Keyboard::Space && GameFinished())
                    ResetGame();
                break;
            case sf::Event::MouseButtonPressed:
                if(GameFinished()) {
                    if (evnt.mouseButton.x <= replayBannerPosition.x + replayBannerSize.x / 2.0f &&
                        evnt.mouseButton.x >= replayBannerPosition.x - replayBannerSize.x / 2.0f &&
                        evnt.mouseButton.y <= replayBannerPosition.y + replayBannerSize.y / 2.0f &&
                        evnt.mouseButton.y >= replayBannerPosition.y - replayBannerSize.y / 2.0f)
                        ResetGame();
                }
                break;
            default:
                break;
        }
    }
}
