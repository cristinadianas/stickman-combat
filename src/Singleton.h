#ifndef OOP_SINGLETON_H
#define OOP_SINGLETON_H

#pragma once
#include <iostream>
#include <random>

template <typename Derived>
class Singleton {
protected:
    Singleton() : instanceID(generateInstanceID()) {};
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Derived& getInstance() {
        static DerivedInstance instance;
        return instance;
    }

    [[nodiscard]] int getInstanceID() const {
        return instanceID;
    }

private:
    int instanceID;

    class DerivedInstance : public Derived{};

    int generateInstanceID() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(1000, 9999);

        return distrib(gen);
    }
};

template <typename T>
void printSingletonInfo(T& instance) {
    std::cout << "Singleton instance of: " << typeid(T).name()
              << " with ID: " << instance.getInstanceID() << std::endl;
}

#endif //OOP_SINGLETON_H
