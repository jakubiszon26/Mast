QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apt_preferences.cpp \
    main.cpp \
    mastwindow.cpp \
    system_info_form.cpp

HEADERS += \
    apt_preferences.h \
    mastwindow.h \
    system_info_form.h

FORMS += \
    apt_preferences.ui \
    mastwindow.ui \
    system_info_form.ui

TRANSLATIONS += \
    Mast_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc