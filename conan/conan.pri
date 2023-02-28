isEmpty(BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$clean_path($$PWD/../)),,
    BUILD_TREE = $$clean_path($$OUT_PWD)
    BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

!isEmpty(CONAN_INSTALL) {
    include(conandeploy.pri)
    CONFIG(debug) {
        copy_files.files = $$CONAN_BINDIRS/bmsd.dll
        copy_files.path = $$OUT_PWD/debug
    }
    else {
        copy_files.files = $$CONAN_BINDIRS/bms.dll
        copy_files.path = $$OUT_PWD/release
    }
    COPIES += copy_files
}

!isEmpty(LIB_NAME) {
    include(conanupload.pri)
}
