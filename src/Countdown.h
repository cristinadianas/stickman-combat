#ifndef OOP_COUNTDOWN_H
#define OOP_COUNTDOWN_H

#include "Indicator.h"
#include "Animation.h"
#include "GraphicResourcesManager.h"
#include "Constants.h"

class Countdown : public Indicator {
public:
    Countdown(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    void Update(float deltaTime);

    void ExecuteCountdown(float deltaTime, sf::RenderWindow &window);

    bool InCountdownSequence();

private:
    Animation animation;
    GraphicResourcesManager graphicResources;
    float totalTime;
    bool executing_countdown;
};

#endif // OOP_COUNTDOWN_H

