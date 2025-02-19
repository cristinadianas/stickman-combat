#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "DrawableObject.h"
#include "Animation.h"
#include "HealthBar.h"
#include "Collider.h"
#include "HealthBarUtils.h"
#include "GameExceptions.h"
#include "Constants.h"
#include "AudioResourcesManager.h"
#include "GraphicResourcesManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <string>

class Player : public DrawableObject {
public:
    // Factory method to get a Player instance
    // Throws an exception if more than 2 players are requested
    static std::shared_ptr<Player> CreatePlayer(const std::string& name, bool firstPlayer);

    // Destructor
    ~Player() override;

    // Updates the player's state and animations
    void Update(float deltaTime);

    // Resets the health of the player to the original parameter
    void ResetHealth();

    // Resets the player to the default parameters
    void ResetPlayer();

    // Returns true if the player can start an attack
    bool CanAttack() const;

    // Returns true if the player is attackable (not ducking)
    bool IsAttackable() const;

    // Determines if this player is within attack range of an attacking player
    bool IsInAttackRange(const Player& attackingPlayer) const;

    // Returns true if the player is in the attacking phase 2 and hasn't executed the attack yet
    bool IsInAttackingPhase2() const;

    // Marks the attack as executed
    void ExecuteAttack();

    // Processes the player taking a hit
    void TakeHit();

    // Returns true if the player is dead (health bar is empty)
    bool IsDead() const;

    // Returns true if the player is the winner
    bool IsWinner() const;

    // Returns true if the winning player sounds finished playing
    bool Isfinished() const;

    // Makes the player the winner
    void Wins();

    // Makes the player die
    void Dying(float deltaTime);

    // Returns the number of remaining hearts
    int RemainingHearts() const;

    // Returns the player's current position
    sf::Vector2f GetPosition() const;

    // Sets whether the player is on the ground
    void SetIsOnGround(bool value);

    // Update snowball counter
    void UpdateSnowballCounter(float deltaTime);

    // Returns true if the player can be hit by snowball
    bool SnowballHitCooldownPassed() const;

    // Resets the timer for snowball hits
    void SnowballHitCooldownReset();

    // Returns the player's collider
    Collider GetCollider();

    // Handles collision response
    void OnCollision(sf::Vector2f direction);

    // Deletes the players
    static void ClearPlayers();

    // Draws the player on the screen
    void Draw(sf::RenderWindow& window) const override;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    // Constructor
    Player(const sf::String& name, bool firstPlayer);

private:

    GraphicResourcesManager graphicResources;
    AudioResourcesManager audioResources;

    bool firstPlayer;
    sf::String name;
    bool winner;
    bool dyingSoundFinished;
    sf::RectangleShape body;
    Animation animation;
    HealthBar<AnimatedIndicator> healthBar;
    sf::Vector2f velocity;
    int row;
    static float speed;
    static float jumpHeight;
    float snowballHitCooldownRemaining;
    bool faceRight;

    bool jumping;
    bool ducking;
    bool isOnGround;

    // 0: idle, 1: first phase (initializing attack),
    // 2: second phase (attacking), 3: cooldown
    int attackState;
    float attackTimer;
    bool attackExecuted;

    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key attack;

    bool dyingSoundPlayed;
    bool winningSoundPlayed;

    static constexpr int MAX_PLAYERS = 2;
    static std::vector<std::shared_ptr<Player>> players;
};

#endif // OOP_PLAYER_H

