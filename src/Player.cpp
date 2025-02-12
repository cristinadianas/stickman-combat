#include "Player.h"
#include <memory>
#include <vector>
#include <iostream>

float Player::speed = SPEED;
float Player::jumpHeight = JUMP_HEIGHT;

std::vector<std::shared_ptr<Player>> Player::players;

std::shared_ptr<Player> Player::CreatePlayer(const std::string& name, bool firstPlayer) {
    if (players.size() >= MAX_PLAYERS)
        throw std::runtime_error("Maximum number of players reached\n");

    auto newPlayer = std::shared_ptr<Player>(new Player(name, firstPlayer));
    players.push_back(newPlayer);
    return newPlayer;
}

Player::Player(const sf::String& name_, bool firstPlayer_)
        : firstPlayer(firstPlayer_),
          name(name_),
          animation(&graphicResources.GetPlayerTexture(), imageCountPlayer, SWITCHTIME_PLAYER),
          healthBar(NR_HEARTS,
                    ((firstPlayer_)? firstHealthBarPosition : secondHealthBarPosition),
                    firstPlayer_)

{
    sf::Vector2f spawnPosition;
    firstPlayer = firstPlayer_;

    if (firstPlayer)
    {
        spawnPosition = firstSpawnPosition;
        faceRight = true;
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;
        left = sf::Keyboard::A;
        right = sf::Keyboard::D;
        attack = sf::Keyboard::LShift;
    }
    else
    {
        spawnPosition = secondSpawnPosition;
        faceRight = false;
        up = sf::Keyboard::O;
        down = sf::Keyboard::L;
        left = sf::Keyboard::K;
        right = sf::Keyboard::Semicolon;
        attack = sf::Keyboard::RShift;
    }

    healthBar.Initialize(&graphicResources.GetHeartTexture());

    dyingSoundPlayed = false;
    winningSoundPlayed = false;

    row = IDLE;
    winner = false;
    dyingSoundFinished = false;
    snowballHitCooldownRemaining = 0.0f;

    body.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(spawnPosition.x, spawnPosition.y);
    body.setTexture(&graphicResources.GetPlayerTexture());

    jumping = false;
    ducking = false;
    isOnGround = false;

    attackState = 0;
    attackTimer = 0.0f;
    attackExecuted = false;
}

Player::~Player() = default;

void Player::Update(float deltaTime) {
    healthBar.Update(deltaTime);
    UpdateSnowballCounter(deltaTime);

    if (healthBar.RemainingHearts() == 1) {
        auto& indicator = healthBar.GetIndicator(0);
        indicator.SetRow(LAST_HEART);
    }

    if (IsDead()) {
        Dying(deltaTime);
        return;
    }

    if (!SnowballHitCooldownPassed()) {
        row = SNOWBALL_COOLDOWN;
        animation.Update(row, deltaTime, faceRight);
        body.setTextureRect(animation.GetUVRect());
        return;
    }

    if (attackState == ATTACK_STATE_IDLE) {
        // If the attack key is pressed while in the idle state, start the attack sequence
        if (sf::Keyboard::isKeyPressed(attack) && CanAttack()) {
            attackState = ATTACK_PHASE_1;
            attackTimer = 0.0f;
            attackExecuted = false;
            row = INITIALIZE_ATTACK;
        }
    } else if (attackState == ATTACK_PHASE_1) {
        attackTimer += deltaTime;
        // Disable movement while in attack phase 1 and attack phase 2
        velocity.x = 0;
        if (attackTimer >= ATTACK_PHASE_1_DURATION) {
            attackState = ATTACK_PHASE_2;
            attackTimer = 0.0f;
            row = EXECUTE_ATTACK;
        }
    } else if (attackState == ATTACK_PHASE_2) {
        attackTimer += deltaTime;
        // Attack logic handled in Fight::Update
        if (attackTimer >= ATTACK_PHASE_2_DURATION) {
            attackState = ATTACK_COOLDOWN;
            attackTimer = 0.0f;
        }
    } else if (attackState == ATTACK_COOLDOWN) {
        attackTimer += deltaTime;
        if (attackTimer >= ATTACK_COOLDOWN_DURATION) {
            attackState = ATTACK_STATE_IDLE;
            attackTimer = 0.0f;
        }
    }

    // Handle movement and animation

    velocity.x = 0.0f;

    if (attackState == ATTACK_STATE_IDLE || attackState == ATTACK_COOLDOWN) {

        // Handle movement

        // Left
        if (sf::Keyboard::isKeyPressed(left))
            velocity.x -= speed;

        // Right
        if (sf::Keyboard::isKeyPressed(right))
            velocity.x += speed;

        // Jump
        if (sf::Keyboard::isKeyPressed(up) && !jumping && !ducking) {
            jumping = true;
            isOnGround = false;
            audioResources.GetJumpSound().stop();
            audioResources.GetJumpSound().play();
            velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
        }

        // Duck
        if (sf::Keyboard::isKeyPressed(down) && !jumping && !ducking)
            ducking = true;

        // Unduck
        if (!sf::Keyboard::isKeyPressed(down))
            ducking = false;

        // Fall
        if (!isOnGround) {
            velocity.y += 981.0f * deltaTime;
        }

        // Set movement animation
        if (ducking)
            row = DUCK;
        else if (velocity.x == 0.0f && velocity.y == 0.0f)
            row = IDLE;
        else if (velocity.x != 0.0f && velocity.y == 0.0f) {
            row = WALK;
            if (velocity.x > 0.0f) faceRight = true;
            else faceRight = false;
        } else if (velocity.y < 0.0f) {
            row = JUMP;
            if (velocity.x > 0.0f) faceRight = true;
            else faceRight = false;
        }

        body.move(velocity * deltaTime);
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.GetUVRect());
    return;
}

