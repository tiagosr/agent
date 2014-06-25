//
//  gameobject.cpp
//  agent
//
//  Created by Tiago Rezende on 6/21/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include "ent.h"
#include "gameobject.hpp"
#include "m_pd.h"

#include <cmath>

#include "quaternion.hpp"

static t_class *c_gameobject = NULL, *c_transform = NULL;
static t_class *c_localpos = NULL, *c_localrot = NULL, *c_localscale = NULL;
static t_class *c_globalpos = NULL, *c_globalrot = NULL, *c_globallossyscale = NULL;

cpp_gameobject *current_gameobject = NULL;

extern "C" void gameobject_set_current(cpp_gameobject *object) {
    current_gameobject = object;
}

struct _t_gameobject {
    t_object x_obj;
    t_outlet *out_msg;
};
typedef struct _t_transform t_transform;
struct _t_transform {
    t_object x_obj;
    t_outlet *out_msg;
};

static t_gameobject *gameobject_new(void) {
    t_gameobject *gameobject = (t_gameobject *)pd_new(c_gameobject);
    gameobject->out_msg = outlet_new(&gameobject->x_obj, gensym("out"));
    return gameobject;
}

static void gameobject_free(t_gameobject *gameobject) {
    outlet_free(gameobject->out_msg);
}

static void gameobject_bang(t_gameobject *gameobject) {
    if (current_gameobject) {
        outlet_symbol(gameobject->out_msg, current_gameobject->name);
    }
}

static void gameobject_name(t_gameobject *gameobject) {
    if (current_gameobject) {
        outlet_symbol(gameobject->out_msg, current_gameobject->name);
    }
}

static void gameobject_tags(t_gameobject *gameobject) {
    if (current_gameobject) {
        size_t tags_count = current_gameobject->tags.size();
        t_atom tags[tags_count];
        for (size_t i = 0; i < tags_count; i++) {
            SETSYMBOL(tags+i, current_gameobject->tags[i]);
        }
        outlet_list(gameobject->out_msg, gensym("tags"), tags_count, tags);
    }
}

static t_transform *transform_new(void) {
    t_transform *transform = (t_transform *)pd_new(c_transform);
    transform->out_msg = outlet_new(&transform->x_obj, gensym("out"));
    return transform;
}

static void transform_free(t_transform *transform) {
    outlet_free(transform->out_msg);
}

static void transform_localposition(t_transform *transform) {
    t_atom position[3];
    SETFLOAT(position, current_gameobject->x);
    SETFLOAT(position+1, current_gameobject->y);
    SETFLOAT(position+2, current_gameobject->z);
    outlet_list(transform->out_msg, gensym("vec3"), 3, position);
}

static void transform_set_localposition(t_transform *transform,
                                        t_symbol *symbol, int argc, t_atom *argv) {
    if (argc >= 2) {
        current_gameobject->x = atom_getfloat(argv);
        current_gameobject->y = atom_getfloat(argv+1);
        if (argc > 2) {
            current_gameobject->z = atom_getfloat(argv+2);
        }
    }
}

static void transform_localrotation(t_transform *transform) {
    t_atom position[4];
    SETFLOAT(position, current_gameobject->qw);
    SETFLOAT(position+1, current_gameobject->qx);
    SETFLOAT(position+2, current_gameobject->qy);
    SETFLOAT(position+3, current_gameobject->qz);
    outlet_list(transform->out_msg, gensym("quat"), 4, position);
}



static void transform_set_localrotation(t_transform *transform,
                                        t_symbol *symbol, int argc, t_atom *argv) {
    if (symbol == gensym("quat")) {
        if (argc == 4) {
            current_gameobject->qw = atom_getfloat(argv);
            current_gameobject->qx = atom_getfloat(argv+1);
            current_gameobject->qy = atom_getfloat(argv+2);
            current_gameobject->qz = atom_getfloat(argv+3);
        }
    } else if (symbol == gensym("mtx3")) {
        if (argc == 9) {
            t_float k[9];
            for (int i = 0; i < 9; i++) {
                k[i] = atom_getfloat(argv+i);
            }
            quat_from_rotation_matrix3(k,
                                       current_gameobject->qw,
                                       current_gameobject->qx,
                                       current_gameobject->qy,
                                       current_gameobject->qz);
        }
    }
}


static void transform_localscale(t_transform *transform) {
    t_atom position[3];
    SETFLOAT(position, current_gameobject->sx);
    SETFLOAT(position+1, current_gameobject->sy);
    SETFLOAT(position+2, current_gameobject->sz);
    outlet_list(transform->out_msg, gensym("vec3"), 3, position);
}



extern "C" void gameobject_setup(void) {
    c_gameobject = class_new(s_gameobject,
                             (t_newmethod)gameobject_new,
                             (t_method)gameobject_free,
                             sizeof(t_gameobject), CLASS_DEFAULT, A_NULL, 0);
    class_addbang(c_gameobject, gameobject_bang);
    class_addmethod(c_gameobject, (t_method)gameobject_name, gensym("name"), A_NULL, 0);
    class_addmethod(c_gameobject, (t_method)gameobject_tags, gensym("tags"), A_NULL, 0);
}

extern "C" void transform_setup(void) {
    c_transform = class_new(s_transform,
                            (t_newmethod)transform_new,
                            (t_method)transform_free,
                            sizeof(t_transform),
                            CLASS_DEFAULT, A_NULL, 0);
    class_addmethod(c_transform, (t_method)transform_localposition, gensym("local-position"), A_NULL, 0);
    class_addmethod(c_transform, (t_method)transform_localrotation, gensym("local-rotation"), A_NULL, 0);
    class_addmethod(c_transform, (t_method)transform_localscale, gensym("local-scale"), A_NULL, 0);
}

static t_transform *localpos_new(void) {
    t_transform *t = (t_transform *)pd_new(c_localpos);
    t->out_msg = outlet_new(&t->x_obj, gensym("vec3"));
    return t;
}
extern "C" void localpos_setup(void) {
    c_localpos = class_new(s_localpos,
                           (t_newmethod)localpos_new,
                           (t_method)transform_free,
                           sizeof(t_transform),
                           CLASS_DEFAULT, A_NULL, 0);
    class_addbang(c_localpos, (t_method)transform_localposition);
    class_addmethod(c_localpos, (t_method)transform_set_localposition,
                    gensym("set"), A_GIMME, 0);
}
