#ifndef OOP_AUDIO_RESOURCES_MANAGER_H
#define OOP_AUDIO_RESOURCES_MANAGER_H

#include <SFML/Audio.hpp>
#include "GameExceptions.h"
#include "Constants.h"

class AudioResourcesManager {
public:
    AudioResourcesManager();
    ~AudioResourcesManager();

    void PlayBackgroundMusic();

    sf::Music& GetHitSound();

    sf::Music& GetJumpSound();

    sf::Music& GetWinningSound();

    sf::Music& GetDyingSound();

private:
    sf::Music backgroundMusic;
    sf::Music jumpSound;
    sf::Music hitSound;
    sf::Music winningSound;
    sf::Music dyingSound;
};

#endif // OOP_AUDIO_RESOURCES_MANAGER_H
