#include "info.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace Eendgine {

void Info::init() {}
void Info::close() {}

void Info::registerInt(const std::string& name, const uint32_t options) {
    if (_registeredInts.contains(name))
        return;
    _registeredInts[name] = registeredInt{
        0,       // value
        options, // options
        0,       // count
        0        // average
    };
}

void Info::registerFloat(const std::string& name, const uint32_t options) {
    if (_registeredFloats.contains(name))
        return;
    _registeredFloats[name] = registeredFloat{
        0.0f,    // value
        options, // options
        0,       // count
        0.0f     // average
    };
}

void Info::registerTime(const std::string& name, const uint32_t options) {
    if (_registeredTimes.contains(name))
        return;
    _registeredTimes[name] = registeredTime{
        0.0f,    // value
        0.0f,    // start
        options, // options
        0,       // count
        0.0f     // average
    };
}

void Info::updateInt(const std::string& name, const int update) {
    if (!_registeredInts.contains(name))
        return;
    auto tmp_reg = _registeredInts[name];
    if (tmp_reg.options & INFO_OPTION_AVERAGE) {
        if (tmp_reg.count != 0) {
            tmp_reg.average = (update + (tmp_reg.value * tmp_reg.count)) / (tmp_reg.count + 1);
        } else {
            tmp_reg.average = update;
        }
    }
    tmp_reg.value = update;
    tmp_reg.count++;
    _registeredInts[name] = tmp_reg;
}

void Info::updateFloat(const std::string& name, const float update) {
    if (!_registeredFloats.contains(name))
        return;
    auto tmp_reg = _registeredFloats[name];
    if (tmp_reg.options & INFO_OPTION_AVERAGE) {
        if (tmp_reg.count != 0) {
            tmp_reg.average = (update + (tmp_reg.value * tmp_reg.count)) / (tmp_reg.count + 1);
        } else {
            tmp_reg.average = update;
        }
    }
    tmp_reg.value = update;
    tmp_reg.count++;
    _registeredFloats[name] = tmp_reg;
}

void Info::startTime(const std::string& name) {
    if (!_registeredTimes.contains(name))
        return;
    _registeredTimes[name].start = SDL_GetTicks();
}

void Info::stopTime(const std::string& name) {
    if (!_registeredTimes.contains(name))
        return;
    float updatedValue = SDL_GetTicks() - _registeredTimes[name].start;
    auto tmp_reg = _registeredTimes[name];
    if (tmp_reg.options & INFO_OPTION_AVERAGE) {
        if (tmp_reg.count != 0) {
            tmp_reg.average =
                (updatedValue + (tmp_reg.value * tmp_reg.count)) / (tmp_reg.count + 1);
        } else {
            tmp_reg.average = updatedValue;
        }
    }
    tmp_reg.value = updatedValue;
    tmp_reg.count++;
    _registeredTimes[name] = tmp_reg;
}

template <typename T> void printInfoMap(const T& map) {
    for (auto const& [key, info] : map) {
        if (info.count != 0) {
            std::cout << key << ":\t" // key
                      << info.value;
            if (info.options & INFO_OPTION_AVERAGE) {
                std::cout << "\taverage:\t" << info.average;
            }
            std::cout << '\n';
        }
    }
}

void Info::print() {
    std::system("clear");
    printInfoMap(_registeredInts);
    printInfoMap(_registeredFloats);
    printInfoMap(_registeredTimes);
}
} // namespace Eendgine
