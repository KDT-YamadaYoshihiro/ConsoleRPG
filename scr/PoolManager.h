#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <stack>
#include "Character.h"
#include "ObjectPool.h"

class CharacterPoolManager {
public:
    static CharacterPoolManager& GetInstance() {
        static CharacterPoolManager instance;
        return instance;
    }

    // キャラクターをID指定で取得
    std::shared_ptr<Character> Acquire(int id) {
        auto& pool = pools[id];
        if (pool == nullptr) {
            pool = std::make_unique<ObjectPool<Character>>(5); // 初期5体
        }

        auto obj = pool->Acquire();
        obj->setID(id);
        return obj;
    }

    // キャラクターを返却
    void Release(int id, std::shared_ptr<Character> ch) {
        if (pools.count(id)) {
            pools[id]->Release(ch);
        }
    }

private:
    std::unordered_map<int, std::unique_ptr<ObjectPool<Character>>> pools;
    CharacterPoolManager() = default;
};
#pragma once
