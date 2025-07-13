#pragma once

#include <memory>
#include <vector>

template<typename T, typename Func>
bool CheckCollision(const std::vector<std::shared_ptr<T>>& list, Func condition) {
    for (const auto& item : list) {
        if (condition(*item)) return true;
    }
    return false;
}