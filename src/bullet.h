#pragma once

#include <string>

namespace Bullet {
    class Bullet {
        private:
            std::string name;

        public:
            Bullet(): name("Bullet") {}

            std::string GetName() {
                return name;
            }

            void Start();
    };
}