#pragma once

#include <limits>

#include <godot_cpp/core/math_defs.hpp>

#include "stagehand/ecs/components/macros.h"
#include "stagehand/registry.h"

inline constexpr godot::real_t kEnemyDeathInvulnerableHitPoints = std::numeric_limits<godot::real_t>::max();

FLOAT(HitPoints);
FLOAT(HitRadius);
FLOAT(MovementSpeed);
FLOAT(MeleeDamage);
FLOAT(AnimationFrameOffset);
FLOAT(DeathTimer);
FLOAT(HitReactionTimer);
FLOAT(HFlipTimer);
FLOAT(VFlipTimer);
FLOAT(ProjectileHitTimeout);
FLOAT(ShockwaveHitTimeout);
