#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "src/flecs_registry.h"

#include "src/components/physics.h"
#include "src/components/transform.h"
#include "src/utilities/godot_signal.h"

#include "components/enemy.h"
#include "components/singletons.h"

inline FlecsRegistry register_enemy_death_system([](flecs::world& world) {
    world.system<HitPoints, DeathTimer, MeleeDamage, MovementSpeed, Velocity2D, const EnemyAnimationSettings, const Position2D>("Enemy Death")
        .with(flecs::IsA, world.lookup("Enemy"))
        .kind(flecs::OnValidate)
        .run([](flecs::iter& it) {
        while (it.next()) {
            flecs::field<HitPoints> hit_points = it.field<HitPoints>(0);
            flecs::field<DeathTimer> death_timer = it.field<DeathTimer>(1);
            flecs::field<MeleeDamage> melee_damage = it.field<MeleeDamage>(2);
            flecs::field<MovementSpeed> movement_speed = it.field<MovementSpeed>(3);
            flecs::field<Velocity2D> velocities = it.field<Velocity2D>(4);
            flecs::field<const EnemyAnimationSettings> animation_settings_field = it.field<const EnemyAnimationSettings>(5); // singleton
            flecs::field<const Position2D> positions = it.field<const Position2D>(6);

            const EnemyAnimationSettings* animation_settings = &animation_settings_field[0];
            const godot::real_t death_animation_duration = animation_settings->animation_interval * animation_settings->death_animation_frame_count;
            const godot::real_t invulnerable_hit_points = kEnemyDeathInvulnerableHitPoints;

            for (auto entity_index : it) {
                if (hit_points[entity_index].value > godot::real_t(0.0)) { continue; }

                flecs::entity entity = it.entity(static_cast<std::int32_t>(entity_index));
                godot::Dictionary signal_data;
                const flecs::entity prefab_entity = entity.target(flecs::IsA);
                signal_data["enemy_type"] = godot::String(prefab_entity.name().c_str());
                signal_data["enemy_position"] = positions[entity_index].value;
                emit_godot_signal(it.world(), entity, "enemy_died", signal_data);

                hit_points[entity_index].value = invulnerable_hit_points;
                death_timer[entity_index].value = death_animation_duration;
                melee_damage[entity_index].value = godot::real_t(0.0);
                movement_speed[entity_index].value = godot::real_t(0.0);
                velocities[entity_index].value = godot::Vector2(0.0f, 0.0f);
            }
        }
    });

});
