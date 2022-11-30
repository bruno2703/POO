#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include "aux.hpp"


class Kid
{
private:
    int age;
    std::string name;

public:
    Kid(std::string name, int age)
    {
        this->age = age;
        this->name = name;
    }
    int getAge()
    {
        return age;
    }
    std::string getName()
    {
        return name;
    }
    std::string str()
    {
        return name + ":" + std::to_string(age);
    }
};

using PtrKid = std::shared_ptr<Kid>;

std::ostream &operator<<(std::ostream &os, PtrKid kid)
{
    return (os << kid->str());
}

class Trampoline
{
    std::list<PtrKid> waiting;
    std::list<PtrKid> playing;

    PtrKid removeFromList(std::string name, std::list<PtrKid> &lista)
    {
        for (auto it = lista.begin(); it != lista.end(); it++)
        {
            if ((*it)->getName() == name)
            {
                PtrKid kid = *it;
                lista.erase(it);
                return kid;
            }
        }
        return nullptr;
    }

public:
    Trampoline()
    {
        waiting = std::list<PtrKid>();
        playing = std::list<PtrKid>();
    }
    void arrive(PtrKid kid)
    {
        waiting.push_front(kid);
    }

    void enter()
    {
        if (waiting.size() > 0)
        {
            PtrKid kid = waiting.back();
            waiting.pop_back();
            playing.push_front(kid);
        }
    }

    void leave()
    {
        if (playing.size() > 0)
        {
            PtrKid kid = playing.back();
            playing.pop_back();
            waiting.push_front(kid);
        }
    }

    PtrKid removeKid(std::string name)
    {
        PtrKid kid = removeFromList(name, waiting);
        if (kid == nullptr)
        {
            kid = removeFromList(name, playing);
        }
        return kid;
    }

    std::string str() const {
        std::stringstream ss;
        std::vector<PtrKid> vWaiting(waiting.begin(), waiting.end());
        std::vector<PtrKid> vPlaying(playing.begin(), playing.end());
        ss << aux::fmt<PtrKid>(vWaiting) << " => "
           << aux::fmt<PtrKid>(vPlaying) ;
        std::string V = ss.str();
        return ss.str();
    }
};

int main()
{
    aux::Chain chain;
    aux::Param param;
    Trampoline tr;
    chain["arrive"] = [&]()
    { tr.arrive(std::make_shared<Kid>(param[1], aux::to<int>(param[2]))); };
    chain["enter"] = [&]()
    { tr.enter(); };
    chain["leave"] = [&]()
    { tr.leave(); };
    chain["remove"] = [&]()
    { tr.removeKid(param[1]); };
    chain["show"] = [&]()
    { std::cout << tr.str() << std::endl; };

    aux::execute(chain, param);
}