exists($$PWD/conandeploy.py.in) {
    include(buildinfo.pri)
    CHANNEL = Qt$${QT_VERSION}

    !isEmpty(CONAN_INSTALL){
        for (l, CONAN_INSTALL) {
            REQUIRES_TARGET_LIST += \"$${l}@lys/$${CHANNEL}\"
        }
    }

    REQUIRES_TARGET_LIST = $$join(REQUIRES_TARGET_LIST, ",")

        deployconanfile.input = $$PWD/conandeploy.py.in
        deployconanfile.output = $${BUILD_TREE}/_conandeploy_/conanfile.py
        QMAKE_SUBSTITUTES += deployconanfile
        win32 {
            deploydefaultprofile.input = $$PWD/default.in
        } else {
            deploydefaultprofile.input = $$PWD/default_linux.in
        }
        deploydefaultprofile.output = $${BUILD_TREE}/_conandeploy_/default
        QMAKE_SUBSTITUTES += deploydefaultprofile

        conandeploy.target = conandeploy
        conandeploy.commands = conan install $${BUILD_TREE}/_conandeploy_ -pr $${BUILD_TREE}/_conandeploy_/default -if $${BUILD_TREE}/_conandeploy_ -r liyaosong -u
    } else {
        conandeploy.CONFIG += recursive
    }
    QMAKE_EXTRA_TARGETS += conandeploy
exists($${BUILD_TREE}/_conandeploy_/conanbuildinfo.pri){
CONFIG += conan_basic_setup
include($${BUILD_TREE}/_conandeploy_/conanbuildinfo.pri)
}
