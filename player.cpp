//
//  player.cpp
//  8700AS4
//
//  Created by yuyaolong on 15/11/5.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "player.h"

#include "frameFactory.h"

Player::Player(const std::string& name):
        TwoWaySprite(name),
        state(MOVELEFT),
        gameOver(false)
{
    velocity[0] =abs(Gamedata::getInstance().getXmlInt(name+"/speedX"));
    velocity[1] =abs(Gamedata::getInstance().getXmlInt(name+"/speedY"));
}



void Player::draw() const
{
    if (!gameOver) {
         TwoWaySprite::draw();
    }
}

void Player::setStatus(PlayerStatus s)
{
    state = s;
    switch (state) {
        case STAND:
            velocityX(0);
            velocityY(0);
            break;
        case MOVERIGHT:
            velocityX(velocity[0]);
            velocityY(0);
            flipX = 1;
            break;
        case MOVELEFT:
            velocityX(-1*velocity[0]);
            velocityY(0);
            flipX = -1;
            break;
        case MOVEUP:
            velocityX(0);
            velocityY(-1*velocity[1]);
            break;
        case MOVEDOWN:
            velocityX(0);
            velocityY(velocity[1]);
            break;
        default:
            break;
    }
}


void Player:: update(unsigned int ticks)
{
    if (!gameOver) {
       
        TwoWaySprite::update(ticks);
                
        
        }
    
    
   
}

