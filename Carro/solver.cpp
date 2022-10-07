/*
1)
Fiz sozinho
2)
Pequenas duvidas em relacao a utilidade do this-> 
3)
3 horas apenas
*/

#include <iostream>
#include <sstream>
#include "aux.hpp"


class Car
{
public:
    int pass {0};
    int passMax {0};
    int gas {0};
    int gasMax {0};
    int km {0};
    
    Car(int passMax = 2, int gasMax = 100)
    {
        this->passMax = passMax;
        this->gasMax = gasMax;
    }

    void enter()
    {
        if(pass == passMax)
        {
            std::cout << "fail: limite de pessoas atingido" <<"\n";
        } else
        {
            pass += 1;
        }
    }

    void leave()
    {
        if(pass == 0) {
            std::cout << "fail: nao ha ninguem no carro" <<"\n";
        } else
        {
            pass -= 1;
        }
    }

    void fuel(int combustivel)
    {
        if(gasMax <= combustivel)
        {
            gas = gasMax;
        }
        else
        {
        gas += combustivel;
        }
    }

    void drive(int distancia)
    {
        if(pass == 0)
        {
            std::cout << "fail: nao ha ninguem no carro" << "\n";
        }
        else if(gas == 0)
        {
            std::cout << "fail: tanque vazio" <<"\n";
        }
        else if(distancia >= gas)
        {
            km += gas;
            std:: cout << "fail: tanque vazio apos andar " << gas <<"\n";
            gas = 0;
        }
        else
        {
            km += distancia;
            gas -= distancia;
        }
    }
    std::string str() {
        std::stringstream ss;
        ss << "pass: " << pass << ", gas: " << gas << ", km: " << km;
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param ui;

    Car car;

    chain["help"]  = [&](){ aux::show << "show; enter; leave; fuel _gas; drive _km; end"; };
    chain["show"]  = [&](){ aux::show << car.str(); };
    chain["enter"] = [&](){ car.enter(); };
    chain["leave"] = [&](){ car.leave(); };
    chain["fuel"]  = [&](){ car.fuel(aux::to<int>(ui[1])); };
    chain["drive"] = [&](){ car.drive(aux::to<int>(ui[1])); };

    aux::execute(chain, ui);
}