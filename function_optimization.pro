QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        BoxArea.cpp \
        MethodStatus.cpp \
        NMSDstop.cpp \
        NMStatus.cpp \
        NelderMead.cpp \
        OptimizationMethod.cpp \
        SingletonGenerator.cpp \
        StohIterStop.cpp \
        StohStatus.cpp \
        StohasticOptimization.cpp \
        StopCriterion.cpp \
        function.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    BoxArea.h \
    MethodStatus.h \
    NMSDstop.h \
    NMStatus.h \
    NelderMead.h \
    OptimizationMethod.h \
    SingletonGenerator.h \
    StohIterStop.h \
    StohStatus.h \
    StohasticOptimization.h \
    StopCriterion.h \
    function.h
