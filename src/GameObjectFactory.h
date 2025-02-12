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
    static std::shared_ptr<Player> CreatePlayer(const std::string& name, bool firstPlayer) {
        return Player::CreatePlayer(name, firstPlayer);
    }

    // Creates a Platform
    static std::unique_ptr<Platform> CreatePlatform(sf::Texture* texture,
                                                    const sf::Vector2f& size,
                                                    const sf::Vector2f& position) {
        return std::make_unique<Platform>(texture, size, position);
    }

    // Create an Indicator
    static std::unique_ptr<Indicator> CreateIndicator(sf::Texture* texture,
                                                      const sf::Vector2f& size,
                                                      const sf::Vector2f& position) {
        return std::make_unique<Indicator>(texture, size, position);
    }

    // Creates a Wind indicator
    static std::unique_ptr<Wind> CreateWind(sf::Texture* texture,
                                            const sf::Vector2f& size,
                                            float speed,
                                            float cooldown) {
        return std::make_unique<Wind>(texture, size, speed, cooldown);
    }

    // Create a Moveable Indicator
    static std::unique_ptr<MoveableIndicator> CreateMoveableIndicator(sf::Texture* texture,
                                                                      const sf::Vector2f& size,
                                                                      const sf::Vector2f& position) {
        return std::make_unique<MoveableIndicator>(texture, size, position);
    }

    // Creates a Snowball Enemy
    static std::unique_ptr<SnowballEnemy> CreateSnowballEnemy(sf::Texture* texture) {
        return std::make_unique<SnowballEnemy>(texture, imageCountSnowball, SWITCHTIME_SNOWBALL, snowballSize);
    }
};

#endif // OOP_GAME_OBJECT_FACTORY_H
