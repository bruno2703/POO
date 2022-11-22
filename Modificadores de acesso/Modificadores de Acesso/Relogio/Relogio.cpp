#include <iostream>
#include <sstream>
#include <iomanip>
#include <aux.hpp>

class Time {
private:
    int hour = 0;
    int minute = 0;
    int second = 0;
   
public:
    Time(int hour = 0, int minute = 0, int second = 0) {
        setHour(hour);
        setMinute(minute);
        setSecond(second);
    }
    void setHour(int hour) {
        if (hour < 0 || hour > 23) {
            std::cout << "fail: hora invalida";
        }
        this->hour = hour;
    }
    void setMinute(int minute) {
        if (minute < 0 || minute > 59) {
            std::cout << "fail: minuto invalido";
        }
        this->minute = minute;
    }
    void setSecond(int second) {
        if (second < 0 || second > 59) {
            std::cout << "fail: segundo invalido";
        }
        this->second = second;
    }
    int getHour() {
        return hour;
    }
    int getMinute() {
        return minute;
    }
    int getSecond() {
        return second;
    }
    void nextSecond(){
        second++;
        if (second > 59) {
            second = 0;
            minute++;
            if (minute > 59) {
                minute = 0;
                hour++;
                if (hour > 23) {
                    hour = 0;
                }
            }
        }
    }
    std::string str() {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hour << ":"
           << std::setfill('0') << std::setw(2) << minute << ":"
           << std::setfill('0') << std::setw(2) << second;
        return ss.str();
    }
};

int main() {
    aux::Chain chain;
    aux::Param param;
    Time time;

    auto INT = aux::STR2<int>();

    chain["set"] = [&]() {
        time.setHour(INT(param[1]));
        time.setMinute(INT(param[2]));
        time.setSecond(INT(param[3]));
    };
    chain["init"] = [&]() {
        time = Time(INT(param[1]), INT(param[2]), INT(param[3]));
    };
    chain["show"] = [&]() {
        std::cout << time.str() << '\n';
    };
    chain["next"] = [&]() {
        time.nextSecond();
    };

    aux::execute(chain, param);
}
