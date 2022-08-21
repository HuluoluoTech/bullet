#include <iostream>
#include "bullet.h"
#include "config.h"

int main(void)
{
    std::cout << "Hello world." << Bullet::Config::MAX_HUB << std::endl;

    Bullet::Bullet* b = new Bullet::Bullet();
    std::cout << b->GetName() << std::endl;
    b->Start();
    
    return 0;
}