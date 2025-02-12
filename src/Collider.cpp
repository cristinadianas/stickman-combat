#include "Collider.h"
#include <algorithm>
#include <cmath>

Collider::Collider(sf::RectangleShape& body_)
        : body(body_)
{
}

Collider::~Collider() = default;

void Collider::Move(float dx, float dy) {
    body.move(dx, dy);
}

sf::Vector2f Collider::GetPosition() const {
    return body.getPosition();
}

sf::Vector2f Collider::GetHalfSize() const {
    return body.getSize() / 2.0f;
}

bool Collider::CheckCollision(Collider other, sf::Vector2f &direction, bool solveCollision, float push) {
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = std::min(std::max(push, 0.0f), 1.0f);

        if (solveCollision) {
            if (intersectX > intersectY) {
                if (deltaX > 0.0f) {
                    Move(intersectX * (1.0f - push), 0.0f);
                    other.Move(-intersectX * push, 0.0f);
                    direction.x = 1.0f;
                    direction.y = 0.0f;
                } else {
                    Move(-intersectX * (1.0f - push), 0.0f);
                    other.Move(intersectX * push, 0.0f);
                    direction.x = -1.0f;
                    direction.y = 0.0f;
                }
            } else {
                if (deltaY > 0.0f) {
                    Move(0.0f, intersectY * (1.0f - push));
                    other.Move(0.0f, -intersectY * push);
                    direction.x = 0.0f;
                    direction.y = 1.0f;
                } else {
                    Move(0.0f, -intersectY * (1.0f - push));
                    other.Move(0.0f, intersectY * push);
                    direction.x = 0.0f;
                    direction.y = -1.0f;
                }
            }
        }
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Collider& collider) {
    os << "Pozitie collider: " << collider.GetPosition().x << ", " << collider.GetPosition().y
       << ", Half size collider: " << collider.GetHalfSize().x << ", " << collider.GetHalfSize().y << "\n";
    return os;
}
