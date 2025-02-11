#include <iostream>
#include <array>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
// #include <Helper.h>
// #include "env_fixes.h"

// ANIMATION ROWS
constexpr int IDLE = 0;
constexpr int WALK = 1;
constexpr int JUMP = 2;
constexpr int DUCK = 3;
constexpr int EXECUTE_ATTACK = 4;
constexpr int INITIALIZE_ATTACK = 5;
constexpr int FULL_HEART = 0;
constexpr int LAST_HEART = 1;

// ANIMATION PARAMETERS
constexpr int NR_FRAMES_PLAYER = 5;
constexpr int NR_ANIMATIONS_PLAYER = 6;
constexpr int NR_FRAMES_HEART = 3;
constexpr int NR_ANIMATIONS_HEART = 2;
static const sf::Vector2i singleImageCount(1, 1);

// PLAYER PARAMETERS
constexpr float SPEED = 250.0f;
constexpr float JUMP_HEIGHT = 400.0f;
constexpr float SWITCHTIME_PLAYER = 0.1f;
constexpr int NR_HEARTS = 5;
static const sf::Vector2i imageCountPlayer(NR_FRAMES_PLAYER, NR_ANIMATIONS_PLAYER);
static const sf:: Vector2f player1SpawnPosition(300.0f, 300.0f);
static const sf:: Vector2f player2SpawnPosition(1100.0f, 300.0f);
static const sf::Vector2f healthBar1Position(60.0f, 60.0f);
static const sf::Vector2f healthBar2Position(1380.0f, 60.0f);
static const sf::String player1Name("Venom");
static const sf::String player2Name("Shadow");

// ATTACK PARAMETRES
constexpr float ATTACK_RANGE = 200.0f;
constexpr int ATTACK_STATE_IDLE = 0;
constexpr int ATTACK_PHASE_1 = 1;
constexpr int ATTACK_PHASE_2 = 2;
constexpr int ATTACK_COOLDOWN = 3;
constexpr float ATTACK_PHASE_1_DURATION = 0.5f;
constexpr float ATTACK_PHASE_2_DURATION = 0.3f;
constexpr float ATTACK_COOLDOWN_DURATION = 1.2f;

// HEART PARAMETERS
constexpr float SWITCHTIME_HEART = 0.3f;
static const sf::Vector2i imageCountHeart(NR_FRAMES_HEART, NR_ANIMATIONS_HEART);

// SIZES
constexpr float HEART_SIZE = 80.0f;
constexpr float GROUND_HEIGHT = 275.0f;
constexpr float PLAYER_WIDTH = 170.0f;
constexpr float PLAYER_HEIGHT = 1.5f * PLAYER_WIDTH;
constexpr float WINDOW_WIDTH = 1450.0f;
constexpr float WINDOW_HEIGHT = 1024.0f;
static const sf::Vector2f fightBannerSize(200.0f, 200.0f);
static const sf::Vector2f fightBannerPosition(WINDOW_WIDTH / 2.0f, 50.0f);

// FRAME REFRESH
constexpr float MAX_SWITCH_TIME = 1.0f / 20.0f;


class Animation {
public:
    Animation(sf::Texture *texture, sf::Vector2i imageCount_, float switchTime_) :
            imageCount(imageCount_), switchTime(switchTime_)
    {
        totalTime = 0.0f;
        currentImage.x = 0;

        uvRect.width = (int) (texture->getSize().x / imageCount.x);
        uvRect.height = (int) (texture->getSize().y / imageCount.y);
    };

    ~Animation() {
        std::cout << "Destr Animation\n";
    };

    Animation(const Animation& other) : imageCount{other.imageCount}, currentImage{other.currentImage},
                                        uvRect{other.uvRect}, totalTime{other.totalTime}, switchTime{other.switchTime} {
        std::cout << "Constr de copiere Animation\n";
    }

    Animation& operator=(const Animation& other) {
        imageCount = other.imageCount;
        currentImage = other.currentImage;
        uvRect = other.uvRect;
        totalTime = other.totalTime;
        switchTime = other.switchTime;

        std::cout << "operator= copiere Animation\n";
        return *this;
    }

    sf::IntRect GetUVRect() const {
        return uvRect;
    }

