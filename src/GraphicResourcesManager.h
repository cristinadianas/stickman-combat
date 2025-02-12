#ifndef GRAPHIC_RESOURCES_MANAGER_H
#define GRAPHIC_RESOURCES_MANAGER_H

#include <SFML/Graphics.hpp>
#include "GameExceptions.h"

class GraphicResourcesManager {
public:
    // Constructor and destructor
    GraphicResourcesManager();
    ~GraphicResourcesManager();

    // Get textures
    sf::Texture& GetPlayerTexture();
    sf::Texture& GetTransparentTexture();
    sf::Texture& GetHeartTexture();
    sf::Texture& GetFightBannerTexture();
    sf::Texture& GetWindTexture();
    sf::Texture& GetWinnerBannerTexture();
    sf::Texture& GetSnowballTexture();

    // Returns a sprite for the background scaled to the given window size
    sf::Sprite GetScaledBackgroundSprite(const sf::Vector2u& windowSize) const;

private:
    sf::Texture playerTexture;
    sf::Texture transparentTexture;
    sf::Texture heartTexture;
    sf::Texture fightBannerTexture;
    sf::Texture windTexture;
    sf::Texture winnerBannerTexture;
    sf::Texture snowballTexture;
    sf::Texture backgroundTexture;
};

#endif // GRAPHIC_RESOURCES_MANAGER_H
