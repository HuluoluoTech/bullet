#include <iostream>
#include "bullet.h"
#include "config.h"

int main(void)
{
    Bullet::Bullet* b = new Bullet::Bullet();
    b->Start();
    
    exit(EXIT_SUCCESS);
}