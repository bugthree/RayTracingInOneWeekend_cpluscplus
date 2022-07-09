#ifndef RAY_H
#define RAY_H

#include "vec3.h"

///****************************************************************************
/// @brief   : 关于 光线追踪 射线部分的类，由起点和方向组成
/// @father  : 
/// @child   : 
/// @author  : bugthree
/// @date    : 2022-07-02      
/// @file    : 
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}
    // 起点
    point3 origin() const { 
        return orig; 
    }
    // 方向
    vec3 direction() const { 
        return dir; 
    }

    point3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig;
    vec3 dir;
};

#endif