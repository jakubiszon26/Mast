QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apt_preferences.cpp \
    bootloader.cpp \
    hardware_info.cpp \
    hostname.cpp \
    main.cpp \
    mastwindow.cpp \
    security.cpp \
    services_manager.cpp \
    system_info_form.cpp

HEADERS += \
    apt_preferences.h \
    bootloader.h \
    hardware_info.h \
    hostname.h \
    mastwindow.h \
    security.h \
    services_manager.h \
    system_info_form.h

FORMS += \
    apt_preferences.ui \
    bootloader.ui \
    hardware_info.ui \
    hostname.ui \
    mastwindow.ui \
    security.ui \
    services_manager.ui \
    system_info_form.ui

TRANSLATIONS += \
    Mast_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
