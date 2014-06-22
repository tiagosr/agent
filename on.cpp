//
//  on.c
//  agent
//
//  Created by Tiago Rezende on 6/21/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include "ent.h"
#include "g_canvas.h"

static t_class *on_class = NULL;

t_on *on_new(t_symbol *sym) {
    t_on *on = (t_on *)pd_new(on_class);
    t_canvas *canvas = canvas_getcurrent();
    if(canvas->gl_obj.te_g.g_pd == c_does_class) {
        does_add_on((t_does *)canvas, on, sym);
    }
    on->out_msg = outlet_new(&on->x_obj, gensym("event"));
    return on;
}
static void on_destroy(t_on *on) {
    outlet_free(on->out_msg);
    t_canvas *canvas = canvas_getcurrent();
    if (canvas->gl_obj.te_g.g_pd == c_does_class) {
        does_remove_on((t_does *)canvas, on);
    }
}

extern "C" void on_setup(void) {
    on_class = class_new(s_on, (t_newmethod)on_new, (t_method)on_destroy,
                         sizeof(t_on), CLASS_NOINLET, A_SYMBOL, 0);
    
}