    void Update(int row, float deltaTime, bool faceRight = true) {
        currentImage.y = row;
        totalTime += deltaTime;

        if (totalTime >= switchTime) {
            totalTime -= switchTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x)
                // Reset the animation
                currentImage.x = 0;
        }

        uvRect.top = currentImage.y * uvRect.height;

        if (faceRight) {
            uvRect.left = currentImage.x * uvRect.width;
            uvRect.width = abs(uvRect.width);
        } else {
            uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
            uvRect.width = -abs(uvRect.width);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Animation& animation) {
        os << "Number of rows: " << animation.imageCount.y << "\n";
        os << "Number of frames per row: " << animation.imageCount.x << "\n";
        os << "Time per frame: " << animation.switchTime << " seconds\n";
        return os;
    }

private:
    sf::Vector2i imageCount;
    sf::Vector2i currentImage;
    sf::IntRect uvRect;
    float totalTime;
    float switchTime;
};


class Collider
{
public:
    explicit Collider(sf::RectangleShape& body_) : body(body_) {};

    ~Collider()= default;

    void Move(float dx, float dy) {
        body.move(dx, dy);
    }

    sf::Vector2f GetPosition() const {
        return body.getPosition();
    }

    sf::Vector2f GetHalfSize() const {
        return body.getSize() / 2.0f;
    }

    bool CheckCollision(Collider other, sf::Vector2f & direction, float push) {
        sf::Vector2f otherPosition = other.GetPosition();
        sf::Vector2f otherHalfSize = other.GetHalfSize();
        sf::Vector2f thisPosition = GetPosition();
        sf::Vector2f thisHalfSize = GetHalfSize();

        float deltaX = otherPosition.x - thisPosition.x;
        float deltaY = otherPosition.y - thisPosition.y;

        float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
        float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

        if (intersectX < 0.0f && intersectY < 0.0f) {
            push = std::min(std::max(push, 0.0f), 1.0f);

            if(intersectX > intersectY)
            {
                if (deltaX > 0.0f)
                {
                    Move(intersectX * (1.0f - push), 0.0f);
                    other.Move(-intersectX * push, 0.0f);
                    direction.x = 1.0f;
                    direction.y = 0.0f;
                }
                else
                {
                    Move(-intersectX * (1.0f - push), 0.0f);
                    other.Move(intersectX * push, 0.0f);
                    direction.x = -1.0f;
                    direction.y = 0.0f;
                }
            }
            else
            {
                if (deltaY > 0.0f)
                {
                    Move(0.0f, intersectY * (1.0f - push));
                    other.Move(0.0f, -intersectY * push);
                    direction.x = 0.0f;
                    direction.y = 1.0f;
                }
                else
                {
                    Move(0.0f, -intersectY * (1.0f - push));
                    other.Move(0.0f, intersectY * push);
                    direction.x = 0.0f;
                    direction.y = -1.0f;
                }
            }
            return true;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Collider& collider) {
        os << "Pozitie collider: " << collider.GetPosition().x << ", " << collider.GetPosition().y
           << ", Half size collider: " << collider.GetHalfSize().x << ", " << collider.GetHalfSize().y << "\n";
        return os;
    }

private:
    sf::RectangleShape& body;
};


class Indicator {
public:
    Indicator(sf::Texture *texture, sf::Vector2i imageCount, float switchTime,
              sf::Vector2f size, sf::Vector2f position) :
            animation(texture, imageCount, switchTime) {
        row = 0;
        body.setSize(size);
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(position);
        body.setTexture(texture);
    };

    ~Indicator() = default;

    void Update(float deltaTime) {
        animation.Update(row, deltaTime);
        body.setTextureRect(animation.GetUVRect());
    }

    void SetRow(int value) {
        row = value;
    }

    void Draw(sf::RenderWindow &window) const {
        window.draw(body);
    }

    friend std::ostream& operator<<(std::ostream& os, const Indicator& indicator) {
        os << "Indicator at position " << indicator.body.getPosition().x << ", "
           << indicator.body.getPosition().y << " is in the animation from row "
           << indicator.row << ".\n";
        return os;
    }

private:
    int row;
    Animation animation;
    sf::RectangleShape body;
};


class Platform {
public:
    Platform(sf::Texture* texture, sf::Vector2i imageCount, float switchTime,
             sf::Vector2f size, sf::Vector2f position) :
            animation(texture, imageCount, switchTime)
    {
        row = 0;
        body.setSize(size);
        body.setOrigin(body.getSize() / 2.0f);
        body.setPosition(position);
        body.setTexture(texture);
    };

