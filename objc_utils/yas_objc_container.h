//
//  yas_objc_container.h
//

#pragma once

#include <objc/objc.h>
#include <mutex>
#include "yas_objc_macros.h"

namespace yas {
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

    template <typename T = strong>
    class container {
       public:
        container(id const object = nil);

        ~container() = default;

        container(const container &);
        container(container &&);
        container &operator=(const container &);
        container &operator=(container &&);

        container &operator=(id const object);

        explicit operator bool() const;

        void set_object(id const object);
        id object() const;
        id retained_object() const;
        id autoreleased_object() const;

        container<strong_holder> lock() const;

       private:
        T _holder;
        mutable std::recursive_mutex _mutex;
    };
}
}
