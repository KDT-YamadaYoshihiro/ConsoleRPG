#pragma once
#include <memory>


template<typename T>
class ObjectPool;

template <typename T>
class PoolHandle {
    std::shared_ptr<T> obj_;        // 共有ポインタで扱う
    ObjectPool<T>* pool_ = nullptr; // 所属プール

    friend class ObjectPool<T>;

    explicit PoolHandle(std::shared_ptr<T> obj, ObjectPool<T>* pool)
        : obj_(obj), pool_(pool) {
    }

public:
    // コピー禁止
    PoolHandle(const PoolHandle&) = delete;

    // ムーブ可能
    PoolHandle(PoolHandle&& other) noexcept
        : obj_(std::move(other.obj_)), pool_(other.pool_) {
        other.pool_ = nullptr;
    }

    // デストラクタで自動返却
    ~PoolHandle() {
        if (obj_ && pool_) {
            pool_->Release(obj_);
        }
    }

    // アクセス演算子
    T* operator->() { return obj_.get(); }
    T& operator*() { return *obj_; }

    // 明示的に所有を解除（再利用時など）
    std::shared_ptr<T> Detach() {
        auto temp = obj_;
        obj_.reset();
        pool_ = nullptr;
        return temp;
    }
};