    ~Platform()= default;

    void Update(float deltaTime) {
        animation.Update(row, deltaTime);
        body.setTextureRect(animation.GetUVRect());
    }

    void Draw(sf::RenderWindow& window) const {
        window.draw(body);
    }

    Collider GetCollider() {
        return Collider{body};
    }

    friend std::ostream& operator<<(std::ostream& os, const Platform& platform) {
        os << "Platform at position " << platform.body.getPosition().x << ", "
           << platform.body.getPosition().y << " is in the animation from row "
           << platform.row << ".\n";
        return os;
    }

private:
    int row;
    sf::RectangleShape body;
    Animation animation;
};


class HealthBar {
public:
    HealthBar(int nrHearts_, sf::Vector2f startPosition_, bool goRight_) :
            nrHearts(nrHearts_), startPosition(startPosition_), goRight(goRight_) {};

    ~HealthBar()= default;

    void Initialize (sf::Texture * texture) {
        sf::Vector2f coordinates;
        coordinates.y = startPosition.y;

        for (int i = 0; i < nrHearts; i++)
        {
            if(goRight)
                coordinates.x = startPosition.x + (HEART_SIZE * i);
            else
                coordinates.x = startPosition.x - (HEART_SIZE * i);
            hearts.push_back(Indicator(texture, imageCountHeart, SWITCHTIME_HEART,
                                       sf::Vector2f (HEART_SIZE, HEART_SIZE), coordinates));
        }
    }

    void Update (float deltaTime) {
        if (nrHearts == 1)
            hearts[0].SetRow(LAST_HEART);

        for (int i = 0; i < nrHearts; i++)
            hearts[i].Update(deltaTime);
    }

    void DeleteHeart() {
        if(!IsDead()) {
            hearts.pop_back();
            nrHearts--;
        }
    }

    int RemainingHearts() const {
        return nrHearts;
    }

    bool IsDead() const {
        return nrHearts <= 0;
    }

    void Draw(sf::RenderWindow & window) const {
        for (int i = 0; i < nrHearts; i++)
            hearts[i].Draw(window);
    }

    friend std::ostream& operator<<(std::ostream& os, const HealthBar& healthBar) {
        os << "Remaining hearts: " << healthBar.nrHearts << "\n";
        return os;
    }

private:
    int nrHearts;
    sf::Vector2f startPosition;
    bool goRight;
    std::vector<Indicator> hearts;
};


class Player
{
public:
    Player(sf::String name_, sf::Texture* texture, sf::Vector2i imageCount, float switchTime,
           float speed_, float jumpHeight_, sf::Vector2f spawnPosition,
           int nrHearts, sf::Vector2f healthBarPosition, bool goRight=true, bool faceRight_=true,
           sf::Keyboard::Key up_=sf::Keyboard::W, sf::Keyboard::Key down_=sf::Keyboard::S, sf::Keyboard::Key left_=sf::Keyboard::A,
           sf::Keyboard::Key right_=sf::Keyboard::D, sf::Keyboard::Key attack_=sf::Keyboard::E) :

            name(name_),
            animation(texture, imageCount, switchTime),
            healthBar(nrHearts, healthBarPosition, goRight),
            speed(speed_), jumpHeight(jumpHeight_), faceRight(faceRight_),
            up(up_), down(down_), left(left_), right(right_), attack(attack_)
    {
        row = IDLE;

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
    };

    ~Player()= default;

