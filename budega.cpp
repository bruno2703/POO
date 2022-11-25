#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include "aux.hpp"

class Pessoa
{
private:
    std::string nome;

public:
    Pessoa(std::string nome)
    { 
        this->nome = nome;
    }
    std::string getNome() const
    {
        return nome;
    }
    void setNome(std::string nome)
    {
        this->nome = nome;
    }
    std::string toString() const
    {
        return nome;
    }
    std::string str() const
    {
        std::stringstream ss;
        ss << nome;
        return ss.str();
    }
};
std::ostream &operator<<(std::ostream &os, const Pessoa &p)
{
    return (os << p.str());
}

class Mercantil
{
private:
    std::vector<std::shared_ptr<Pessoa>> caixas;  // caixas do supermercado
    std::list<std::shared_ptr<Pessoa>> esperando; // lista de clientes esperando

    bool validarIndice(int indice)
    {
        if (indice < 0 || indice >= caixas.size())
        {
            throw std::out_of_range("Indice invalido");
        }
        return true;
    }

public:
    Mercantil(int qtd_caixas)
    { 
        caixas = std::vector<std::shared_ptr<Pessoa>>(qtd_caixas, nullptr);
    }

    void chegar(const std::shared_ptr<Pessoa> &person)
    {
        esperando.push_back(person);
    }

    bool chamarNoCaixa(int indice)
    {
        validarIndice(indice);
        if(caixas[indice] != nullptr)
        {
            std::cout << "fail: caixa ocupado" << std::endl;
            return false;
        }
        else if(esperando.empty())
        {
            std::cout << "fail: sem clientes" << std::endl;
            return false;
        }
        else{
        caixas[indice] = esperando.front();
        esperando.pop_front();
        return true;
        }
    }

    std::shared_ptr<Pessoa> finalizar(int indice)
    {
        if(indice < 0 || indice >= caixas.size()){
            std::cout << "fail: caixa inexistente" << std::endl;
            return nullptr;
        }
        else if(caixas[indice] == nullptr)
        {
            std::cout << "fail: caixa vazio" << std::endl;
            return nullptr;
        }
        else
        {
        auto cliente = caixas[indice];
        caixas[indice] = nullptr;
        return cliente;
        }
    }

std::string str() const
    {
        int i = 0;
        auto fn = [&i](auto p)
        {
            std::stringstream ss;
            ss << " " << i++ << ":" << (p == nullptr ? "-----" : p->getNome()) << " ";
            return ss.str();
        };
        std::stringstream os;
        os << "Caixas: |" << (caixas | aux::MAP(fn) | aux::JOIN("|")) << "|\n"
           << "Espera: " << (esperando | aux::MAP(LAMBDA(x, *x)) | aux::FMT());
        return os.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Mercantil &b)
{
    return (os << b.str());
}

int main()
{
    aux::Chain chain;
    aux::Param par;

    Mercantil bank(0);

    chain["init"] = [&]()
    { bank = Mercantil(aux::to<int>(par[1])); };
    chain["call"] = [&]()
    { bank.chamarNoCaixa(aux::to<int>(par[1])); };
    chain["finish"] = [&]()
    { bank.finalizar(aux::to<int>(par[1])); };
    chain["arrive"] = [&]()
    { bank.chegar(std::make_shared<Pessoa>(par[1])); };
    chain["show"] = [&]()
    { std::cout << bank << '\n'; };

    aux::execute(chain, par);
}
