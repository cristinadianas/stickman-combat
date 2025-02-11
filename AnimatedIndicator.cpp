#include "AnimatedIndicator.h"

AnimatedIndicator::AnimatedIndicator(sf::Texture* texture, sf::Vector2i imageCount, float switchTime,
                                     sf::Vector2f size, sf::Vector2f position)
        : Indicator(texture, size, position),
          row(0),
          animation(texture, imageCount, switchTime)
{
}

AnimatedIndicator::~AnimatedIndicator() = default;

void AnimatedIndicator::Update(float deltaTime) {
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.GetUVRect());
}

void AnimatedIndicator::SetRow(int value) {
    row = value;
}

std::ostream& operator<<(std::ostream& os, const AnimatedIndicator& animatedIndicator) {
    os << "Indicator at position "
       << animatedIndicator.body.getPosition().x << ", "
       << animatedIndicator.body.getPosition().y
       << " is in the animation from row " << animatedIndicator.row << ".\n";
    return os;
}

