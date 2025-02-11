#ifndef OOP_WIND_H
#define OOP_WIND_H

#include "MoveableIndicator.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Wind : MoveableIndicator {
public:
    // Constructor and destructor
    Wind(sf::Texture* texture, sf::Vector2f size, float speed, float cooldown);
    virtual ~Wind();

    // Update the wind state (move if active, otherwise wait until cooldown has passed)
    void Update(float deltaTime);

    // Draw the wind if it is active
    void Draw(sf::RenderWindow &window) const override;

    // Resets the wind, randomly chooses a start position
    void Reset();

private:
    float windSpeed;
    float cooldownTime;
    float timer;
    bool isActive;
    int direction;
};

#endif // OOP_WIND_H
