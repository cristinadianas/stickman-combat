#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <ctime>

using namespace std;

class Fighter {
    string name;
    int life;
    int attack_damage;
    int sp_attack_damage;
    int sp_attack_cooldown;
public:
    Fighter(string  name_ = "Fighter", int life_ = 100, int attack_damage_ = 15,
            int sp_attack_damage_ = 40, int sp_attack_cooldown_ = 20) :
            name{std::move(name_)}, life{life_}, attack_damage{attack_damage_},
            sp_attack_damage{sp_attack_damage_}, sp_attack_cooldown{sp_attack_cooldown_} {
        cout <<name<< " has joined the game!\n";
    }

    Fighter(const Fighter& other) : name{other.name}, life{other.life}, attack_damage{other.attack_damage},
                                    sp_attack_damage{other.sp_attack_damage},
                                    sp_attack_cooldown{other.sp_attack_cooldown}{}

    Fighter& operator=(const Fighter& other) {
        name = other.name;
        life = other.life;
        attack_damage = other.attack_damage;
        sp_attack_damage = other.sp_attack_damage;
        sp_attack_cooldown = other.sp_attack_cooldown;
        return *this;
    }

    ~Fighter() = default;

    friend std::ostream& operator<<(std::ostream& os, const Fighter& f) {
        os << "NAME: " << f.name << "\nLIFE: " << f.life << "\nDAMAGE DEALT BY SIMPLE ATTACK: "
        << f.attack_damage << "\nDAMAGE DEALT BY SPECIAL ATTACK: " << f.sp_attack_damage
        << "\nSPECIAL ATTACK COOLDOWN: " << f.sp_attack_cooldown << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fighter& f) {
        cout << "NAME: ";
        is >> f.name;
        cout << "\nLIFE: ";
        is >> f.life;
        cout << "\nDAMAGE DEALT BY SIMPLE ATTACK: ";
        is >> f.attack_damage;
        cout << "\nDAMAGE DEALT BY SPECIAL ATTACK: ";
        is >> f.sp_attack_damage;
        cout << "\nSPECIAL ATTACK COOLDOWN: ";
        cin >> f.sp_attack_cooldown;
        cout << "\n";
        return is;
    }
};

class Game {
    Fighter fighter1, fighter2;
public:
    explicit Game(const Fighter& fighter1_ = {"Fighter 1", 100, 15, 40, 20},
         const Fighter& fighter2_ = {"Fighter 2", 100, 15, 40, 20}) :
        fighter1{fighter1_}, fighter2{fighter2_} {
        cout << "The game has started!";
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& g) {
        os << "INFORMATION ABOUT THE GAME\n"
        << "FIGHTERS: " <<  g.fighter1 << g.fighter2 << "\n";
        return os;
    }

    static void start() {
        int action;
        cin >> action;
    }
};

class Settings {
    double game_duration;
    int block_time;
public:
    explicit Settings(double game_duration_ = 60.00, int block_time_ = 2) :
            game_duration{game_duration_}, block_time{block_time_} {}

    friend std::istream& operator>>(std::istream& is, Settings& s) {
        cout << "\nThe game duration is currently " << s.game_duration << " second.\n"
        << "Please enter the new game duration: ";
        is >> s.game_duration;
        cout << "\nThe maximum block time is currently " << s.block_time << " seconds.\n"
        << "Please enter the new maximum block time: ";
        is >> s.block_time;
        return is;
    }

    [[nodiscard]] double get_game_duration() const {
        return game_duration;
    }

};

class Menu {
    int state;
public:
    explicit Menu(int state_ = 0) : state{state_} {
        cout << "Welcome to Stickman Combat!\n\n";
    };

    friend std::ostream& operator<<(std::ostream& os, const Menu& m) {
        os <<m.state <<"What would you like to do?\n"
        << "1. Start game\n" << "2. Open settings\n" << "3. Exit\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Menu& m) {
        is >> m.state;
        while(m.state != 1 && m.state != 2 && m.state != 3) {
            cout << "Please introduce a valid option! (1 or 2)\n";
            cin >> m.state;
        }
        return is;
    }

    void run() const {
        Settings settings;
        while(state != 3) {
            if (state == 1) {
                Fighter f1, f2;
                Game game{f1, f2};
                time_t t1 = time(nullptr);
                time_t t2 = time(nullptr);
                while(difftime(t2, t1) <= settings.get_game_duration()) {
                    Game::start();
                    t2 = time(nullptr);
                }

            } else if (state == 2)
                cin >> settings;
        }
    }
};

int main() {
    Menu menu;
    cout << menu;
    cin >> menu;
    menu.run();
    return 0;
}