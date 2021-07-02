QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        chest.cpp \
        console.cpp \
        door.cpp \
        enemy.cpp \
        equipment.cpp \
        game.cpp \
        main.cpp \
        menu.cpp \
        player.cpp \
        room.cpp \
        roomgenerator.cpp \
        tile.cpp \
        worldgrid.cpp

PRECOMPILED_HEADER = pch.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += "C:\SFML-2.5.1\include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    chest.hpp \
    console.hpp \
    door.hpp \
    enemy.hpp \
    equipment.hpp \
    game.hpp \
    menu.hpp \
    player.hpp \
    room.hpp \
    roomgenerator.hpp \
    roomlayout.hpp \
    tile.hpp \
    worldgrid.hpp
