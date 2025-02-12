#include "GraphicResourcesManager.h"

GraphicResourcesManager::GraphicResourcesManager() {
    if (!playerTexture.loadFromFile("../textures/player_texture.png"))
        throw TextureLoadException("../textures/player_texture.png");
    if (!transparentTexture.loadFromFile("../textures/transparent_texture.png"))
        throw TextureLoadException("../textures/transparent_texture.png");
    if (!heartTexture.loadFromFile("../textures/heart_texture.png"))
        throw TextureLoadException("../textures/heart_texture.png");
    if (!fightBannerTexture.loadFromFile("../textures/fight_banner_texture.png"))
        throw TextureLoadException("../textures/fight_banner_texture.png");
    if (!windTexture.loadFromFile("../textures/wind_texture.png"))
        throw TextureLoadException("../textures/wind_texture.png");
    if (!winnerBannerTexture.loadFromFile("../textures/winner_texture.png"))
        throw TextureLoadException("../textures/winner_texture.png");
    if(!snowballTexture.loadFromFile("../textures/snowball_texture.png"))
        throw TextureLoadException("..textures/snowball_texture.png");
    if (!backgroundTexture.loadFromFile("../textures/background.png"))
        throw TextureLoadException("../textures/background.png");
}

GraphicResourcesManager::~GraphicResourcesManager() = default;

sf::Texture& GraphicResourcesManager::GetPlayerTexture() {
    return playerTexture;
}

sf::Texture& GraphicResourcesManager::GetTransparentTexture() {
    return transparentTexture;
}

sf::Texture& GraphicResourcesManager::GetHeartTexture() {
    return heartTexture;
}

sf::Texture& GraphicResourcesManager::GetFightBannerTexture() {
    return fightBannerTexture;
}

sf::Texture& GraphicResourcesManager::GetWindTexture() {
    return windTexture;
}

sf::Texture& GraphicResourcesManager::GetWinnerBannerTexture() {
    return winnerBannerTexture;
}

sf::Texture& GraphicResourcesManager::GetSnowballTexture() {
    return snowballTexture;
}

sf::Sprite GraphicResourcesManager::GetScaledBackgroundSprite(const sf::Vector2u& windowSize) const {
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);

    background.setScale(scaleX, scaleY);
    return background;
}