    void Update(float deltaTime) {
        // Handle attack & attack animation
        if (attackState == ATTACK_STATE_IDLE) {
            // If the attack key is pressed while in the idle state, start the attack sequence
            if (sf::Keyboard::isKeyPressed(attack) && CanAttack()) {
                attackState = ATTACK_PHASE_1;
                attackTimer = 0.0f;
                attackExecuted = false;
                row = INITIALIZE_ATTACK;
            }
        }
        else if (attackState == ATTACK_PHASE_1) {
            attackTimer += deltaTime;
            // Disable movement while in attack phase 1 and attack phase 2
            velocity.x = 0;
            if (attackTimer >= ATTACK_PHASE_1_DURATION) {
                attackState = ATTACK_PHASE_2;
                attackTimer = 0.0f;
                row = EXECUTE_ATTACK;
            }
        }
        else if (attackState == ATTACK_PHASE_2) {
            attackTimer += deltaTime;
            // Attack logic handled in Fight::Update
            if (attackTimer >= ATTACK_PHASE_2_DURATION) {
                attackState = ATTACK_COOLDOWN;
                attackTimer = 0.0f;
            }
        }
        else if (attackState == ATTACK_COOLDOWN) {
            attackTimer += deltaTime;
            if (attackTimer >= ATTACK_COOLDOWN_DURATION) {
                attackState = ATTACK_STATE_IDLE;
                attackTimer = 0.0f;
            }
        }

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
                velocity.y += 981.0f * deltaTime;}

            // Set movement animation
            if (ducking)
                row = DUCK;
            else if (velocity.x == 0.0f && velocity.y == 0.0f)
                row = IDLE;
            else if (velocity.x != 0.0f && velocity.y == 0.0f)
            {
                row = WALK;
                if (velocity.x > 0.0f) faceRight = true;
                else faceRight = false;
            }
            else if (velocity.y < 0.0f)
            {
                row = JUMP;
                if (velocity.x > 0.0f) faceRight = true;
                else faceRight = false;
            }
        }

        healthBar.Update(deltaTime);
        animation.Update(row, deltaTime, faceRight);
        body.setTextureRect(animation.GetUVRect());
        body.move(velocity * deltaTime);
    };

    bool CanAttack() const {
        return !jumping && !ducking && (attackState == 0);
    }

    bool IsAttackable() const {
        return !ducking;  // isn't ducking
    }

    bool IsInAttackRange(const Player& attackingPlayer) const {
        float distance = abs(attackingPlayer.GetPosition().x - this->GetPosition().x);

        if (distance < ATTACK_RANGE) {
            // Check if the attacker is facing this player
            if ((attackingPlayer.faceRight && attackingPlayer.GetPosition().x < this->GetPosition().x) ||
                (!attackingPlayer.faceRight && attackingPlayer.GetPosition().x > this->GetPosition().x)) {
                return true;
            }
        }

        return false;
    }

    bool IsInAttackingPhase2() const {
        return (attackState == 2 && !attackExecuted);
    }

    void ExecuteAttack() {
        attackExecuted = true;
    }

    void TakeHit() {
        healthBar.DeleteHeart();
    }

    bool IsDead() const {
        return healthBar.IsDead();
    }

    int RemainingHearts() const {
        return healthBar.RemainingHearts();
    }

    void InitializeHealthBar(sf::Texture * texture) {
        healthBar.Initialize(texture);
    }

    void DrawHealthBar(sf::RenderWindow & window) const {
        healthBar.Draw(window);
    }

    sf::Vector2f GetPosition() const {
        return body.getPosition();
    }

    void SetIsOnGround(bool value) {
        isOnGround = value;
    }

    Collider GetCollider() {
        return Collider{body};
    }

    void OnCollision(sf::Vector2f direction) {
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

    void Draw(sf::RenderWindow& window) const {
        window.draw(body);
    }

    sf::String GetName() const {
        return name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << "Name: " << player.name.toAnsiString() << ", Status: " << (player.IsDead() ? ("Dead") : ("Alive"))
           << ", Position: " << player.GetPosition().x << ", " << player.GetPosition().y << ", Remaining Health: "
           << player.RemainingHearts() << "\n";
        return os;
    }

private:
    sf::String name;
    sf::RectangleShape body;
    Animation animation;
    HealthBar healthBar;
    sf::Vector2f velocity;
    int row;
    float speed;
    float jumpHeight;
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
};


class Fight {
public:
    Fight(Player& player1, Player& player2)
            : player1(player1), player2(player2) {
    }

    ~Fight()= default;

