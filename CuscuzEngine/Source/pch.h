#pragma once

#include <iostream>
#include <memory>
#include <functional>

#include <string>
#include <sstream>

#include <vector>
#include <unordered_map>

#include <filesystem>

#define BIT(x) (1 << x)

#define BIND_FUNCTION(Instance, Func) std::bind(&Func, Instance, std::placeholders::_1)