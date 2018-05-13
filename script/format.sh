#!/bin/sh

clang-format -i -style=file `find ../objc_utils ../objc_utils_test/objc_utils_test_common ../objc_utils_test/objc_utils_test_ios_non_arc ../objc_utils_test/objc_utils_test_non_arc -type f \( -name *.h -o -name *.cpp -o -name *.hpp -o -name *.m -o -name *.mm \)`
