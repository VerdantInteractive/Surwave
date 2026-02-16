#pragma once

#include "stagehand/registry.h"

#include "components/physics.h"
#include "components/transform.h"

inline stagehand::Registry register_velocity_to_position_system([](flecs::world &world) {
    world.system<Position2D, const Velocity2D>("Velocity to Position")
        .kind(flecs::PostUpdate)
        .each([](flecs::iter &it, size_t i, Position2D &position, const Velocity2D &velocity) { position += velocity * it.delta_time(); });
});
