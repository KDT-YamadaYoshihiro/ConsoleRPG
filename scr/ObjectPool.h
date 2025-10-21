#pragma once
#include <vector>
#include <memory>
#include <stack>



template<typename T>
class ObjectPool {
private:
    std::vector<std::shared_ptr<T>> objects;
    std::stack<std::shared_ptr<T>> freeStack;

public:
    ObjectPool(size_t initCount = 10) {
        for (size_t i = 0; i < initCount; ++i) {
            auto obj = std::make_shared<T>();
            objects.push_back(obj);
            freeStack.push(obj);
        }
    }

    // オブジェクト取得
    std::shared_ptr<T> Acquire() {
        if (freeStack.empty()) {
            auto obj = std::make_shared<T>();
            objects.push_back(obj);
            return obj;
        }
        auto obj = freeStack.top();
        freeStack.pop();
        return obj;
    }

    // オブジェクト返却
    void Release(std::shared_ptr<T> obj) {
        freeStack.push(obj);
    }

    size_t Count() const { return objects.size(); }
};
