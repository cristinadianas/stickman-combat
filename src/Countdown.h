#ifndef OOP_COUNTDOWN_H
#define OOP_COUNTDOWN_H

#include "Indicator.h"
#include "Animation.h"
#include "GraphicResourcesManager.h"
#include "AudioResourcesManager.h"
#include "Constants.h"
#include <vector>

class Countdown : public Indicator {
public:
    // Constructor and destructor
    Countdown(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Countdown() override;

    // Update animation
    void Update(float deltaTime);

    // Update total time (executes until countdown is finished)
    void UpdateTotalTime(float deltaTime);

    // Update and draw countdown
    void ExecuteCountdown(float deltaTime, sf::RenderWindow &window);

    // Play countdown sounds at appropriate times
    void PlayCountdownSounds();

    // Returns true if the countdown is not finished
    bool InCountdownSequence();

private:
    Animation animation;
    GraphicResourcesManager graphicResources;
    AudioResourcesManager audioResources;
    float totalTime;
    std::vector<bool> beepsPlayed;
    bool executing_countdown;
};

#endif // OOP_COUNTDOWN_H

