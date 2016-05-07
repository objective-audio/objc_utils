//
//  yas_objc_weak.h
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface YASUnownedObject <T> : NSObject

- (void)setObject:(nullable T)object;
- (nullable T)object;
- (nullable T)retainedObject;
- (nullable T)autoreleasedObject;

@end

NS_ASSUME_NONNULL_END