void Player::ResetHealth() {
    ResetHealthBar(
            healthBar,
            &graphicResources.GetHeartTexture(),
            NR_HEARTS,
            (firstPlayer ? firstHealthBarPosition : secondHealthBarPosition),
            firstPlayer
    );
}

void Player::ResetPlayer() {
    audioResources.GetWinningSound().stop();

    sf::Vector2f spawnPosition = firstPlayer ? firstSpawnPosition : secondSpawnPosition;
    body.setPosition(spawnPosition);

    velocity = sf::Vector2f(0.f, 0.f);

    winner = false;
    jumping = false;
    ducking = false;
    isOnGround = false;
    attackState = ATTACK_STATE_IDLE;
    attackTimer = 0.0f;
    attackExecuted = false;
    snowballHitCooldownRemaining = 0.0f;
    dyingSoundPlayed = false;
    winningSoundPlayed = false;
    dyingSoundFinished = false;
    row = IDLE;
    faceRight = firstPlayer;

    ResetHealth();
}

bool Player::CanAttack() const {
    return !jumping && !ducking && (attackState == 0);
}

bool Player::IsAttackable() const {
    return !ducking;  // isn't ducking
}

bool Player::IsInAttackRange(const Player& attackingPlayer) const {
    float distance = std::abs(attackingPlayer.GetPosition().x - this->GetPosition().x);

    if (distance < ATTACK_RANGE) {
        // Check if the attacker is facing this player
        if ((attackingPlayer.faceRight && attackingPlayer.GetPosition().x < this->GetPosition().x) ||
            (!attackingPlayer.faceRight && attackingPlayer.GetPosition().x > this->GetPosition().x)) {
            return true;
        }
    }

    return false;
}

bool Player::IsInAttackingPhase2() const {
    return (attackState == 2 && !attackExecuted);
}

void Player::ExecuteAttack() {
    attackExecuted = true;
}

void Player::TakeHit() {
    if (!IsWinner()) {
        audioResources.GetHitSound().play();
        healthBar.DeleteHeart();
    }
}

bool Player::IsDead() const {
    return healthBar.IsDead();
}

bool Player::IsWinner() const {
    return winner;
}

bool Player::Isfinished() const {
    return dyingSoundFinished;
}

void Player::Wins() {
    winner = true;
}

void Player::Dying(float deltaTime) {
    if (!dyingSoundPlayed)
    {
        // Dying sound for this player
        audioResources.GetDyingSound().play();
        dyingSoundPlayed = true;
    }
    else if (audioResources.GetDyingSound().getStatus() == sf::SoundSource::Stopped && !winningSoundPlayed)
    {
        // Winning sound for the other player
        winningSoundPlayed = true;
        dyingSoundFinished = true;
        audioResources.GetWinningSound().play();
        audioResources.GetWinningSound().setLoop(true);
    }

    velocity.x = 0.0f;
    velocity.y -= DYING_SPEED;
    body.move(velocity * deltaTime);
}

int Player::RemainingHearts() const {
    return healthBar.RemainingHearts();
}

sf::Vector2f Player::GetPosition() const {
    return body.getPosition();
}

void Player::SetIsOnGround(bool value) {
    isOnGround = value;
}

void Player::UpdateSnowballCounter(float deltaTime) {
    if (snowballHitCooldownRemaining > 0.0f)
        snowballHitCooldownRemaining -= deltaTime;
}

bool Player::SnowballHitCooldownPassed() const {
    return (snowballHitCooldownRemaining <= 0.0f);
}

void Player::SnowballHitCooldownReset() {
    snowballHitCooldownRemaining = SNOWBALL_HIT_COOLDOWN;
}

Collider Player::GetCollider() {
    return Collider{body};
}

void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x != 0.0f)
    {
        // Collision on the left or on the right
        velocity.x = 0.0f;
    }
    if (direction.y < 0.0f)
    {
        // Collision on the bottom =>
        // the player is not jumping and
        // the player is on top of an object
        velocity.y = 0.0f;
        jumping = false;
        isOnGround = true;
    }
    else if (direction.y > 0.0f)
    {
        // Collision on the top
        velocity.y = 0.0f;
    }
}

sf::String Player::GetName() const {
    return name;
}

void Player::ClearPlayers() {
    players.clear();
}

void Player::Draw(sf::RenderWindow& window) const {
    window.draw(body);
    healthBar.Draw(window);
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Name: " << player.name.toAnsiString() << ", Status: "
       << (player.IsDead() ? ("Dead") : ("Alive"))
       << ", Position: " << player.GetPosition().x << ", "
       << player.GetPosition().y << ", Remaining Health: "
       << player.RemainingHearts() << "\n";
    return os;
}

