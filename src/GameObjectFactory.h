#ifndef OOP_GAME_OBJECT_FACTORY_H
#define OOP_GAME_OBJECT_FACTORY_H

#include <memory>
#include "DrawableObject.h"
#include "Player.h"
#include "Platform.h"
#include "Wind.h"
#include "SnowballEnemy.h"
#include "GraphicResourcesManager.h"
#include "Constants.h"

class GameObjectFactory {
public:
    // Creates a Player
    static std::shared_ptr<Player> CreatePlayer(const std::string& name, bool firstPlayer);

    // Creates a Platform
    static std::unique_ptr<Platform> CreatePlatform(const sf::Vector2f& size, const sf::Vector2f& position);

    // Creates a Wind indicator
    static std::unique_ptr<Wind> CreateWind(const sf::Vector2f& size, float speed, float cooldown);

    // Creates a Snowball Enemy
    static std::unique_ptr<SnowballEnemy> CreateSnowballEnemy();

    // Returns graphic manager
    static GraphicResourcesManager& GetGraphicResources();
};

#endif // OOP_GAME_OBJECT_FACTORY_H
