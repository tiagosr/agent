//
//  ent.h
//  agent
//
//  Created by Tiago Rezende on 6/20/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#ifndef agent_ent_h
#define agent_ent_h
#include "m_pd.h"
#include "utlist.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _t_ent t_ent;
extern t_ent *current_ent;
typedef struct _t_does t_does;
typedef struct _t_gameobject t_gameobject;


typedef struct _t_on t_on;

extern t_class *c_does_class;

struct _t_on {
    t_object x_obj;
    t_canvas *canvas;
    t_outlet *out_msg;
    struct _t_on *next;
};

/*
 * Behaviour entry points
 * unabashedly copied from Unity's MonoBehaviour/Component class
 */

extern t_symbol
*s_on,
*s_awake,
*s_reset,
*s_start,
*s_update,
*s_late_update,
*s_fixed_update,
*s_animator_ik,
*s_animator_move,
*s_app_focus,
*s_app_pause,
*s_app_quit,
//*s_audio_filter_read,
*s_became_invisible,
*s_became_visible,
*s_collision_enter,
*s_collision_exit,
*s_collision_stay,
*s_collision_enter_2d,
*s_collision_exit_2d,
*s_collision_stay_2d,
//*s_connected_to_server,
*s_controller_collider_hit,
*s_destroy,
*s_disable,
//*s_disconnected_from_server,
*s_draw_gizmos,
*s_draw_gizmos_selected,
*s_enable,
//*s_failed_to_connect,
//*s_failed_to_connect_to_master_server,
*s_gui,
*s_joint_break,
*s_level_was_loaded,
//*s_master_server_event,
*s_mouse_down,
*s_mouse_drag,
*s_mouse_enter,
*s_mouse_exit,
*s_mouse_over,
*s_mouse_up,
*s_mouse_up_as_button,
//*s_network_instantiate,
*s_particle_collision,
//*s_player_connected,
//*s_player_disconnected,
*s_post_render,
*s_pre_cull,
*s_pre_render,
*s_render_image,
*s_render_object,
//*s_serialize_network_view,
//*s_server_initialized,
*s_trigger_enter,
*s_trigger_enter_2d,
*s_trigger_exit,
*s_trigger_exit_2d,
*s_trigger_stay,
*s_trigger_stay_2d,
//*s_validate,
*s_will_render_object;

extern t_symbol
*s_animation,
*s_animator,
*s_camera,
*s_collider,
*s_collider_2d,
*s_constant_force,
*s_hinge_joint,
*s_light,
//*s_network_view,
*s_particle_emitter,
*s_particle_system,
*s_renderer,
*s_rigid_body,
*s_rigid_body_2d,
*s_transform,

*s_get_ent,
*s_get_tag,
*s_get_name;

void does_add_on(t_does *does, t_on *on, t_symbol *sym);
void does_remove_on(t_does *does, t_on *on);


void setup_symbols(void);
void ent_class_setup(void);
void does_class_setup(void);
    
#ifdef __cplusplus
};
#endif

#endif
