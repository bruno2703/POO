/*
1)
Fiz sozinho
2)
Sem duvidas
3)
2 horas apenas
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include "aux.hpp"

struct Calculator {
    int batteryMax;
    int battery;
    float display;

    Calculator(int batteryMax)
    {
        this->batteryMax = batteryMax;
        battery=0;
        display=0;
    }

    void chargeBattery(int value)
    {
         battery += value;
         if(battery > batteryMax) battery = batteryMax;
    }

    bool useBattery()
    {
        if(battery <= 0)
        {
            std::cout << "fail: bateria insuficiente" <<"\n";
            return false;
        } 
        else
        {
            battery-- ;
            return true;
        }
    }

    void sum(int a, int b)
    { 
        if(useBattery()) display = a+b;
    }

    void division(int num, int den)
    {
        if(useBattery())
        {
            if(den == 0) std::cout << "fail: divisao por zero" <<"\n";
            else display = (float) num/den;
        }
    }

    std::string str() { 
        std::stringstream ss;
        ss << "display = " << std::fixed << std::setprecision(2) << this->display;
        ss << ", battery = " << this->battery;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Calculator c) {
    return (os << c.str());
}

int main() {
    Calculator c(0);
    aux::Chain chain;
    aux::Param param;

    // função para obter um parâmetro convertido para inteiro
    auto par_int = [&param](int index) { return aux::to<int>(param[index]); };

    chain["show"]   = [&]() { std::cout << c << std::endl;         };
    chain["init"]   = [&]() {  c = Calculator(par_int(1)          ); };
    chain["charge"] = [&]() { c.chargeBattery(par_int(1)          ); };
    chain["sum"]    = [&]() {           c.sum(par_int(1), par_int(2)); };
    chain["div"]    = [&]() {      c.division(par_int(1), par_int(2)); };

    aux::execute(chain, param);
}