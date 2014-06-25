//
//  gameobject.h
//  agent
//
//  Created by Tiago Rezende on 6/21/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#ifndef agent_gameobject_h
#define agent_gameobject_h

#include <list>
#include <vector>

struct cpp_gameobject {
    t_ent *entity;
    std::vector<t_symbol *> tags;
    t_symbol *name;
    t_float x, y, z;
    t_float sx, sy, sz;
    t_float qw, qx, qy, qz;
    bool enabled;
};


#endif
