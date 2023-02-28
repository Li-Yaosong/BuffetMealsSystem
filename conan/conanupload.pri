DATA_PATH = $$BUILD_TREE/$${LIB_NAME}/

exists($$PWD/conanfile.py.in): exists($$PWD/default.in) {
    include($$PWD/buildinfo.pri)

    SHARED_OR_STATIC = True
    static: SHARED_OR_STATIC = False
    CHANNEL = Qt$$QT_VERSION
    CONFIG(debug) {
       TARGET = bmsd
       install_lib.files += $$OUT_PWD/debug/$${TARGET}.lib
       install_bin.files += $$OUT_PWD/debug/$${TARGET}.dll
       message($$install_lib.files)
    }
    else {
       TARGET = bms
       install_lib.files += $$OUT_PWD/release/$${TARGET}.lib
       install_bin.files += $$OUT_PWD/release/$${TARGET}.dll
       message($$install_lib.files)
    }
    no_conan_upload {
        conanupload.CONFIG += recursive
        QMAKE_EXTRA_TARGETS += conanupload
    } else {
        install_headers.path = $${DATA_PATH}include
        install_lib.path = $${DATA_PATH}lib
        install_bin.path = $${DATA_PATH}bin

        conanfile.input = $$PWD/conanfile.py.in
        defaultprofile.input = $$PWD/default.in

        conanfile.output = $${DATA_PATH}/conanfile.py
        defaultprofile.output = $${DATA_PATH}/default


        QMAKE_SUBSTITUTES += conanfile defaultprofile
        conan.files += $${DATA_PATH}conanfile.py
        conan.CONFIG += no_check_exist
        conan.path = $$BUILD_TREE

        profile.files += $${DATA_PATH}default
        profile.CONFIG += no_check_exist
        profile.path = $$BUILD_TREE

        INSTALLS += conan profile
        INSTALLS += install_headers install_lib install_bin

        conanupload.target = conanupload
        conanupload.depends = install
        conanupload.commands = conan export-pkg -pf $$DATA_PATH -pr $$BUILD_TREE/default -f $$BUILD_TREE && conan upload $${LIB_NAME}/$$LIB_VERSION@lys/$$CHANNEL -q \"os=$$BUILD_OS AND compiler=\\\"$$COMPILER\\\" AND compiler.version=$$COMPILER_VERSION AND build_type=$$BUILD_TYPE\" -r liyaosong -c --force
        QMAKE_EXTRA_TARGETS += conanupload
    }
}
