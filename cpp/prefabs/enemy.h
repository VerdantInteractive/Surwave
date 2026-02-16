#pragma once

#include "src/flecs_registry.h"

#include "components/enemy.h"


inline FlecsRegistry register_enemy_prefab([](flecs::world& world) {
    world.prefab("Enemy")
        .is_a(world.lookup("Character2D"))
        // https://discord.com/channels/633826290415435777/1455553733978099763/1455638300051116145
        .set<HitPoints>({ godot::real_t(100.0) })
        .set<HitRadius>({ godot::real_t(14.0) })
        .set<MeleeDamage>({ godot::real_t(10.0) })
        .set<MovementSpeed>({ godot::real_t(50.0) })
        .set<AnimationFrameOffset>({ godot::real_t(0.0) })
        .set<DeathTimer>({ godot::real_t(0.0) })
        .set<HitReactionTimer>({ godot::real_t(0.0) })
        .set<HFlipTimer>({ godot::real_t(0.5) })
        .set<VFlipTimer>({ godot::real_t(0.5) })
        .set<ProjectileHitTimeout>({ godot::real_t(0.0) })
        .set<ShockwaveHitTimeout>({ godot::real_t(0.0) });
});
