#include "AudioResourcesManager.h"

AudioResourcesManager::AudioResourcesManager() {
    if(!hitSound.openFromFile("../sounds/fist_hit.wav"))
        throw ResourceLoadException("../sounds/fist_hit.wav");
    if (!backgroundMusic.openFromFile("../sounds/bg_music.wav"))
        throw ResourceLoadException("../sounds/bg_music.wav");
    if (!jumpSound.openFromFile("../sounds/jump.wav"))
        throw ResourceLoadException("../sounds/jump.wav");
    if (!dyingSound.openFromFile("../sounds/dying.wav"))
        throw ResourceLoadException("../sounds/dying.wav");
    if (!winningSound.openFromFile("../sounds/win.wav"))
        throw ResourceLoadException("../sounds/win.wav");

    dyingSound.setVolume(DIE_SOUND_VOLUME);
    winningSound.setVolume(WIN_SOUND_VOLUME);
    hitSound.setVolume(HIT_SOUND_VOLUME);
    jumpSound.setVolume(JUMP_SOUND_VOLUME);
    backgroundMusic.setVolume(BG_MUSIC_VOLUME);
}

AudioResourcesManager::~AudioResourcesManager() = default;

void AudioResourcesManager::PlayBackgroundMusic() {
    backgroundMusic.play();
    backgroundMusic.setLoop(true);
}

sf::Music &AudioResourcesManager::GetHitSound() {
    return hitSound;
}

sf::Music &AudioResourcesManager::GetJumpSound() {
    return jumpSound;
}

sf::Music &AudioResourcesManager::GetWinningSound() {
    return winningSound;
}

sf::Music &AudioResourcesManager::GetDyingSound() {
    return dyingSound;
}
