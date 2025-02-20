#include "GameObjectFactory.h"

GraphicResourcesManager& GameObjectFactory::GetGraphicResources() {
    static GraphicResourcesManager instance;
    return instance;
}

std::shared_ptr<Player> GameObjectFactory::CreatePlayer(const std::string& name, bool firstPlayer) {
    return Player::CreatePlayer(name, firstPlayer);
}

std::unique_ptr<Platform> GameObjectFactory::CreatePlatform(const sf::Vector2f& size, const sf::Vector2f& position) {
    auto& graphicResources = GetGraphicResources();
    return std::make_unique<Platform>(&graphicResources.GetTransparentTexture(), size, position);
}

std::unique_ptr<Wind> GameObjectFactory::CreateWind(const sf::Vector2f& size, float speed, float cooldown) {
    auto& graphicResources = GetGraphicResources();
    return std::make_unique<Wind>(&graphicResources.GetWindTexture(), size, speed, cooldown);
}

std::unique_ptr<SnowballEnemy> GameObjectFactory::CreateSnowballEnemy() {
    auto& graphicResources = GetGraphicResources();
    return std::make_unique<SnowballEnemy>(&graphicResources.GetSnowballTexture(),
                                           imageCountSnowball, SWITCHTIME_SNOWBALL, snowballSize);
}
