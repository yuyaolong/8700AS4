//
//  explotion.cpp
//  OOAS3
//
//  Created by yuyaolong on 15/10/20.
//  Copyright © 2015年 yuyaolong. All rights reserved.
//

#include "explotion.h"
#include "gamedata.h"
Explotion:: Explotion(const std::string& name):MultiSprite(name,
                                                
                                                Gamedata::getInstance().getXmlInt("world/width")*(rand()*1.0/RAND_MAX),
                                                Gamedata::getInstance().getXmlInt("world/height")*(rand()*1.0/RAND_MAX),
                                                Gamedata::getInstance().getXmlInt(name+"/speedX")*(rand()*1.0/RAND_MAX+0.3),
                                                Gamedata::getInstance().getXmlInt(name+"/speedY")*(rand()*1.0/RAND_MAX+0.3)
                                                ){}

