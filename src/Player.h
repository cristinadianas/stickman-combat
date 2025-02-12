#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include "Drawable.h"
#include "Animation.h"
#include "HealthBar.h"
#include "Collider.h"
#include "GameExceptions.h"
#include "Constants.h"
#include "AudioResourcesManager.h"
#include "GraphicResourcesManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

class Player : public Drawable {
public:
    // Constructor and destructor
    Player(const sf::String& name_, bool firstPlayer);

    ~Player();

    // Updates the player's state and animations
    void Update(float deltaTime);

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

    // Returns true if a player has won and all the sounds have finished playing
    bool GameFinished() const;

    // Returns the player's current position
    sf::Vector2f GetPosition() const;

    // Sets whether the player is on the ground
    void SetIsOnGround(bool value);

    // Returns the player's collider
    Collider GetCollider();

    // Handles collision response
    void OnCollision(sf::Vector2f direction);

    // Returns the player's name
    sf::String GetName() const;

    // Draws the player on the screen
    void Draw(sf::RenderWindow& window) const override;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    GraphicResourcesManager graphicResources;
    AudioResourcesManager audioResources;

    sf::String name;
    bool winner;
    bool finished;
    sf::RectangleShape body;
    Animation animation;
    HealthBar healthBar;
    sf::Vector2f velocity;
    int row;
    static float speed;
    static float jumpHeight;
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
};

#endif // OOP_PLAYER_H

