#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include <tuple>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "helpers.hpp"
#include "log.hpp"

// Scope wrapper for unique smart pointers
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> createScope(Args&& ... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Ref wrapper for shared smart pointers
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> createRef(Args&& ... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#endif
