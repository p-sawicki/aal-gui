QT       += core gui
QT  += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aal/bf/bf.cpp \
    aal/dp/dp.cpp \
    aal/gen/gen.cpp \
    aal/graph/graph.cpp \
    aal/utils/utils.cpp \
    brickinfodialog.cpp \
    brickstablemodel.cpp \
    generatebricksdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    testdialog.cpp \
    testrunner.cpp

HEADERS += \
    aal/inc/bf.h \
    aal/inc/brick.h \
    aal/inc/dp.h \
    aal/inc/gen.h \
    aal/inc/graph.h \
    aal/inc/utils.h \
    brickinfodialog.h \
    brickstablemodel.h \
    generatebricksdialog.h \
    mainwindow.h \
    testdialog.h \
    testrunner.h

FORMS += \
    brickinfodialog.ui \
    generatebricksdialog.ui \
    mainwindow.ui \
    testdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    loader.qrc
