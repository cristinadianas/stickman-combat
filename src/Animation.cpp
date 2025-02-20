#include "Animation.h"
#include <cmath>

Animation::Animation(sf::Texture* texture, sf::Vector2i imageCount_, float switchTime_, bool repeat_)
        : imageCount(imageCount_),
          switchTime(switchTime_),
          repeat(repeat_),
          finished(false)
{
    if (texture->getSize().x == 0 || texture->getSize().y == 0)
        throw AnimationException("Texture size 0");

    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;

    uvRect.width = static_cast<int>(texture->getSize().x / imageCount.x);
    uvRect.height = static_cast<int>(texture->getSize().y / imageCount.y);
}

Animation::~Animation() = default;

sf::IntRect Animation::GetUVRect() const {
    return uvRect;
}

void Animation::Update(int row, float deltaTime, bool faceRight) {
    if(!repeat && finished)
        return;

    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
            finished = true;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight) {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = std::abs(uvRect.width);
    } else {
        uvRect.left = (currentImage.x + 1) * std::abs(uvRect.width);
        uvRect.width = -std::abs(uvRect.width);
    }
}

std::ostream& operator<<(std::ostream& os, const Animation& animation) {
    os << "Number of rows: " << animation.imageCount.y << "\n";
    os << "Number of frames per row: " << animation.imageCount.x << "\n";
    os << "Time per frame: " << animation.switchTime << " seconds\n";
    return os;
}
