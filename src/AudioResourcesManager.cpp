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
    if (!shortBeep.openFromFile("../sounds/short_beep.wav"))
        throw ResourceLoadException("../sounds/short_beep.wav");
    if (!longBeep.openFromFile("../sounds/long_beep.wav"))
        throw ResourceLoadException("../sounds/long_beep.wav");

    dyingSound.setVolume(DIE_SOUND_VOLUME);
    winningSound.setVolume(WIN_SOUND_VOLUME);
    hitSound.setVolume(HIT_SOUND_VOLUME);
    jumpSound.setVolume(JUMP_SOUND_VOLUME);
    backgroundMusic.setVolume(BG_MUSIC_VOLUME);
}

AudioResourcesManager::~AudioResourcesManager() = default;

void AudioResourcesManager::PlayBackgroundMusic() {
    if(backgroundMusic.getStatus() == sf::SoundSource::Stopped)
        backgroundMusic.play();
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

sf::Music &AudioResourcesManager::GetShortBeep() {
    return shortBeep;
}

sf::Music &AudioResourcesManager::GetLongBeep() {
    return longBeep;
}