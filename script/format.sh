#!/bin/sh

export PATH=$PATH:/opt/homebrew/bin
clang-format -i -style=file `find ../objc_utils ../objc_utils_test/objc_utils_test_common ../objc_utils_mac_tests/objc_utils_mac_tests ../objc_utils_ios_tests/objc_utils_ios_tests -type f \( -name *.h -o -name *.cpp -o -name *.hpp -o -name *.m -o -name *.mm \)`
