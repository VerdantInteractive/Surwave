#pragma once

#include <godot_cpp/core/math_defs.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "stagehand/ecs/components/godot_variants.h"
#include "stagehand/registry.h"

struct EnemyBoidMovementSettings {
    godot::real_t player_attraction_weight;
    godot::real_t player_engage_distance;
    godot::real_t neighbor_radius;
    godot::real_t separation_radius;
    godot::real_t max_speed_multiplier;
    godot::real_t max_force;
    godot::real_t grid_cell_size;
    godot::real_t separation_weight;
    godot::real_t kd_tree_rebuild_distance;
    godot::real_t kd_tree_max_stale_frames;
    godot::real_t max_neighbor_sample_count;
    godot::real_t separation_noise_intensity;
};

struct EnemyAnimationSettings {
    godot::real_t animation_interval;
    godot::real_t walk_animation_range;
    godot::real_t death_animation_frame_count;
    godot::real_t up_direction_frame_offset;
    godot::real_t horizontal_flip_cooldown;
    godot::real_t vertical_flip_cooldown;
    godot::real_t nominal_movement_speed;
    godot::real_t animation_offset_fraction_range;
    godot::real_t hit_reaction_duration;
};

struct EnemyTakeDamageSettings {
    godot::real_t projectile_hit_cooldown;
    godot::real_t shockwave_hit_cooldown;
    godot::real_t projectile_damage;
    godot::real_t shockwave_damage;
};

struct PlayerTakeDamageSettings {
    godot::real_t damage_cooldown;
    godot::real_t player_hit_radius;
};

GODOT_VARIANT(ProjectileData, Dictionary);
GODOT_VARIANT(ShockwaveData, Dictionary);

struct EnemyCount {
    size_t value;

    // Allows implicit conversion of this struct to a godot::Variant.
    operator godot::Variant() const { return static_cast<int64_t>(value); }
    operator int64_t() const { return static_cast<int64_t>(value); }
};

