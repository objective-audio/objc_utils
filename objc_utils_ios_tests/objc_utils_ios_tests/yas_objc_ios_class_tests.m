//
//  yas_objc_ios_class_tests.m
//

#import <XCTest/XCTest.h>
#import <objc_utils/objc_utils.h>

@interface yas_objc_ios_class_tests : XCTestCase

@end

@implementation yas_objc_ios_class_tests

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

- (void)test_class {
    XCTAssertEqualObjects([yas_objc_view class], [UIView class]);
    XCTAssertEqualObjects([yas_objc_view_controller class], [UIViewController class]);
    XCTAssertEqualObjects([yas_objc_color class], [UIColor class]);
}

@end
