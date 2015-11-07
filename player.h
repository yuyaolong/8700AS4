//
//  player.hpp
//  8700AS4
//
//  Created by yuyaolong on 15/11/5.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "gamedata.h"
#include "twowaysprite.h"


class Player: public TwoWaySprite{
public:
    Player(const std::string&);
    virtual ~Player(){};
    
    virtual void draw() const;
    virtual void update(unsigned int ticks);
    
    void setStatus(PlayerStatus s);

private:
    PlayerStatus state;
    bool gameOver;
    float velocity[2];
    
    Player(const Player&);
    Player& operator=(const Player&);
    
    
    
};




#endif /* player_hpp */
