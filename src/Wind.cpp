#include "Wind.h"

Wind::Wind(sf::Texture* texture, sf::Vector2f size, float speed, float cooldown)
        : MoveableIndicator(texture, size, sf::Vector2f(0, 0)),
          windSpeed(speed),
          cooldownTime(cooldown),
          timer(0.f),
          isActive(false),
          direction(RIGHT)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Reset();
}

Wind::~Wind() = default;

void Wind::Reset() {
    int side = std::rand() % 2;

    float positionY = static_cast<float>(std::rand() % static_cast<int>(WINDOW_HEIGHT));

    if (side == START_LEFT) {
        // Start at the left side
        SetPosition(sf::Vector2f(0.f, positionY));
        SetScale(sf::Vector2f(1.f, 1.f));
        direction = RIGHT;
    } else if (side == START_RIGHT){
        // Start at the right side
        SetPosition(sf::Vector2f(WINDOW_WIDTH, positionY));
        // Flip the image so it faces left
        SetScale(sf::Vector2f(-1.f, 1.f));
        direction = LEFT;
    }

    isActive = true;
}

void Wind::Update(float deltaTime) {
    if (isActive) {
        // Move the wind horizontallY
        Move(windSpeed * deltaTime * (float) direction, 0.f);

        sf::Vector2f position = GetPosition();

        // If the wind has completely left the screen, disable it and reset the timer
        if ((direction == RIGHT && position.x > WINDOW_WIDTH) ||
            (direction == LEFT && position.x < 0)) {
            isActive = false;
            timer = 0.f;
        }
    }
    else {
        timer += deltaTime;
        if (timer >= cooldownTime) {
            Reset();
        }
    }
}


void Wind::Draw(sf::RenderWindow &window) const{
    if (isActive) {
        window.draw(body);
    }
}
