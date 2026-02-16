#pragma once

#include "stagehand/registry.h"

#include "components/singletons.h"

inline stagehand::Registry register_enemy_count_update_system([](flecs::world &world) {
    const flecs::entity enemy_prefab = world.lookup("Enemy");
    const flecs::query<> enemy_instance_query = world.query_builder<>().with(flecs::IsA, enemy_prefab).build();

    world.system<>("Enemy Count Update").kind(flecs::PostUpdate).run([enemy_instance_query](flecs::iter &it) {
        const size_t current_enemy_count = static_cast<size_t>(enemy_instance_query.iter(it).count());
        // https://discord.com/channels/633826290415435777/1455553733978099763/1455637997361041458
        EnemyCount *singleton_component = it.world().try_get_mut<EnemyCount>();
        if (singleton_component == nullptr || singleton_component->value != current_enemy_count) {
            singleton_component->value = current_enemy_count;
            it.world().modified<EnemyCount>();
        }
    });
});
