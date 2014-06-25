//
//  symbols.c
//  agent
//
//  Created by Tiago Rezende on 6/21/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#include <stdio.h>
#include "ent.h"

t_symbol
*s_on = NULL,
*s_awake = NULL,
*s_reset = NULL,
*s_start = NULL,
*s_update = NULL,
*s_late_update = NULL,
*s_fixed_update = NULL,
*s_animator_ik = NULL,
*s_animator_move = NULL,
*s_app_focus = NULL,
*s_app_pause = NULL,
*s_app_quit = NULL,
//*s_audio_filter_read = NULL,
*s_became_invisible = NULL,
*s_became_visible = NULL,
*s_collision_enter = NULL,
*s_collision_exit = NULL,
*s_collision_stay = NULL,
*s_collision_enter_2d = NULL,
*s_collision_exit_2d = NULL,
*s_collision_stay_2d = NULL,
//*s_connected_to_server = NULL,
*s_controller_collider_hit = NULL,
*s_destroy = NULL,
*s_disable = NULL,
//*s_disconnected_from_server = NULL,
*s_draw_gizmos = NULL,
*s_draw_gizmos_selected = NULL,
*s_enable = NULL,
//*s_failed_to_connect = NULL,
//*s_failed_to_connect_to_master_server = NULL,
*s_gui = NULL,
*s_joint_break = NULL,
*s_level_was_loaded = NULL,
//*s_master_server_event = NULL,
*s_mouse_down = NULL,
*s_mouse_drag = NULL,
*s_mouse_enter = NULL,
*s_mouse_exit = NULL,
*s_mouse_over = NULL,
*s_mouse_up = NULL,
*s_mouse_up_as_button = NULL,
//*s_network_instantiate = NULL,
*s_particle_collision = NULL,
//*s_player_connected = NULL,
//*s_player_disconnected = NULL,
*s_post_render = NULL,
*s_pre_cull = NULL,
*s_pre_render = NULL,
*s_render_image = NULL,
*s_render_object = NULL,
//*s_serialize_network_view = NULL,
//*s_server_initialized = NULL,
*s_trigger_enter = NULL,
*s_trigger_enter_2d = NULL,
*s_trigger_exit = NULL,
*s_trigger_exit_2d = NULL,
*s_trigger_stay = NULL,
*s_trigger_stay_2d = NULL,
//*s_validate = NULL,
*s_will_render_object = NULL;

t_symbol *s_gameobject = NULL,
    *s_instantiate = NULL,
    *s_localpos = NULL,
    *s_localrot = NULL,
    *s_localscale = NULL,
    *s_globalpos = NULL,
    *s_globalrot = NULL,
    *s_globallossyscale = NULL,
    *s_localmtx = NULL,
    *s_globalmtx = NULL;

void setup_symbols(void) {
    s_on = gensym("on");
    s_awake = gensym("awake");
    s_reset = gensym("reset");
    s_start = gensym("start");
    s_update = gensym("update");
    s_late_update = gensym("late-update");
    s_fixed_update = gensym("fixed-update");
    s_animator_ik = gensym("animator-ik");
    s_animator_move = gensym("animator-move");
    s_app_focus = gensym("app-focus");
    s_app_pause = gensym("app-pause");
    s_app_quit = gensym("app-quit");
    s_became_invisible = gensym("became-invisible");
    s_became_visible = gensym("became-visible");
    s_collision_enter = gensym("collision-enter");
    s_collision_exit = gensym("collision-exit");
    s_collision_stay = gensym("collision-stay");
    s_collision_enter_2d = gensym("collision-enter-2d");
    s_collision_exit_2d = gensym("collision-exit-2d");
    s_collision_stay_2d = gensym("collision-stay-2d");
    s_controller_collider_hit = gensym("controller-collider-hit");
    s_destroy = gensym("destroy");
    s_disable = gensym("disable");
    s_draw_gizmos = gensym("draw-gizmos");
    s_draw_gizmos_selected = gensym("draw-gizmos-selected");
    s_enable = gensym("enable");
    s_gui = gensym("gui");
    s_joint_break = gensym("joint-break");
    s_level_was_loaded = gensym("level-was-loaded");
    s_mouse_down = gensym("mouse-down");
    s_mouse_drag = gensym("mouse-drag");
    s_mouse_enter = gensym("mouse-enter");
    s_mouse_exit = gensym("mouse-exit");
    s_mouse_over = gensym("mouse-over");
    s_mouse_up = gensym("mouse-up");
    s_mouse_up_as_button = gensym("mouse-up-as-button");
    s_particle_collision = gensym("particle-collision");
    s_post_render = gensym("post-render");
    s_pre_cull = gensym("pre-cull");
    s_pre_render = gensym("pre-render");
    s_render_image = gensym("render-image");
    s_render_object = gensym("render-object");
    s_trigger_enter = gensym("trigger-enter");
    s_trigger_enter_2d = gensym("trigger-enter-2d");
    s_trigger_exit = gensym("trigger-exit");
    s_trigger_exit_2d = gensym("trigger-exit-2d");
    s_trigger_stay = gensym("trigger-stay");
    s_trigger_stay_2d = gensym("trigger-stay-2d");
    s_will_render_object = gensym("will-render-object");
    
    s_gameobject = gensym("gameobject");
    s_instantiate = gensym("instantiate");
    s_localpos = gensym("local-pos");
    s_localrot = gensym("local-rot");
    s_localscale = gensym("local-scale");
    s_globalpos = gensym("global-pos");
    s_globalrot = gensym("global-rot");
    s_globallossyscale = gensym("global-lossy-scale");
    s_localmtx = gensym("local-mtx");
    s_globalmtx = gensym("global-mtx");
}