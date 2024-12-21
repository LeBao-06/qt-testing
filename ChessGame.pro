QT += core gui
QT += multimedia
QT += svg
QT += svgwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/StockfishHandler.cpp \
    src/buttongame.cpp \
    src/chessboard.cpp \
    src/chesspiece.cpp \
    src/chesstile.cpp \
    src/loadgameui.cpp \
    src/main.cpp \
    src/mainmenu.cpp \
    src/settingsMenu.cpp \
    src/soundeffects.cpp \
    src/svgbutton.cpp \
    src/themesSetting.cpp \
    src/view.cpp

HEADERS += \
    header/StockfishHandler.h \
    header/buttongame.h \
    header/chess.hpp \
    header/chessboard.h \
    header/chesspiece.h \
    header/chesstile.h \
    header/loadgameui.h \
    header/mainmenu.h \
    header/settingsMenu.h \
    header/soundeffects.h \
    header/svgbutton.h \
    header/themesSetting.h \
    header/utilities.h \
    header/view.h

# Define Boost root directory

# Specify Boost include and library directories

# Link necessary Boost libraries
# win32:CONFIG(release, debug|release): {
#     LIBS += -llibboost_system-vc143-mt-x64-1_86 -llibboost_filesystem-vc143-mt-x64-1_86 -llibboost_thread-vc143-mt-x64-1_86
# }

# Fallback for debug if debug libraries are missing
# win32:CONFIG(debug, debug|release): {
#     LIBS += -llibboost_system-vc143-mt-x64-1_86 -llibboost_filesystem-vc143-mt-x64-1_86 -llibboost_thread-vc143-mt-x64-1_86
# }

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
