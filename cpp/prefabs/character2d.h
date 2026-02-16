#pragma once

#include <godot_cpp/variant/transform2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "src/flecs_registry.h"
#include "src/components/physics.h"
#include "src/components/transform.h"
#include "src/components/entity_rendering.h"


inline FlecsRegistry register_character2d_prefab([](flecs::world& world) {
    world.prefab("Character2D")
        .set<Velocity2D>({ godot::Vector2(0.0f, 0.0f) })

        .set<Position2D>({ godot::Vector2(0.0f, 0.0f) })
        .set<Rotation2D>({ 0.0f })
        .set<Scale2D>({ godot::Vector2(1.0f, 1.0f) })
        .set<godot::Transform2D>(godot::Transform2D())

        .set<RenderingCustomData>({ 0.0f, 0.0f, 0.0f, 0.0f });
});
