//
//  yas_objc_container.mm
//

#include <Foundation/Foundation.h>
#include "yas_objc_container.h"
#include "yas_objc_macros.h"

using namespace yas::objc;

strong_holder::strong_holder() : _object(nil) {
}

strong_holder::strong_holder(id const object) : _object(object) {
    yas_retain_or_ignore(object);
}

strong_holder::~strong_holder() {
    yas_release(_object);
    _object = nil;
}

void strong_holder::set_object(id const object) {
    yas_retain_or_ignore(object);
    yas_release(_object);
    _object = object;
}

weak_holder::weak_holder() : _object(nil) {
}

weak_holder::weak_holder(id const object) : _object(object) {
}

weak_holder::~weak_holder() {
    _object = nil;
}

void weak_holder::set_object(id const object) {
    _object = object;
}
