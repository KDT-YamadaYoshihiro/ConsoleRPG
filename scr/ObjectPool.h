#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include "PoolHandle.h"

template<typename T>
class ObjectPool {
    std::vector<std::shared_ptr<T>> objects_;
    std::stack<std::shared_ptr<T>> free_;

public:
    ObjectPool(size_t initialCount = 10) {
        for (size_t i = 0; i < initialCount; i++) {
            auto obj = std::make_shared<T>();
            objects_.push_back(obj);
            free_.push(obj);
        }
    }

    PoolHandle<T> Acquire() {
        if (free_.empty()) {
            size_t addCount = std::max<size_t>(1, objects_.size());
            for (size_t i = 0; i < addCount; i++) {
                auto obj = std::make_shared<T>();
                objects_.push_back(obj);
                free_.push(obj);
            }
        }
        auto obj = free_.top();
        free_.pop();
        return PoolHandle<T>(obj, this);
    }

    void Release(std::shared_ptr<T> obj) {
        free_.push(obj);
    }
};
