/*
1)
Fiz sozinho(com o que tava no moodle)
2)
sem duvidas
3)
5 horas
*/

#include <iostream>
#include <vector>
#include <utility>
#include "aux.hpp"

enum Cents {C10, C25, C50, C100};

class Coin {
    float value;
    int volume;
    std::string label;
public:
    Coin(Cents v) { 
        switch (v) {
            case C10: value = 0.10; volume = 1; label = "C10"; break;
            case C25: value = 0.25; volume = 2; label = "C25"; break;
            case C50: value = 0.50; volume = 3; label = "C50"; break;
            case C100: value = 1.0; volume = 4; label = "C100"; break;
        }
    }
    float getValue() const { 
        return value; 
    }
    int getVolume() const { 
        return volume; 
    }
    std::string getLabel() const { 
        return label; 
    }
};


class Item {
    std::string label;
    int volume;
public:
    Item(std::string label, int volume) {
        setVolume(volume);
        setLabel(label);
    }
    int getVolume() const {
        return volume; 
    }
    std::string getLabel() const {
        return label; 
    }
    void setVolume(int volume) {
        this-> volume = volume;
    }
    void setLabel(std::string label) {
        this->label = label;
    }
    std::string str() const {
        return {}; // todo
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return os << item.str();
}

class Pig {
    std::vector<std::string> itens;
    double value {0};
    int volume {0};
    int volumeMax {0};
    bool broken {false};

public:
    Pig(int volumeMax = 0) {
    this->volumeMax = volumeMax;
    this->itens = {};
    this->volume = 0;
    this->value = 0;
    this-> broken = false;

    }
    
    bool addCoin(Coin coin) {
        if(broken==false)
        {
        this->value += coin.getValue();
        this->volume += coin.getVolume();
        }
        else std::cout << "fail: the pig is broken"<<"\n";
        return {}; 
    }

    bool addItem(Item item) {
        if(broken==false)
        {
        this->volume += item.getVolume();
        this-> itens.push_back(item.getLabel());
        }
        else std::cout << "fail: the pig is broken"<<"\n";
        return {}; 
    }

    bool breakPig() {
        broken = true;
        this->volume = 0;
        return {}; 
    }

    double getCoins() {
        std::stringstream SS;
        if(broken)
        {
        SS << std::fixed << std::setprecision(2) << value ;
        std::string V = SS.str();
        std::cout << V;
        }
        else std::cout << "fail: you must break the pig first"<<"\n";
        return {}; 
    }

    std::string getItems() {
        std::stringstream SS;
        if(broken)
        {
        SS << aux::fmt(this->itens);
        itens.clear();
        }
        else SS << "fail: you must break the pig first"<<"\n";
        return SS.str(); 
    }

    std::string str() const {
        std::stringstream ss;
        ss << aux::fmt(this->itens) << " : "
           << aux::fmt(value) << "$ : "
           << volume <<  "/" << volumeMax << " : " 
           <<  (broken ? "broken" : "unbroken");
        std::string V = ss.str();
        std::cout << V;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Pig& pig) {
    return os << pig.str();
}

int main() {
    aux::Chain chain;
    aux::Param par;

    Pig pig;
    
    auto toint = aux::to<int>;

    chain["addCoin"] = [&]() { 
        if      (par[1] == "10") pig.addCoin(Coin(C10));
        else if (par[1] == "25") pig.addCoin(Coin(C25));
        else if (par[1] == "50") pig.addCoin(Coin(C50));
        else if (par[1] == "100") pig.addCoin(Coin(C100));
    };
    chain["init"]     = [&]() { pig = Pig(toint(par[1])); };
    chain["addItem"]  = [&]() { pig.addItem(Item(par[1], toint(par[2]))); };
    chain["break"]    = [&]() { pig.breakPig(); };
    chain["getCoins"] = [&]() { aux::show << pig.getCoins(); };
    chain["getItems"] = [&]() { aux::show << pig.getItems(); };
    chain["show"]     = [&]() { aux::show << pig.str(); };

    aux::execute(chain, par);
}

