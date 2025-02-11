#include "Player.h"
#include <cmath>


Player::Player(const sf::String& name_, sf::Texture* texture, sf::Vector2i imageCount, float switchTime,
               float speed_, float jumpHeight_, sf::Vector2f spawnPosition,
               int nrHearts, sf::Vector2f healthBarPosition, bool goRight, bool faceRight_,
               sf::Keyboard::Key up_, sf::Keyboard::Key down_, sf::Keyboard::Key left_,
               sf::Keyboard::Key right_, sf::Keyboard::Key attack_)
        : name(name_),
          animation(texture, imageCount, switchTime),
          healthBar(nrHearts, healthBarPosition, goRight),
          speed(speed_), jumpHeight(jumpHeight_), faceRight(faceRight_),
          up(up_), down(down_), left(left_), right(right_), attack(attack_)
{
    dyingSoundPlayed = false;
    winningSoundPlayed = false;

    if (!jumpSound.openFromFile("../sounds/jump.wav"))
        throw SoundException("../sounds/jump.wav");
    if (!dyingSound.openFromFile("../sounds/dying.wav"))
        throw SoundException("../sounds/dying.wav");
    if (!winningSound.openFromFile("../sounds/win.wav"))
        throw SoundException("../sounds/win.wav");

    dyingSound.setVolume(DIE_SOUND_VOLUME);
    winningSound.setVolume(WIN_SOUND_VOLUME);

    row = IDLE;
    winner = false;
    finished = false;

    body.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(spawnPosition.x, spawnPosition.y);
    body.setTexture(texture);

    jumping = false;
    ducking = false;
    isOnGround = false;

    attackState = 0;
    attackTimer = 0.0f;
    attackExecuted = false;
}

Player::~Player() = default;

void Player::Update(float deltaTime) {

    if(IsDead())
        Dying(deltaTime);
    else {
        // Handle attack & attack animation

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

        velocity.x = 0.0f;

        // Handle movement and animation

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
                jumpSound.stop();
                jumpSound.play();
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
        }

        healthBar.Update(deltaTime);
        animation.Update(row, deltaTime, faceRight);
        body.setTextureRect(animation.GetUVRect());
        body.move(velocity * deltaTime);
    }
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
    healthBar.DeleteHeart();
}

bool Player::IsDead() const {
    return healthBar.IsDead();
}

bool Player::IsWinner() const {
    return winner;
}

void Player::Wins() {
    winner = true;
}

void Player::Dying(float deltaTime) {
    if (!dyingSoundPlayed)
    {
        dyingSound.play();
        dyingSoundPlayed = true;
    }
    else if (dyingSound.getStatus() == sf::SoundSource::Stopped && !winningSoundPlayed)
    {
        winningSound.play();
        winningSoundPlayed = true;
    }
    else if (winningSoundPlayed && winningSound.getStatus() == sf::SoundSource::Stopped)
        finished = true;

    velocity.x = 0.0f;
    velocity.y -= DYING_SPEED;
    body.move(velocity * deltaTime);
}

int Player::RemainingHearts() const {
    return healthBar.RemainingHearts();
}

void Player::InitializeHealthBar(sf::Texture* texture) {
    healthBar.Initialize(texture);
}

void Player::DrawHealthBar(sf::RenderWindow& window) const {
    if (!IsDead())
        healthBar.Draw(window);
}

bool Player::GameFinished() const {
    return finished;
}

sf::Vector2f Player::GetPosition() const {
    return body.getPosition();
}

void Player::SetIsOnGround(bool value) {
    isOnGround = value;
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

void Player::Draw(sf::RenderWindow& window) const {
    window.draw(body);
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "Name: " << player.name.toAnsiString() << ", Status: "
       << (player.IsDead() ? ("Dead") : ("Alive"))
       << ", Position: " << player.GetPosition().x << ", "
       << player.GetPosition().y << ", Remaining Health: "
       << player.RemainingHearts() << "\n";
    return os;
}

