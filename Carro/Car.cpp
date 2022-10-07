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
#include <vector>

class Car
{
public:
    int pass {0};
    int passMax {0};
    int gas {0};
    int gasMax {0};
    int km {0};
    
    //1. sempre inicialize
    //2. sempre deixe um construtor default

    //sobrecarga de método
    Car(int passMax = 2, int gasMax = 100)
    {
        this->passMax = passMax;
        this->gasMax = gasMax;
    }

    //método
    void entrar()
    {
        if(pass == passMax)
        {
            std::cout << "fail: limite de pessoas atingido";
        } else
        {
            pass += 1;
        }
    }

    void leave()
    {
        if(pass == 0) {
            std::cout << "fail: nao ha ninguem no carro";
        } else
        {
            pass -= 1;
        }
    }

    void fuell(int combustivel)
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
            std::cout << "fail: nao ha ninguem no carro";
        }
        else if(gas == 0)
        {
            std::cout << "fail: tanque vazio";
        }
        else if(distancia >= gas)
        {
            km += gas;
            std:: cout << "fail: tanque vazio apos andar " << gas;
            gas = 0;
        }
        else
        {
            km += distancia;
            gas -= distancia;
        }
    }
    //metodo
    std::string str() {
        std::stringstream ss;
        ss << "pass: " << pass << ", gas: " << gas << ", km: " << km;
        return ss.str();
    }
};

int main()
{
    Car car;
    std::cout << car.str() << '\n';
    car.entrar();
    car.fuell(50);
    std::cout << car.str() << '\n';
    car.entrar();
    car.drive(70);
    car.drive(10);
    std::cout << car.str() << '\n';
    car.entrar();
    car.leave();
    std::cout << car.str() << '\n';
    
    

}