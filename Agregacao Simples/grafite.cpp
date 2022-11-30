#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include "aux.hpp"

class Lead {
    float thickness;
    std::string hardness;
    int size;

public:
    Lead(float thickness, std::string hardness, int size) {

        this->thickness = thickness;
        this->hardness = hardness;
        this->size = size;
    }

    int usagePerSheet() const {

        if (hardness == "HB") {
            return 1;
        } else if (hardness == "2B") {
            return 2;
        } else if (hardness == "4B") {
            return 4;
        } else if (hardness == "6B") {
            return 6;
        } else {
            return 0;
        }
    }

    float getThickness() const {
        return thickness;
    }

    std::string getHardness() const {
        return hardness;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        this->size = size;
    }
    std::string str() const {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) 
           << thickness << ":" << hardness << ":" << size;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& ss, Lead gr) {
    return ss << gr.str();
}

struct Pencil {
    float thickness {0.f};
    std::shared_ptr<Lead> tip {nullptr};

    Pencil(float thickness = 0.0) { 
        this->thickness = thickness;
    }

    bool hasGrafite() {
        return tip != nullptr;
    }

    bool insert(std::shared_ptr<Lead> grafite) {
        if (tip == nullptr && grafite->getThickness() == thickness) {
            tip = grafite;
            return true;
        }
        else if(tip != nullptr){
            std::cout << "fail: ja existe grafite"  << std::endl;
            return false;
        } 
        else {
            std::cout << "fail: calibre incompativel" << std::endl;
            return false;
        }
    }

    std::shared_ptr<Lead> remove() {
        if (tip != nullptr) {
            return std::exchange(tip, nullptr);
        } else {
            return nullptr;
        }
    }


void writePage() {

        if (tip != nullptr) {
            int size = tip->getSize();
            int usage = tip->usagePerSheet();
            int diferenca = (size-usage);

            if(size > 10)
            {
                if(diferenca >= 10)
                {
                    tip->setSize(diferenca);
                }
                else
                {
                    tip->setSize(10);
                    std::cout << "fail: folha incompleta" << std::endl;
                }
            } 
            else
            {
                std::cout << "fail: tamanho insuficiente" << std::endl;
            }


        }
        else
            std::cout << "fail: nao existe grafite" << std::endl;
    }

    std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}

int main() {
    aux::Chain chain;
    aux::Param ui;

    Pencil pencil;

    auto tofloat = aux::to<float>;
    auto toint   = aux::to<int>;

    chain["show"]   = [&]() { std::cout << pencil << std::endl; };
    chain["init"]   = [&]() { pencil = Pencil(tofloat(ui[1])); };
    chain["insert"] = [&]() { pencil.insert(std::make_shared<Lead>(tofloat(ui[1]), ui[2], toint(ui[3]))); };
    chain["remove"] = [&]() { pencil.remove(); };
    chain["write"]  = [&]() { pencil.writePage(); };

    aux::execute(chain, ui);
}
