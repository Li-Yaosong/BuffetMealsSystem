INCLUDED_BUILDINFO = 1
isEmpty(COMPILER) {
    msvc {
        COMPILER=Visual Studio
        COMPILER_VERSION = $$MSVC_VER
        COMPILER_VERSION = $$section(COMPILER_VERSION, ., 0, 0)
    }
    mingw {
        COMPILER=MinGW_$${QT_ARCH}
        COMPILER_VERSION = $${QT_GCC_MAJOR_VERSION}.$${QT_GCC_MINOR_VERSION}.$${QT_GCC_PATCH_VERSION}
    }
    clang {
       COMPILER=clang
       COMPILER_VERSION = $${QMAKE_CLANG_MAJOR_VERSION}.$${QMAKE_CLANG_MINOR_VERSION}
    }else:gcc:!clang {
       COMPILER=gcc
       COMPILER_VERSION = $${QT_GCC_MAJOR_VERSION}.$${QT_GCC_MINOR_VERSION}
    }
}
BUILD_TYPE=Release
CONFIG(debug, debug|release) {
    BUILD_TYPE=Debug
}

BUILD_ARCH = $$QT_ARCH
contains(QT_ARCH, i386) {
    BUILD_ARCH = x86
}

contains(QT_ARCH, arm64) {
    BUILD_ARCH = armv8
}

BUILD_OS=Linux
win32: BUILD_OS=Windows
