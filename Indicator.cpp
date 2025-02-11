#include "Indicator.h"

Indicator::Indicator(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(position);
    body.setTexture(texture);
}

Indicator::~Indicator() = default;

void Indicator::Draw(sf::RenderWindow &window) const {
    window.draw(body);
}

std::ostream& operator<<(std::ostream& os, const Indicator& indicator) {
    os << "Indicator at position: "
       << indicator.body.getPosition().x << ", "
       << indicator.body.getPosition().y << "\n";
    return os;
}

