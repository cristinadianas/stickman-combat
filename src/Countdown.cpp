#include "Countdown.h"

Countdown::Countdown(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
        : Indicator(texture, size, position),
          animation(texture, sf::Vector2i(NR_FRAMES_COUNTDOWN, NR_ROWS_COUNTDOWN),
                    SWITCHTIME_COUNTDOWN, false),
          totalTime(0.0f),
          executing_countdown(true)
{
    // Vector care retine daca un sunet a fost redat
    // Normal Countdown: NR_FRAMES_COUNTDOWN-2 frames -> NR_FRAMES_COUNTDOWN-2 short beeps
    // Start Message: 2 frames -> 1 long beep
    beepsPlayed.resize(NR_FRAMES_COUNTDOWN - 1, false);
    body.setTextureRect(animation.GetUVRect());
}

void Countdown::Update(float deltaTime) {
    UpdateTotalTime(deltaTime);
    animation.Update(0, deltaTime,true);
    body.setTextureRect(animation.GetUVRect());
}

void Countdown::UpdateTotalTime(float deltaTime) {
    totalTime += deltaTime;
}

void Countdown::ExecuteCountdown(float deltaTime, sf::RenderWindow &window) {
    if (totalTime <= COUNTDOWN_DURATION) {
        Update(deltaTime);

        PlayCountdownSounds();

        window.clear();
        window.draw(graphicResources.GetScaledBackgroundSprite(window.getSize()));
        Draw(window);
        window.display();
    }
    else executing_countdown = false;
}

void Countdown::PlayCountdownSounds() {
    int i;
    for(i = 0; i < NR_FRAMES_COUNTDOWN - 2; i++)
        if(totalTime >= (float) i && !beepsPlayed[i]) {
            audioResources.GetShortBeep().play();
            beepsPlayed[i] = true;
        }
    if(totalTime >= i && !beepsPlayed[i]) {
        audioResources.GetLongBeep().play();
        beepsPlayed[i] = true;
    }
}

bool Countdown::InCountdownSequence() {
    return executing_countdown;
}
