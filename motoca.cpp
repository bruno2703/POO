#include <iostream>
#include <sstream>
#include <memory>
#include <aux.hpp>

class Person {
    std::string name; //atributo
    int age;
public:
    Person(std::string name = "", int age = 0) {
        this->name = name;
        this->age = age;
    }

    Person(int age) { 
        this->age = age;
    }

    int getAge() {
        return age;
    }
    std::string getName() {
        return name;
    }
    std::string str() {
        std::stringstream ss;
        ss << name << " " << age;
        return ss.str();
    }
};
std::ostream& operator<<(std::ostream& os, Person& p) {
    return os << p.str();
}

class Motorcycle {
    std::shared_ptr<Person> person {nullptr}; //agregação
    int time {0};
    int power {1};

public:
    Motorcycle(int power = 1) { 
        this->power = power;
    }

    bool insertPerson(std::shared_ptr<Person> p) {
        if (person == nullptr) {
            person = p;
            return true;
        }
        return false;
    }

    std::string honk() {
        std::string s = "P";
        for (int i = 0; i < power; i++) {
            s += "e";
        }
        s += "m";
        return s;
    }

    std::shared_ptr<Person> remove() {
        std::shared_ptr<Person> p = person;
        person = nullptr;
        return p;
    }

    void buyTime(int time) {
        this->time += time;
    }

    void drive(int time) {
        if (person != nullptr) {
            if (person->getAge() <= 10) {
                if (this->time > 0) {
                    if (this->time >= time) {
                        this->time -= time;
                    } else {
                        std::cout << "time ran out in the middle of the tour, " << person->getName() << " walked " << this->time << " minutes" << std::endl;
                        this->time = 0;
                    }
                }
            }
        }

    }

    std::string str() {
        std::ostringstream os;
        os << "power:" << power << ", time:" << time;
        os << ", person:(" << (person == nullptr ? "empty" : person->str()) << ")";
        return os.str();
    }
};


std::ostream& operator<<(std::ostream& os, Motorcycle m) {
    return os << m.str();
}


int main() {
    aux::Chain chain;
    aux::Param param;

    Motorcycle m(1);

    auto INT = aux::to<int>;

    chain["show"]  = [&]() { m | aux::PRINT(); };
    chain["leave"] = [&]() { 
        auto person = m.remove(); 
        if (person != nullptr) {
            *person | aux::PRINT();
        }
    };
    chain["honk"]  = [&]() { m.honk()  | aux::PRINT(); };
    chain["init"]  = [&]() { m = Motorcycle(INT(param.at(1)));};
    chain["enter"] = [&]() { m.insertPerson(std::make_shared<Person>(param.at(1), INT(param.at(2)))); };
    chain["buy"]   = [&]() { m.buyTime(INT(param.at(1))); };
    chain["drive"] = [&]() { m.drive  (INT(param.at(1))); };

    aux::execute(chain, param);
}
