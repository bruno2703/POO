#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <iomanip> //setprecision
#include "aux.hpp"
using namespace std;


class Grafite{
    float calibre;
    std::string dureza;
    int tamanho;
public:
    Grafite(float calibre, std::string dureza, int tamanho) {
        this->calibre = calibre;
        this->dureza = dureza;
        this->tamanho = tamanho;
    }
    int desgastePorFolha() {
        if (dureza == "HB")
            return 1;
        if (dureza == "2B")
            return 2;
        if (dureza == "4B")
            return 4;
        return 6;
    }
    float getCalibre() {
        return calibre;
    }
    std::string getDureza() {
        return dureza;
    }
    int getTamanho() {
        return tamanho;
    }
    void setTamanho(int tamanho) {
        this->tamanho = tamanho;
    }
    std::string str() const {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << calibre << ":" << dureza << ":" << tamanho;
        return os.str();
    }
};
std::ostream& operator<<(std::ostream& os, Grafite g) {
    return os << g.str();
}

using PGrafite = std::shared_ptr<Grafite>;

std::ostream& operator<<(std::ostream& os, PGrafite g) {
    return os << "[" << (g == nullptr ? "" : g->str()) << "]";
}

struct Lapiseira{
    float calibre {0.f};
    PGrafite grafite {nullptr};
    std::list<PGrafite> tambor;

    Lapiseira(float calibre = 0.0) {
        this->calibre = calibre;
    }

    bool inserir(PGrafite grafite) {
        if (grafite->getCalibre() == calibre) {
            tambor.push_back(grafite);
            return true;
        }
        cout << "fail: calibre incompatível" << endl;
        return false;
    }

    PGrafite remover() {
        if (grafite == nullptr)
            return nullptr;
        PGrafite g = grafite;
        grafite = nullptr;
        return g;
    }

    void write() {
        if(grafite == nullptr)
        {
            cout << "fail: nao existe grafite no bico" << endl;
        }
        else if(grafite->getTamanho() <= 10)
        {
            cout << "fail: tamanho insuficiente" << endl;
        }
        else if((grafite->getTamanho() - grafite->desgastePorFolha()) <10)
        {
            grafite->setTamanho(10);
            cout << "fail: folha incompleta" << endl;
        }
        else
        {
        grafite->setTamanho(grafite->getTamanho() - grafite->desgastePorFolha());
        }
    }
    void puxar() {
        if(grafite != nullptr)
        {
            cout << "fail: ja existe grafite no bico" << endl;
        }
        else if(tambor.empty())
        {
            cout << ("tambor vazio") << endl;
        }
        else{
        grafite = tambor.front();
        tambor.pop_front();
        }
    }
    std::string str() const {
        std::ostringstream os;
        os << "calibre: " << calibre 
           << ", bico: " << grafite
           << ", tambor: {" << (tambor | aux::JOIN("")) << "}";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Lapiseira& l) {
    return os << l.str();
}

int main() {
    aux::Chain chain;
    aux::Param param;
    Lapiseira lapiseira;

    auto FLOAT = [&param](int index) {return aux::to<float>(param[index]);};
    auto __INT = [&param](int index) {return aux::to<int>(param[index]);};

    chain["init"]   = [&]() { lapiseira = Lapiseira(FLOAT(1)); };
    chain["show"]   = [&]() { std::cout << lapiseira << std::endl; };
    chain["insert"] = [&]() { lapiseira.inserir(std::make_shared<Grafite>(FLOAT(1), param[2], __INT(3))); };
    chain["remove"] = [&]() { lapiseira.remover(); };
    chain["pull"]   = [&]() { lapiseira.puxar(); };
    chain["write"]  = [&]() { lapiseira.write(); };

    aux::execute(chain, param);
}
