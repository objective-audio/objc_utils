//
//  yas_objc_container_private.h
//

#pragma once

namespace yas {
namespace objc {
    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>>::container(C const object) : _holder(object) {
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>>::container(container const &other) {
        C obj = other.retained_object();
        set_object(obj);
        yas_release(obj);
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>>::container(container &&other) {
        C obj = other.retained_object();
        set_object(obj);
        yas_release(obj);
        other.set_object(nil);
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>> &container<C, T, enable_if_id_t<C>>::operator=(
        container<C, T, enable_if_id_t<C>> const &rhs) {
        C obj = rhs.retained_object();
        set_object(obj);
        yas_release(obj);

        return *this;
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>> &container<C, T, enable_if_id_t<C>>::operator=(
        container<C, T, enable_if_id_t<C>> &&rhs) {
        C obj = rhs.retained_object();
        set_object(obj);
        yas_release(obj);
        rhs.set_object(nil);

        return *this;
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>> &container<C, T, enable_if_id_t<C>>::operator=(C const rhs) {
        set_object(rhs);

        return *this;
    }

    template <typename C, typename T>
    container<C, T, enable_if_id_t<C>>::operator bool() const {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        return !!_holder._object;
    }

    template <typename C, typename T>
    void container<C, T, enable_if_id_t<C>>::set_object(C const object) {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        _holder.set_object(object);
    }

    template <typename C, typename T>
    void container<C, T, enable_if_id_t<C>>::move_object(C const object) {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        _holder.set_object(object);
        yas_release(object);
    }

    template <typename C, typename T>
    C container<C, T, enable_if_id_t<C>>::object() const {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        return _holder._object;
    }

    template <typename C, typename T>
    C container<C, T, enable_if_id_t<C>>::retained_object() const {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        return yas_retain(_holder._object);
    }

    template <typename C, typename T>
    C container<C, T, enable_if_id_t<C>>::autoreleased_object() const {
        std::lock_guard<std::recursive_mutex> lock(_mutex);
        return yas_retain_and_autorelease(_holder._object);
    }

    template <typename C, typename T>
    container<C, strong, enable_if_id_t<C>> container<C, T, enable_if_id_t<C>>::lock() const {
        C obj = retained_object();
        container<C, strong, enable_if_id_t<C>> strong_container(obj);
        yas_release(obj);
        return strong_container;
    }
}

template <typename C>
objc::container<C> make_container(C const obj) {
    return objc::container<C>(obj);
}

template <typename C>
objc::container<C> make_container(std::function<C(void)> const &func) {
    objc::container<C> container;
    @autoreleasepool {
        auto obj = func();
        container.set_object(obj);
    }
    return container;
}

template <typename C>
objc::container<C> make_container_move(C const obj) {
    objc::container<C> container(obj);
    yas_release(obj);
    return container;
}

template <typename C>
objc::container<C, objc::weak> make_weak_container(C const obj) {
    return objc::container<C, objc::weak>(obj);
}
}