    void Update() {
        if (player1.IsInAttackingPhase2()) {
            if (player2.IsAttackable() && player2.IsInAttackRange(player1)) {
                player1.ExecuteAttack();
                player2.TakeHit();
            }
        }
        if (player2.IsInAttackingPhase2()) {
            if (player1.IsAttackable() && player1.IsInAttackRange(player2)) {
                player2.ExecuteAttack();
                player1.TakeHit();
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Fight& fight) {
        os << "Fight between " << fight.player1.GetName().toAnsiString() << " and "
           << fight.player2.GetName().toAnsiString() << "! ";

        if (fight.player1.RemainingHearts() > fight.player2.RemainingHearts())
            os << fight.player1.GetName().toAnsiString() << " is more likely to win!";
        else if (fight.player1.RemainingHearts() < fight.player2.RemainingHearts())
            os << fight.player2.GetName().toAnsiString() << " is more likely to win!";
        else os << "Equal chances to win!\n";

        return os;
    }

private:
    Player& player1;
    Player& player2;
};


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

void update(float deltaTime, Player &player1, Player &player2, Fight &fight) {
    player1.Update(deltaTime);
    player2.Update(deltaTime);
    fight.Update();
}

void draw(sf::RenderWindow &window, const sf::Sprite &background,
          const Player &player1, const Player &player2, const Indicator &fightBanner) {
    window.clear();

    window.draw(background);
    fightBanner.Draw(window);

    if(!player1.IsDead()) {
        player1.Draw(window);
        player1.DrawHealthBar(window);
    }
    if(!player2.IsDead()) {
        player2.Draw(window);
        player2.DrawHealthBar(window);
    }

    window.display();
}


int main() {
    // Render the window in which the game will take place
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stickman Combat", sf::Style::Default);

    // Get all the textures
    sf::Texture playerTexture;
    playerTexture.loadFromFile("../textures/player_texture.png");
    sf::Texture transparentTexture;
    transparentTexture.loadFromFile("../textures/transparent_texture.png");
    sf::Texture heartTexture;
    heartTexture.loadFromFile("../textures/heart_texture.png");
    sf::Texture fightBannerTexture;
    fightBannerTexture.loadFromFile("../textures/fight_banner_texture.png");
    sf::Texture winnerBannerTexture;
    winnerBannerTexture.loadFromFile("../textures/winner_texture.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../textures/background.png");
    sf::Sprite background(backgroundTexture);

    // Fit background correctly into window
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float ScaleX = (float) windowSize.x / (float) textureSize.x;
    float ScaleY = (float) windowSize.y / (float) textureSize.y;
    background.setTexture(backgroundTexture);
    background.setScale(ScaleX, ScaleY);

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

    Indicator fightBanner(&fightBannerTexture, singleImageCount, 0.0f,
                          fightBannerSize, fightBannerPosition);

    Platform ground(&transparentTexture, singleImageCount, 0.0f,
                    sf::Vector2f (WINDOW_WIDTH, GROUND_HEIGHT),
                    sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - (GROUND_HEIGHT / 2.0f)));
    Platform leftWall(&transparentTexture, singleImageCount, 0.0f,
                      sf::Vector2f (0.1f, WINDOW_HEIGHT),
                      sf::Vector2f(0.0f, WINDOW_HEIGHT / 2.0f));
    Platform rightWall(&transparentTexture, singleImageCount, 0.0f,
                       sf::Vector2f (0.1f, WINDOW_HEIGHT),
                       sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f));

    float deltaTime = 0.0f;
    sf::Clock clock;

    // operator=
    Animation a1(&transparentTexture, singleImageCount, 0.0f);
    Animation a2(&transparentTexture, singleImageCount, 0.1f);
    a2 = a1;

    // Afisari
    std::cout << player1;
    std::cout << player2;
    std::cout << fight;
    std::cout << fightBanner;
    std::cout << ground;
    std::cout << leftWall;
    std::cout << rightWall;

    // Game loop
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > MAX_SWITCH_TIME)
            deltaTime = MAX_SWITCH_TIME;

        sf::Event evnt{};
        while(window.pollEvent(evnt)) {
            switch (evnt.type)
            {
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
        update(deltaTime, player1, player2, fight);
        draw(window, background, player1, player2, fightBanner);
    }

    return 0;
}

