#ifndef OOP_SNOWBALLENEMY_H
#define OOP_SNOWBALLENEMY_H

#include "Indicator.h"
#include "Animation.h"
#include "Collider.h"
#include "Constants.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <random>

class SnowballEnemy : public Indicator {
public:
    // Constructor and destructor
    SnowballEnemy(sf::Texture* texture,
                  sf::Vector2i imageCount,
                  float animationSwitchTime,
                  sf::Vector2f size);
    ~SnowballEnemy() override = default;

    // Update the animation and move
    void Update(float deltaTime);

    // Moves the snowball
    void Move(float deltaTime);

    // Returns true if the snowball is off the screen
    bool OffScreen();

    // Increases the respawn timer
    void IncreaseTimer(float deltaTime);

    // Resets the respawn timer
    void ResetTimer();

    // Returns true if the respawn timer has passed
    bool TimerPassed();

    // Randomly sets the direction of the snowball
    void SetDirection();

    // Sets whether the snowballs respawn
    void setRespawn(bool value);

    // Get SnowballEnemy Collider
    Collider GetCollider();

    // Draw snowball
    void Draw(sf::RenderWindow &window) const override;

    void CheckPlayerHit(Player &player);

private:
    // Respawn at random side and at random intervals
    void Respawn();

private:
    Animation animation;

    bool respawn;
    float speed;
    int goRight;

    float respawnTimer;

    // For random numberS
    std::mt19937 rng;
    std::uniform_real_distribution<float> respawnDist;
};

#endif // OOP_SNOWBALLENEMY_H
