// swift-tools-version: 5.9
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "objc-utils",
    platforms: [.macOS(.v10_15), .iOS(.v13), .macCatalyst(.v13)],
    products: [
        .library(
            name: "objc-utils",
            targets: ["objc-utils"]
        ),
    ],
    targets: [
        .target(
            name: "objc-utils",
            cSettings: [
                .unsafeFlags(["-fno-objc-arc"])
            ]),
        .testTarget(
            name: "objc-utils-tests",
            dependencies: [
                "objc-utils",
            ],
            cSettings: [
                .unsafeFlags(["-fno-objc-arc"])
            ]),
    ],
    cLanguageStandard: .gnu18,
    cxxLanguageStandard: .gnucxx2b
)
