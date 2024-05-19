#pragma once

#include <vector>
#include <string>

#include "entity.hpp"
#include "box2d/box2d.h"

std::vector<Entity> levelLoading(std::string level, b2World & world);