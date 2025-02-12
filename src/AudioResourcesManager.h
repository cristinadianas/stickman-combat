#ifndef OOP_AUDIO_RESOURCES_MANAGER_H
#define OOP_AUDIO_RESOURCES_MANAGER_H

#include <SFML/Audio.hpp>
#include "GameExceptions.h"
#include "Constants.h"

class AudioResourcesManager {
public:
    // Constructor and destructor
    AudioResourcesManager();
    ~AudioResourcesManager();

    // Plays the background music on a loop
    void PlayBackgroundMusic();

    // Get sounds
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
