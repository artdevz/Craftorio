#pragma once
#include <functional>
#include <vector>
#include <memory>

template<typename T>
bool CheckCollision(const std::vector<std::shared_ptr<T>>& list, std::function<bool(const T&)> condition) {
    for (const auto& item : list) {
        if (condition(*item)) return true;
    }
    return false;
}