#pragma once
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>
#include "PoolHandle.h"

template<typename T>
class ObjectPool {
	// プール内のオブジェクトと空きオブジェクトの管理
    std::vector<std::shared_ptr<T>> objects_;
    std::stack<std::shared_ptr<T>> free_;

public:

	// コンストラクタ
	// 初期化
    ObjectPool(size_t initialCount = 10) {
        for (size_t i = 0; i < initialCount; i++) {
            auto obj = std::make_shared<T>();
            objects_.push_back(obj);
            free_.push(obj);
        }
    }

	// オブジェクトの取得
    PoolHandle<T> Acquire() {
		// 空きオブジェクトがない場合、新たにオブジェクトを追加
        if (free_.empty()) {
			// 既存のオブジェクト数分を追加
            size_t addCount = std::max<size_t>(1, objects_.size());
			// 追加
            for (size_t i = 0; i < addCount; i++) {
                auto obj = std::make_shared<T>();
                objects_.push_back(obj);
                free_.push(obj);
            }
        }
		// 空きオブジェクトを返す
        auto obj = free_.top();
        free_.pop();

        return PoolHandle<T>(obj, this);
    }

	// オブジェクトの解放
    void Release(std::shared_ptr<T> obj) {
        free_.push(obj);
    }
};
