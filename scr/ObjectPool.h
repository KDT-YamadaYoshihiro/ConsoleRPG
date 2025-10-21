#pragma once
#include <vector>
#include <memory>
#include <stack>
#include <unordered_map>
#include <cassert>

template <typename T>
class ObjectPool {
    std::unordered_map<int, std::stack<T*>> freeListById;
    std::vector<std::unique_ptr<T>> objects;

public:
    std::shared_ptr<T> Acquire(int id) {
        T* obj = nullptr;

        if (freeListById[id].empty()) {
            objects.emplace_back(std::make_unique<T>());
            obj = objects.back().get();
        }
        else {
            obj = freeListById[id].top();
            freeListById[id].pop();
        }

        // ƒJƒXƒ^ƒ€deleter‚Å•Ô‹p
        return std::shared_ptr<T>(obj, [this, id](T* p) {
            freeListById[id].push(p);
            });
    }
};
