#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
        : Indicator(texture, size, position)
{
}

Platform::~Platform() = default;

Collider Platform::GetCollider() {
    return Collider(body);
}

std::ostream& operator<<(std::ostream& os, const Platform& platform) {
    os << "Platform at position ("
       << platform.body.getPosition().x << ", "
       << platform.body.getPosition().y << ").";
    return os;
}
