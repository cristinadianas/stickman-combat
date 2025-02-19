#include "SnowballEnemy.h"
#include <algorithm>

SnowballEnemy::SnowballEnemy(sf::Texture* texture,
                             sf::Vector2i imageCount,
                             float switchTime,
                             sf::Vector2f size)
        : Indicator(texture, size, defaultPosition),
          animation(texture, imageCount, switchTime),
          speed(SNOWBALL_SPEED),
          goRight(true),
          respawnTimer(0.0f),
          rng(std::random_device{}())
{
    respawn = true;
    Respawn();
}

void SnowballEnemy::Update(float deltaTime) {
    if (OffScreen()) {
        IncreaseTimer(deltaTime);
        if (TimerPassed()) {
            ResetTimer();
            Respawn();
        }
    } else
        Move(deltaTime);
}

void SnowballEnemy::Move(float deltaTime) {
    // Move horizontally
    float dx = speed * deltaTime * ((goRight == RIGHT) ? 1.0f : -1.0f);
    body.move(dx, 0.0f);
    animation.Update(0, deltaTime, true);
    body.setTextureRect(animation.GetUVRect());
}

void SnowballEnemy::IncreaseTimer(float deltaTime) {
    respawnTimer += deltaTime;
}

void SnowballEnemy::ResetTimer() {
    respawnTimer = 0.0f;
}

bool SnowballEnemy::TimerPassed() {
    return (respawnTimer >= SNOWBALL_RESPAWN_TIME);
}

bool SnowballEnemy::OffScreen() {
    sf::Vector2f position = body.getPosition();

    return ((goRight && position.x > WINDOW_WIDTH + body.getSize().x) ||
            (!goRight && position.x < 0 - body.getSize().x));

}

void SnowballEnemy::Respawn() {
    if (respawn) {
        SetDirection();

        sf::Vector2f position;
        if (goRight) {
            position.x = -body.getSize().x;
            body.setScale(1.0f, 1.0f);
        } else {
            position.x = WINDOW_WIDTH + body.getSize().x;  // Spawn just off the right side.
            // Flip image horizontally.
            body.setScale(-1.0f, 1.0f);
        }
        position.y = WINDOW_HEIGHT - GROUND_HEIGHT - SNOWBALL_HEIGHT_OFF_GROUND;
        body.setPosition(position);
    }
}

void SnowballEnemy::setRespawn(bool value) {
    respawn = value;
}

void SnowballEnemy::SetDirection() {
    std::uniform_int_distribution<int> sideDist(0, 1);
    int side = sideDist(rng);
    goRight = (side == 0);
}

void SnowballEnemy::CheckPlayerHit(Player &player) {
    if (!player.IsWinner()) {
        sf::Vector2f direction_;
        bool colliding = GetCollider().HandleCollision(player.GetCollider(), direction_, false);

        if (colliding && player.SnowballHitCooldownPassed()) {
            player.TakeHit();
            player.SnowballHitCooldownReset();
        }
    }
}

Collider SnowballEnemy::GetCollider() {
    return Collider{body};
}

void SnowballEnemy::Draw(sf::RenderWindow &window) const {
    window.draw(body);
}
