QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    loginsystem.cpp \
    main.cpp \
    maindatabase.cpp \
    pulp.cpp \
    pvchat.cpp \
    user.cpp

HEADERS += \
    chat.h \
    loginsystem.h \
    maindatabase.h \
    pulp.h \
    pvchat.h \
    user.h

FORMS += \
    loginsystem.ui \
    pulp.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    elements.qrc

DISTFILES += \
    APproject.pro.user \
    APproject.pro.user.913bdb2 \
    README.md \
    img/3d-fluency-bunch-of-keys.png \
    img/icons8-chat-64.ico \
    img/icons8-login-100.png \
    img/icons8-password-window-66.png \
    img/user.png
