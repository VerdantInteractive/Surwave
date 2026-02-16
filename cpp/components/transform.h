#pragma once

#include <godot_cpp/core/math_defs.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "stagehand/ecs/components/godot_variants.h"
#include "stagehand/ecs/components/macros.h"
#include "stagehand/registry.h"

GODOT_VARIANT(Position2D, Vector2, 0.0f, 0.0f);
GODOT_VARIANT(Scale2D, Vector2, 1.0f, 1.0f);
FLOAT(Rotation2D, 0.0f);
