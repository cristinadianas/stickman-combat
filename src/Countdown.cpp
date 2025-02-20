#include "Countdown.h"

Countdown::Countdown(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
        : Indicator(texture, size, position),
          animation(texture, sf::Vector2i(NR_FRAMES_COUNTDOWN, NR_ROWS_COUNTDOWN), SWITCHTIME_COUNTDOWN),
          totalTime(0.0f),
          executing_countdown(true)
{
    body.setTextureRect(animation.GetUVRect());
}

void Countdown::Update(float deltaTime) {
    animation.Update(0, deltaTime,true);
    body.setTextureRect(animation.GetUVRect());
}

void Countdown::ExecuteCountdown(float deltaTime, sf::RenderWindow &window) {
    if (totalTime <= COUNTDOWN_DURATION) {
        Update(deltaTime);

        window.clear();
        window.draw(graphicResources.GetScaledBackgroundSprite(window.getSize()));
        Draw(window);
        window.display();

        totalTime += deltaTime;
    }
    else executing_countdown = false;
}

bool Countdown::InCountdownSequence() {
    return executing_countdown;
}
