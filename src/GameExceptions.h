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


class ResourceLoadException : public GameException {
public:
    explicit ResourceLoadException(const std::string& filename)
            : GameException("Resource Load Error: '" + filename + "\n") {}
};


class AnimationException : public GameException {
public:
    explicit AnimationException(const std::string& message)
            : GameException("Animation Error: " + message+ "\n") {}
};

class RulesException : public GameException {
public:
    explicit RulesException(const std::string& message)
            : GameException("Rules Error: " + message+ "\n") {}
};

#endif //OOP_GAMEEXCEPTIONS_H
