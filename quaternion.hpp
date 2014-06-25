//
//  quaternion.hpp
//  agent
//
//  Created by Tiago Rezende on 6/24/14.
//  Copyright (c) 2014 Pixel Of View. All rights reserved.
//

#ifndef agent_quaternion_hpp
#define agent_quaternion_hpp

#include "m_pd.h"
#include <cmath>

inline void quat_to_rotation_matrix3(t_float &qw, t_float &qx,
                                     t_float &qy, t_float &qz,
                                     t_float *k[]) {
    t_float tx = qx*qx, ty = qy*qy, tz = qz*qz;
    t_float twx = tx*qw, twy = ty*qw, twz = tz*qw;
    t_float txx = tx*qx, txy = ty*qx, txz = tz*qx;
    t_float tyy = ty*qy, tyz = tz*qy;
    t_float tzz = tz*qz;
    
    *k[0] = 1.0f - (tyy + tzz);
    *k[1] = txy - twz;
    *k[2] = txz + twy;
    *k[3] = txy + twz;
    *k[4] = 1.0f - (txx + tzz);
    *k[5] = tyz - twx;
    *k[6] = txz - twy;
    *k[7] = tyz + twx;
    *k[8] = 1.0f - (txx + tyy);
}
inline void quat_from_rotation_matrix3(t_float k[],
                                       t_float &qw, t_float &qx,
                                       t_float &qy, t_float &qz) {
    t_float trace = k[0]+k[4]+k[8];
    t_float root;
    if (trace > 0.0f) {
        root = sqrtf(trace + 1.0f);
        qw = 0.5f*root;
        root = 0.5f/root;
        qx = (k[7]-k[5])*root;
        qy = (k[2]-k[6])*root;
        qz = (k[3]-k[1])*root;
    } else {
        static size_t sNext[3] = {1, 2, 0};
        size_t i = 0;
        if (k[4] < k[0]) {
            i = 1;
        }
        if (k[8] < k[i+3*i]) {
            i = 2;
        }
        size_t j = sNext[i];
        size_t l = sNext[j];
        root = sqrtf(k[i+3*i] - k[j+3*j] - k[l+3*l] + 1.f);
        t_float *apkquat[3] = {&qx, &qy, &qz};
        *apkquat[i] = 0.5f * root;
        root = 0.5f / root;
        qw = (k[j+3*l]-k[l+3*j])*root;
        *apkquat[j] = (k[i+3*j]+k[j+3*i])*root;
        *apkquat[l] = (k[i+3*l]+k[l+3*i])*root;
    }
}


#endif
