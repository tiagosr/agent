//
//  does.c
//  agent
//
//  Created by Tiago Rezende on 6/20/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include <stdio.h>
#include "ent.h"
#include "g_canvas.h"
#include "pdutils.h"
#include <list>
#include <map>


static t_symbol *s_does = NULL;
typedef std::list<t_on *> t_on_list;
typedef std::map<t_symbol *, t_on_list> t_on_map;
struct t_does_canvas_item {
    t_canvas *canvas;
    int refcount;
};

typedef std::map<t_symbol *, t_does_canvas_item> t_does_canvas_map;
static t_does_canvas_map does_canvases;

struct _t_does {
    t_object x_obj;
    t_symbol *sym_name;
    t_outlet *out_msg;
    t_on_map *ons;
};


t_class *c_does_class;

t_canvas *does_canvas_for_sym(t_symbol *sym) {
    if (does_canvases.count(sym) != 0) {
        return does_canvases[sym].canvas;
    }
    return NULL;
}

t_canvas *does_canvas_get_and_add_sym_ref(t_symbol *sym) {
    if (does_canvases.count(sym) != 0) {
        does_canvases[sym].refcount++;
        return does_canvases[sym].canvas;
    }
    return NULL;
}

void does_canvas_set_for_sym(t_symbol *sym, t_canvas *canvas) {
    does_canvases[sym] = {canvas, 1};
}

void does_canvas_rm_sym_ref(t_symbol *sym) {
    if (does_canvases.count(sym) != 0) {
        if (--does_canvases[sym].refcount <= 0) {
            canvas_free(does_canvases[sym].canvas);
            does_canvases.erase(sym);
        }
    }
}

static t_does *does_new(t_symbol *name) {
    t_does *does = (t_does *)pd_new(c_does_class);
    does->ons = new (std::nothrow) t_on_map;
    //does->does_canvas = canvas_new(NULL, NULL, 6, args);
    //canvas_unsetcurrent(does->does_canvas);
    t_canvas *canvas = does_canvas_get_and_add_sym_ref(name);
    if (!canvas) {
        t_atom args[6];
        SETFLOAT(args+0, 0);
        SETFLOAT(args+1, 0);
        SETFLOAT(args+2, 400);
        SETFLOAT(args+3, 400);
        SETSYMBOL(args+4, name);
        SETFLOAT(args+5, 1);
        canvas = canvas_new(NULL, NULL, 6, args);
        //printf("does: new canvas: %X\n", (unsigned)canvas);
        does_canvas_set_for_sym(name, canvas);
        canvas_unsetcurrent(canvas);
    }
    does->sym_name = name;
    does->out_msg = outlet_new(&does->x_obj, gensym("out"));
    
    return does;
}

extern "C" void does_add_on(t_does *does, t_on *on, t_symbol *sym) {
    if (does->ons->count(sym) == 0) {
        (*does->ons)[sym] = t_on_list();
    }
    (*does->ons)[sym].push_back(on);
}

extern "C" void does_remove_on(t_does *does, t_on *on) {
    for (t_on_map::iterator map_i = does->ons->begin(); map_i != does->ons->end(); ++map_i) {
        map_i->second.remove(on);
    }
}

static void does_destroy(t_does *does) {
    outlet_free(does->out_msg);
    does_canvas_rm_sym_ref(does->sym_name);
    delete does->ons;
}

static void does_click(t_does *does, t_float x, t_float y, t_float w, t_float h, t_float font) {
    //printf("click?\n");
    //post("click!");
    //printf("click! %X\n",(unsigned int)does_canvas_for_sym(does->sym_name));
    canvas_vis(does_canvas_for_sym(does->sym_name), 1);
    //printf("vis!\n");
}

/*
static void does_rename(t_does *does, t_symbol *sym) {
    canvas_rename(does_canvas_for_sym(does->sym_name), sym, 0);
}
 */

static void does_event(t_does *does, t_symbol *event) {
    if (does->ons->count(event)) {
        t_on_list &l = (*does->ons)[event];
        t_on_list::const_iterator i = l.begin();
        while ((++i) != l.end()) {
            outlet_bang((*i)->out_msg);
        }
    }
    t_atom a[1];
    SETSYMBOL(a, event);
    outlet_anything(does->out_msg, gensym("event"), 1, a);
}



void does_class_setup(void) {
    s_does = gensym("does");
    c_does_class = class_new(s_does,
                             (t_newmethod)does_new, (t_method)does_destroy,
                             sizeof(t_does),
                             CLASS_PATCHABLE,
                             A_SYMBOL, 0);
    class_addmethod(c_does_class, (t_method)does_click,
                    gensym("click"), A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, 0);
    /*
    class_addmethod(c_does_class, (t_method)does_rename,
                    gensym("rename"), A_DEFSYMBOL, 0);
     */
    class_addmethod(c_does_class, (t_method)does_event, gensym("event"), A_SYMBOL, 0);
}


