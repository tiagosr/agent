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

struct _t_gameobject {
    t_ent *entity;
    std::list<t_symbol *> tags;
    t_symbol *name;
    t_float x, y, z;
    t_float sx, sy, sz;
    t_float qx, qy, qz, qw;
    bool enabled;
};


#endif
