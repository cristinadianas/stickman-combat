#include "MoveableIndicator.h"

MoveableIndicator::MoveableIndicator(sf::Texture* texture, sf::Vector2f size,
                                     sf::Vector2f position)
        : Indicator(texture, size, position) {}
MoveableIndicator::~MoveableIndicator() = default;

void MoveableIndicator::Move(float dx, float dy) {
    body.move(dx, dy);
}

void MoveableIndicator::SetScale(const sf::Vector2f& scale) {
    body.setScale(scale);
}

void MoveableIndicator::SetPosition(const sf::Vector2f& position) {
    body.setPosition(position);
}

sf::Vector2f MoveableIndicator::GetPosition() const {
    return body.getPosition();
}
