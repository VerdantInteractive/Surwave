#pragma once

#include <cstddef>
#include <cstdint>

#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "stagehand/ecs/components/godot_signal.h"
#include "stagehand/registry.h"

#include "components/enemy.h"
#include "components/player.h"
#include "components/singletons.h"
#include "components/transform.h"

inline stagehand::Registry register_player_take_damage_system([](flecs::world &world) {
    world.system<PlayerDamageCooldown, const PlayerPosition, const PlayerTakeDamageSettings, const Position2D, const MeleeDamage>("Enemy Hit Player")
        .with(flecs::IsA, world.lookup("Enemy"))
        .run([](flecs::iter &it) {
            while (it.next()) {
                flecs::field<PlayerDamageCooldown> player_damage_cooldown = it.field<PlayerDamageCooldown>(0);              // singleton
                flecs::field<const PlayerPosition> player_position = it.field<const PlayerPosition>(1);                     // singleton
                flecs::field<const PlayerTakeDamageSettings> damage_settings = it.field<const PlayerTakeDamageSettings>(2); // singleton
                flecs::field<const Position2D> enemy_positions = it.field<const Position2D>(3);
                flecs::field<const MeleeDamage> melee_damages = it.field<const MeleeDamage>(4);

                const godot::real_t cooldown = godot::Math::max(damage_settings->damage_cooldown, godot::real_t(0.0));
                const bool can_take_damage = cooldown <= godot::real_t(0.0) || player_damage_cooldown->value >= cooldown;
                if (!can_take_damage) {
                    return;
                }

                const godot::real_t player_hit_radius = godot::Math::max(damage_settings->player_hit_radius, godot::real_t(1.0));
                const godot::Vector2 player_position_value = *player_position;

                for (auto entity_index : it) { // https://discord.com/channels/633826290415435777/1455553733978099763/1455637997361041458
                    const godot::Vector2 enemy_position = enemy_positions[entity_index];
                    const godot::Vector2 delta = player_position_value - enemy_position;
                    const godot::real_t distance_squared = delta.length_squared();
                    const godot::real_t contact_radius = player_hit_radius;
                    const godot::real_t contact_radius_squared = contact_radius * contact_radius;
                    if (distance_squared > contact_radius_squared) {
                        continue;
                    }

                    const godot::real_t damage_amount = godot::Math::max(melee_damages[entity_index].value, godot::real_t(0.0));
                    if (damage_amount <= godot::real_t(0.0)) {
                        continue;
                    }

                    flecs::entity damaging_enemy = it.entity(entity_index);
                    godot::Dictionary signal_data;
                    signal_data["damage_amount"] = damage_amount;
                    emit_godot_signal(it.world(), damaging_enemy, "enemy_hit_player", signal_data);

                    player_damage_cooldown->value = godot::real_t(0.0);
                    return;
                }
            }
        });
});
