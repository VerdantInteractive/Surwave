#pragma once

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>

#include "src/flecs_registry.h"


struct Velocity2D
{
    godot::Vector2 value;
};

struct Velocity3D
{
    godot::Vector3 value;
};


inline FlecsRegistry register_physics_components([](flecs::world& world) {
    world.component<Velocity2D>()
        .member<godot::Vector2>("value");

    world.component<Velocity3D>()
        .member<godot::Vector3>("value");
});
