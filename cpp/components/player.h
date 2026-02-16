#pragma once

#include <godot_cpp/variant/vector2.hpp>

#include "stagehand/ecs/components/godot_variants.h"
#include "stagehand/ecs/components/macros.h"
#include "stagehand/registry.h"

GODOT_VARIANT(PlayerPosition, Vector2, 0.0f, 0.0f);

inline auto register_player_position_singleton =
    register_PlayerPosition_variant.then([](auto c) { c.add(flecs::Singleton).template set<PlayerPosition>({Vector2(0.0f, 0.0f)}); });

FLOAT(PlayerDamageCooldown);

inline auto register_player_damage_cooldown_singleton =
    register_PlayerDamageCooldown_float.then([](auto c) { c.add(flecs::Singleton).template set<PlayerDamageCooldown>({0.0f}); });