inline stagehand::Registry register_game_singleton_components([](flecs::world &world) {
    world.component<EnemyBoidMovementSettings>()
        .member<godot::real_t>("player_attraction_weight")
        .member<godot::real_t>("player_engage_distance")
        .member<godot::real_t>("neighbor_radius")
        .member<godot::real_t>("separation_radius")
        .member<godot::real_t>("max_speed_multiplier")
        .member<godot::real_t>("max_force")
        .member<godot::real_t>("grid_cell_size")
        .member<godot::real_t>("separation_weight")
        .member<godot::real_t>("kd_tree_rebuild_distance")
        .member<godot::real_t>("kd_tree_max_stale_frames")
        .member<godot::real_t>("max_neighbor_sample_count")
        .member<godot::real_t>("separation_noise_intensity")
        .add(flecs::Singleton)
        .set<EnemyBoidMovementSettings>({
            godot::real_t(1.0),   // player_attraction_weight
            godot::real_t(28.0),  // player_engage_distance
            godot::real_t(110.0), // neighbor_radius
            godot::real_t(30.0),  // separation_radius
            godot::real_t(1.1),   // max_speed_multiplier
            godot::real_t(220.0), // max_force
            godot::real_t(96.0),  // grid_cell_size
            godot::real_t(1.0),   // separation_weight
            godot::real_t(35.0),  // kd_tree_rebuild_distance
            godot::real_t(8.0),   // kd_tree_max_stale_frames
            godot::real_t(48.0),  // max_neighbor_sample_count
            godot::real_t(0.05)   // separation_noise_intensity
        });

    world.component<EnemyAnimationSettings>()
        .member<godot::real_t>("animation_interval")
        .member<godot::real_t>("walk_animation_range")
        .member<godot::real_t>("death_animation_frame_count")
        .member<godot::real_t>("up_direction_frame_offset")
        .member<godot::real_t>("horizontal_flip_cooldown")
        .member<godot::real_t>("vertical_flip_cooldown")
        .member<godot::real_t>("nominal_movement_speed")
        .member<godot::real_t>("animation_offset_fraction_range")
        .member<godot::real_t>("hit_reaction_duration")
        .add(flecs::Singleton)
        .set<EnemyAnimationSettings>({
            godot::real_t(0.25), // animation_interval
            godot::real_t(5.0),  // walk_animation_range
            godot::real_t(4.0),  // death_animation_frame_count
            godot::real_t(6.0),  // up_direction_frame_offset
            godot::real_t(0.5),  // horizontal_flip_cooldown
            godot::real_t(0.5),  // vertical_flip_cooldown
            godot::real_t(9.0),  // nominal_movement_speed
            godot::real_t(0.3),  // animation_offset_fraction_range
            godot::real_t(0.1)   // hit_reaction_duration
        });

    world.component<EnemyTakeDamageSettings>()
        .member<godot::real_t>("projectile_hit_cooldown")
        .member<godot::real_t>("shockwave_hit_cooldown")
        .member<godot::real_t>("projectile_damage")
        .member<godot::real_t>("shockwave_damage")
        .add(flecs::Singleton)
        .set<EnemyTakeDamageSettings>({
            godot::real_t(0.2), // projectile_hit_cooldown
            godot::real_t(1.0), // shockwave_hit_cooldown
            godot::real_t(1.0), // projectile_damage
            godot::real_t(1.0)  // shockwave_damage
        });

    world.component<PlayerTakeDamageSettings>()
        .member<godot::real_t>("damage_cooldown")
        .member<godot::real_t>("player_hit_radius")
        .add(flecs::Singleton)
        .set<PlayerTakeDamageSettings>({godot::real_t(0.3), godot::real_t(9.0)});

    world.component<EnemyCount>().member<size_t>("value").add(flecs::Singleton).set<EnemyCount>({0});

    world.component<ProjectileData>().add(flecs::Singleton);
    stagehand::register_component_getter<ProjectileData, godot::Dictionary>("ProjectileData");
    stagehand::register_component_setter<ProjectileData, godot::Dictionary>("ProjectileData");

    world.component<ShockwaveData>().add(flecs::Singleton);
    stagehand::register_component_getter<ShockwaveData, godot::Dictionary>("ShockwaveData");
    stagehand::register_component_setter<ShockwaveData, godot::Dictionary>("ShockwaveData");

    stagehand::get_component_setters()["EnemyTakeDamageSettings"] = [](flecs::world &world, flecs::entity_t entity_id, const godot::Variant &value) {
        if (entity_id != 0 || !godot::Variant::can_convert(value.get_type(), godot::Variant::DICTIONARY)) {
            return;
        }

        const godot::Dictionary damage_settings = static_cast<godot::Dictionary>(value);
        const EnemyTakeDamageSettings *existing_settings = world.try_get<EnemyTakeDamageSettings>();
        EnemyTakeDamageSettings updated_settings = existing_settings ? *existing_settings : EnemyTakeDamageSettings{};

        if (damage_settings.has("projectile_hit_cooldown")) {
            updated_settings.projectile_hit_cooldown =
                static_cast<godot::real_t>(damage_settings.get("projectile_hit_cooldown", updated_settings.projectile_hit_cooldown));
        }
        if (damage_settings.has("shockwave_hit_cooldown")) {
            updated_settings.shockwave_hit_cooldown =
                static_cast<godot::real_t>(damage_settings.get("shockwave_hit_cooldown", updated_settings.shockwave_hit_cooldown));
        }
        if (damage_settings.has("projectile_damage")) {
            updated_settings.projectile_damage = static_cast<godot::real_t>(damage_settings.get("projectile_damage", updated_settings.projectile_damage));
        }
        if (damage_settings.has("shockwave_damage")) {
            updated_settings.shockwave_damage = static_cast<godot::real_t>(damage_settings.get("shockwave_damage", updated_settings.shockwave_damage));
        }

        world.set<EnemyTakeDamageSettings>(updated_settings);
    };

    stagehand::register_component_getter<EnemyCount, int64_t>("EnemyCount");
});
