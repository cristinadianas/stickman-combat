#ifndef OOP_HEALTHBAR_UTILS_H
#define OOP_HEALTHBAR_UTILS_H

#include "HealthBar.h"
#include <SFML/Graphics.hpp>

// Resets Health Bar
template<typename IndicatorType>
void ResetHealthBar(HealthBar<IndicatorType>& newHealthBar, sf::Texture* texture,
                    int nrHearts, sf::Vector2f startPosition, bool goRight) {
    newHealthBar = HealthBar<IndicatorType>(nrHearts, startPosition, goRight);
    newHealthBar.Initialize(texture);
}

#endif // OOP_HEALTHBAR_UTILS_H