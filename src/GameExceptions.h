#ifndef OOP_GAMEEXCEPTIONS_H
#define OOP_GAMEEXCEPTIONS_H

#include <exception>
#include <utility>

class GameException : public std::exception {
public:
    explicit GameException(std::string  message_) : message(std::move(message_)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};


class TextureLoadException : public GameException {
public:
    explicit TextureLoadException(const std::string& filename)
            : GameException("Texture Load Error: '" + filename + "\n") {}
};


class AnimationException : public GameException {
public:
    explicit AnimationException(const std::string& message)
            : GameException("Animation Error: " + message+ "\n") {}
};


class SoundException : public GameException {
public:
    explicit SoundException(const std::string& message)
            : GameException("Sound Error: " + message) {}
};

#endif //OOP_GAMEEXCEPTIONS_H
