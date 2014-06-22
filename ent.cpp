//
//  ent.c
//  agent
//
//  Created by Tiago Rezende on 6/20/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include <stdio.h>
#include "ent.h"
#include "g_canvas.h"
#include "pdutils.h"
#include "uthash.h"


static t_symbol *s_ent = NULL;

struct _t_ent {
    t_object x_obj;
    //t_inlet *in_msg;
    t_symbol *name;
    t_outlet *out_msg;
};


t_ent *current_ent;

t_class *c_ent_class;

static t_ent *ent_new(t_symbol *name) {
    t_ent *obj = (t_ent *)pd_new(c_ent_class);
    //obj->in_msg = inlet_new(obj->x_obj, obj->x_obj.ob_pd, NULL, gensym(""));
    obj->name = name;
    obj->out_msg = outlet_new(&obj->x_obj, gensym("out"));
    return obj;
}

static void ent_destroy(t_ent *ent) {
    outlet_free(ent->out_msg);
}


static void ent_event(t_ent *ent, t_symbol *event) {
    t_atom args[1];
    SETSYMBOL(args, event);
    outlet_list(ent->out_msg, gensym("event"), 1, args);
}

extern "C" void ent_class_setup(void) {
    s_ent = gensym("ent");
    c_ent_class = class_new(s_ent,
                            (t_newmethod)ent_new, (t_method)ent_destroy,
                            sizeof(t_ent), CLASS_DEFAULT,
                            A_DEFSYMBOL, 0);
    class_addmethod(c_ent_class, (t_method)ent_event, gensym("event"), A_SYMBOL, 0);
}

