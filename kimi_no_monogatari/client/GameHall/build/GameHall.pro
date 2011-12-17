
ROOT_DIR = ../../..
GAMEHALL_DIR = ..
CLIENT_DIR = $${ROOT_DIR}/client


QMAKE_LIBDIR += $(BOOST_ROOT)/stage/lib

CONFIG += qt

QT += opengl

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

INCLUDEPATH += $${GAMEHALL_DIR}/include
INCLUDEPATH += $(OGRE_INCLUDE)
INCLUDEPATH += $(OGRE_BUILD_INCLUDE)
INCLUDEPATH += $(BOOST_ROOT)
INCLUDEPATH += $(LUA_PATH)/include
INCLUDEPATH += $${GAMEHALL_DIR}/../../common/include
INCLUDEPATH += $${CLIENT_DIR}/include
INCLUDEPATH += $${ROOT_DIR}/dependencies/logging
INCLUDEPATH += $${ROOT_DIR}/dependencies
INCLUDEPATH += $${ROOT_DIR}/common
INCLUDEPATH += $${ROOT_DIR}/common/include
INCLUDEPATH += $${GAMEHALL_DIR}/build

PRECOMPILED_HEADER = pch/pch.h

HEADERS += $${GAMEHALL_DIR}/include/GameHallWindow.h
HEADERS += $${GAMEHALL_DIR}/include/GameHallApplication.h
HEADERS += $${GAMEHALL_DIR}/include/HallLoginState.h
HEADERS += $${GAMEHALL_DIR}/include/HallState.h
HEADERS += $${GAMEHALL_DIR}/include/HallStateManager.h
HEADERS += $${GAMEHALL_DIR}/include/LoginForm.h
HEADERS += $${GAMEHALL_DIR}/include/WidgetListener.h
HEADERS += $${GAMEHALL_DIR}/include/GameHallService.h
HEADERS += $${GAMEHALL_DIR}/include/HallHallState.h
HEADERS += $${GAMEHALL_DIR}/include/HallGameState.h
HEADERS += $${GAMEHALL_DIR}/include/HallWindow.h

SOURCES += $${GAMEHALL_DIR}/src/GameHallWindow.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameHallApplication.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallLoginState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallStateManager.cpp
SOURCES += $${GAMEHALL_DIR}/src/LoginForm.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameHallService.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallHallState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallGameState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallWindow.cpp
SOURCES += $${GAMEHALL_DIR}/src/Sample3DGame.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameGLWidget.cpp
SOURCES += $${GAMEHALL_DIR}/src/main.cpp

SOURCES += $${GAMEHALL_DIR}/src/Logger.cpp



win32:LIBS += $(OGRE_LIB)/OgreMain_d.lib
win32:LIBS += $(OGRE_LIB)/RenderSystem_Direct3D9_d.lib
win32:LIBS += $(OGRE_LIB)/RenderSystem_GL_d.lib
win32:LIBS += $(LUA_PATH)/lua5.1.lib

