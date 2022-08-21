#include <iostream>
#include "bullet.h"
#include "config.h"

int main(void)
{
    Bullet::Bullet* b = new Bullet::Bullet();
    std::cout << "Service Name: " << b->GetName() << std::endl;

    b->Start();
    
    return 0;
}