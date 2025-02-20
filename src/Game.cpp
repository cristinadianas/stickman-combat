#include "Game.h"
#include <iostream>

Game::Game()
        : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stickman Combat", sf::Style::Default),
          player1(GameObjectFactory::CreatePlayer(player1Name, true)),
          player2(GameObjectFactory::CreatePlayer(player2Name, false)),
          winner(nullptr),
          loser(nullptr),
          countdown(GameObjectFactory::CreateCountdown()),
          snowballEnemy(GameObjectFactory::CreateSnowballEnemy()),
          wind(GameObjectFactory::CreateWind(windSize, WIND_SPEED, WIND_COOLDOWN)),
          ground(GameObjectFactory::CreatePlatform(groundSize, groundPosition)),
          leftWall(GameObjectFactory::CreatePlatform(wallSize, leftWallPosition)),
          rightWall(GameObjectFactory::CreatePlatform(wallSize, rightWallPosition))
{
    fight = &Fight::getInstance();
    fight->InitializeFight(*player1, *player2);

    // Fight Banner
    indicators.push_back(std::make_unique<Indicator>(&graphicResources.GetFightBannerTexture(),
                                                     fightBannerSize,fightBannerPosition));
    // Winner Banner
    indicators.push_back(std::make_unique<MoveableIndicator>(&graphicResources.GetWinnerBannerTexture(),
                                                             winnerBannerSize,defaultPosition));
    // Replay Banner
    indicators.push_back(std::make_unique<Indicator>(&graphicResources.GetReplayBannerTexture(),
                                                     replayBannerSize,replayBannerPosition));

    deltaTime = 0.0f;
}

Game::~Game() {
    Player::ClearPlayers();
}

void Game::Run() {
    PrintGameInfo();
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        CheckEvents();

        if(countdown->InCountdownSequence())
            countdown->ExecuteCountdown(deltaTime, window);
        else
        {
            audioResources.PlayBackgroundMusic();

            if (deltaTime > MAX_SWITCH_TIME)
                deltaTime = MAX_SWITCH_TIME;

            CheckWinner();
            SolveCollisions();
            Update();
            Draw();
        }
    }
}

void Game::PrintGameInfo() const {
    printSingletonInfo(*this);
    std::cout << "\n" << *fight;
    std::cout << "Fight!\n\n";
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

void Game::HandlePlatformCollisions(Player* player, const std::vector<Collider*>& platforms, float push) {
    sf::Vector2f direction;
    for (auto* collider : platforms) {
        if (collider->HandleCollision(player->GetCollider(), direction, true, push))
            player->OnCollision(direction);
    }
}

void Game::SolveCollisions() {
    // Reset the ground state for both players.
    player1->SetIsOnGround(false);
    player2->SetIsOnGround(false);

    sf::Vector2f direction;

    Collider groundCollider   = ground->GetCollider();
    Collider leftWallCollider = leftWall->GetCollider();
    Collider rightWallCollider = rightWall->GetCollider();

    std::vector<Collider*> platformColliders = {
            &groundCollider,
            &leftWallCollider,
            &rightWallCollider
    };

    HandlePlatformCollisions(player1.get(), platformColliders, 1.0f);
    HandlePlatformCollisions(player2.get(), platformColliders, 1.0f);

    if (player1->GetCollider().HandleCollision(player2->GetCollider(), direction, true, 0.5f)) {
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
    auto *winnerBanner = dynamic_cast<MoveableIndicator*>(indicators[WINNER_BANNER_IDX].get());
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
    indicators[FIGHT_BANNER_IDX]->Draw(window);
    if (GameFinished())
        indicators[REPLAY_BANNER_IDX]->Draw(window);

    // Draw enemy snowballs
    if(!GameWon())
        snowballEnemy->Draw(window);

    // Draw players
    player1->Draw(window);
    player2->Draw(window);
    if(GameFinished())
        indicators[WINNER_BANNER_IDX]->Draw(window);

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
                    if ((float) evnt.mouseButton.x <= replayBannerPosition.x + replayBannerSize.x / 2.0f &&
                        (float) evnt.mouseButton.x >= replayBannerPosition.x - replayBannerSize.x / 2.0f &&
                        (float) evnt.mouseButton.y <= replayBannerPosition.y + replayBannerSize.y / 2.0f &&
                        (float) evnt.mouseButton.y >= replayBannerPosition.y - replayBannerSize.y / 2.0f)
                        ResetGame();
                }
                break;
            default:
                break;
        }
    }
}
