//
//  yas_objc_container.h
//

#pragma once

#include <objc/objc.h>
#include <mutex>
#include "yas_objc_macros.h"

namespace yas {
template <typename T>
using enable_if_id_t = typename std::enable_if_t<std::is_convertible<T, id>::value>;

namespace objc {
    struct strong_holder {
        strong_holder();
        strong_holder(id const object);
        ~strong_holder();
        void set_object(id const object);

        id _object;
    };

    struct weak_holder {
        weak_holder();
        weak_holder(id const object);
        ~weak_holder();
        void set_object(id const object);

        yas_weak_for_variable id _object;
    };

    using strong = strong_holder;
    using weak = weak_holder;

    template <typename C = id, typename T = strong, typename Enable = void>
    class container;

    template <typename C, typename T>
    class container<C, T, enable_if_id_t<C>> {
       public:
        container(C const object = nil);

        ~container() = default;

        container(container const &);
        container(container &&);
        container &operator=(container const &);
        container &operator=(container &&);

        container &operator=(C const object);

        explicit operator bool() const;

        void set_object(C const object);
        C object() const;
        C retained_object() const;
        C autoreleased_object() const;

        container<C, strong, enable_if_id_t<C>> lock() const;

       private:
        T _holder;
        mutable std::recursive_mutex _mutex;
    };
}
template <typename C>
objc::container<C> make_container(C const);
template <typename C>
objc::container<C> make_container(std::function<C(void)> const &func);
template <typename C>
objc::container<C> make_container_move(C const obj);

template <typename C>
objc::container<C, objc::weak> make_weak_container(C const);
}

#include "yas_objc_container_private.h"
