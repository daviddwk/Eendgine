#pragma once
#include <map>
#include <stdint.h>
#include <string>

#define INFO_OPTION_NONE ((0x00000000))
#define INFO_OPTION_AVERAGE ((0x00000001))

namespace Eendgine {
class Info {
    public:
        static void init();
        static void close();

        static void registerInt(const std::string& name, const uint32_t options);
        static void registerFloat(const std::string& name, const uint32_t options);
        static void registerTime(const std::string& name, const uint32_t options);

        static void updateInt(const std::string& name, const int update);
        static void updateFloat(const std::string& name, const float update);

        static void startTime(const std::string& name);
        static void stopTime(const std::string& name);

        static void print();

    private:
        struct registeredInt {
                int value;
                uint32_t options;
                uint64_t count;
                int average;
        };
        struct registeredFloat {
                float value;
                uint32_t options;
                uint64_t count;
                float average;
        };
        struct registeredTime {
                float value;
                float start;
                uint32_t options;
                uint64_t count;
                float average;
        };

        inline static std::map<std::string, registeredInt> _registeredInts;
        inline static std::map<std::string, registeredFloat> _registeredFloats;
        inline static std::map<std::string, registeredTime> _registeredTimes;
};
} // namespace Eendgine
