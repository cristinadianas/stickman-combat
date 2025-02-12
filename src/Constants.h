#ifndef OOP_CONSTANTS_H
#define OOP_CONSTANTS_H

#include <SFML/Graphics.hpp>


// ANIMATION ROWS
constexpr int IDLE = 0;
constexpr int WALK = 1;
constexpr int JUMP = 2;
constexpr int DUCK = 3;
constexpr int EXECUTE_ATTACK = 4;
constexpr int INITIALIZE_ATTACK = 5;
constexpr int SNOWBALL_COOLDOWN = 6;
constexpr int LAST_HEART = 1;


// ATTACK PARAMETERS
constexpr float ATTACK_RANGE = 200.0f;
constexpr int ATTACK_STATE_IDLE = 0;
constexpr int ATTACK_PHASE_1 = 1;
constexpr int ATTACK_PHASE_2 = 2;
constexpr int ATTACK_COOLDOWN = 3;
constexpr float ATTACK_PHASE_1_DURATION = 0.25f;
constexpr float ATTACK_PHASE_2_DURATION = 0.25f;
constexpr float ATTACK_COOLDOWN_DURATION = 0.5f;


// AUDIO
constexpr float WIN_SOUND_VOLUME = 80.0f;
constexpr float DIE_SOUND_VOLUME = 50.0f;
constexpr float HIT_SOUND_VOLUME = 22.0f;
constexpr float JUMP_SOUND_VOLUME = 100.0f;
constexpr float BG_MUSIC_VOLUME = 100.0f;


// PLAYER PARAMETERS
constexpr float PLAYER_WIDTH = 170.0f;
constexpr float PLAYER_HEIGHT = 1.5f * PLAYER_WIDTH;
constexpr float DYING_SPEED = 2.0f;
constexpr int NR_FRAMES_PLAYER = 5;
constexpr int NR_ANIMATIONS_PLAYER = 7;
constexpr float SPEED = 250.0f;
constexpr float JUMP_HEIGHT = 400.0f;
constexpr float SWITCHTIME_PLAYER = 0.1f;
constexpr int NR_HEARTS = 5;
static const sf::Vector2i imageCountPlayer(NR_FRAMES_PLAYER, NR_ANIMATIONS_PLAYER);
static const sf:: Vector2f firstSpawnPosition(300.0f, 300.0f);
static const sf:: Vector2f secondSpawnPosition(1100.0f, 300.0f);
static const sf::Vector2f firstHealthBarPosition(60.0f, 60.0f);
static const sf::Vector2f secondHealthBarPosition(1380.0f, 60.0f);
static const sf::String player1Name("Venom");
static const sf::String player2Name("Shadow");


// HEART PARAMETERS
constexpr float HEART_SIZE = 80.0f;
constexpr int NR_FRAMES_HEART = 3;
constexpr int NR_ANIMATIONS_HEART = 2;
constexpr float SWITCHTIME_HEART = 0.3f;
static const sf::Vector2i imageCountHeart(NR_FRAMES_HEART, NR_ANIMATIONS_HEART);


// WIND PARAMETERS
constexpr int START_LEFT = 0;
constexpr int START_RIGHT = 1;
constexpr int RIGHT = 1;
constexpr int LEFT = -1;
constexpr float WIND_SPEED = 300.0f;
constexpr float WIND_COOLDOWN = 5.0f;


// SIZES
constexpr float GROUND_HEIGHT = 275.0f;
constexpr float WINDOW_WIDTH = 1450.0f;
constexpr float WINDOW_HEIGHT = 1024.0f;
constexpr float OFFSET_BANNER = 0.65f * PLAYER_HEIGHT;
constexpr float REPLAY_BUTTON_WIDTH = 400.0f;
constexpr float REPLAY_BUTTON_HEIGHT = REPLAY_BUTTON_WIDTH;
static const sf::Vector2f defaultPosition(-300.0f, -300.0f);
static const sf::Vector2f groundSize(WINDOW_WIDTH, GROUND_HEIGHT);
static const sf::Vector2f groundPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - (GROUND_HEIGHT / 2.0f));
static const sf::Vector2f wallSize(0.1f, WINDOW_HEIGHT);
static const sf::Vector2f leftWallPosition(0.0f, WINDOW_HEIGHT / 2.0f);
static const sf::Vector2f rightWallPosition(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f);
static const sf::Vector2f replayBannerSize(REPLAY_BUTTON_WIDTH, REPLAY_BUTTON_HEIGHT);
static const sf::Vector2f replayBannerPosition(WINDOW_WIDTH / 2.0f, 100.0f);


// SNOWBALL PARAMETERS
static const sf::Vector2i imageCountSnowball(6, 1);
constexpr float SWITCHTIME_SNOWBALL = 0.2f;
static const sf::Vector2f snowballSize(PLAYER_HEIGHT * 0.6f, PLAYER_HEIGHT * 0.4f);
constexpr float SNOWBALL_SPEED = 200.0f;
constexpr float SNOWBALL_RESPAWN_TIME = 3.0f;
constexpr float SNOWBALL_HIT_COOLDOWN = 2.0f;
constexpr float SNOWBALL_HEIGHT_OFF_GROUND = PLAYER_HEIGHT * 0.25;


// INDICATORS
static const sf::Vector2f winnerBannerSize(225.0f, 225.0f);
static const sf::Vector2f windSize(200.0f, 100.0f);
static const sf::Vector2f fightBannerSize(200.0f, 200.0f);
static const sf::Vector2f fightBannerPosition(WINDOW_WIDTH / 2.0f, 50.0f);


// FRAME REFRESH
constexpr float MAX_SWITCH_TIME = 1.0f / 20.0f;

#endif //OOP_CONSTANTS_H
