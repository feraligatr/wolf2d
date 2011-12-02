
ROOT_DIR = ..

CONFIG += qt

QT += opengl

INCLUDEPATH += $${ROOT_DIR}/include
INCLUDEPATH += $${ROOT_DIR}/include
INCLUDEPATH += F:/3d/ogre_src_v1-7-3/OgreMain/include
INCLUDEPATH += $${ROOT_DIR}/../../common/include

PRECOMPILED_HEADER = ../../../include/pch.h

HEADERS += $${ROOT_DIR}/include/GameHallWindow.h
HEADERS += $${ROOT_DIR}/include/GameHallApplication.h
HEADERS += $${ROOT_DIR}/include/HallLoginState.h
HEADERS += $${ROOT_DIR}/include/HallState.h
HEADERS += $${ROOT_DIR}/include/HallStateManager.h
HEADERS += $${ROOT_DIR}/include/LoginForm.h
HEADERS += $${ROOT_DIR}/include/Status.h
HEADERS += $${ROOT_DIR}/include/WidgetListener.h
HEADERS += $${ROOT_DIR}/include/GameHallService.h
HEADERS += $${ROOT_DIR}/include/HallHallState.h
HEADERS += $${ROOT_DIR}/include/HallGameState.h
HEADERS += $${ROOT_DIR}/include/HallWindow.h

SOURCES += $${ROOT_DIR}/src/GameHallWindow.cpp
SOURCES += $${ROOT_DIR}/src/GameHallApplication.cpp
SOURCES += $${ROOT_DIR}/src/HallLoginState.cpp
SOURCES += $${ROOT_DIR}/src/HallStateManager.cpp
SOURCES += $${ROOT_DIR}/src/LoginForm.cpp
SOURCES += $${ROOT_DIR}/src/GameHallService.cpp
SOURCES += $${ROOT_DIR}/src/HallHallState.cpp
SOURCES += $${ROOT_DIR}/src/HallGameState.cpp
SOURCES += $${ROOT_DIR}/src/HallWindow.cpp
SOURCES += $${ROOT_DIR}/src/Sample3DGame.cpp
SOURCES += $${ROOT_DIR}/src/GameGLWidget.cpp
SOURCES += $${ROOT_DIR}/src/main.cpp

win32:LIBS += F:/3d/ogre_v1-7-3-build/lib/Debug/OgreMain_d.lib
win32:LIBS += F:/3d/ogre_v1-7-3-build/lib/Debug/RenderSystem_Direct3D9_d.lib
win32:LIBS += F:/3d/ogre_v1-7-3-build/lib/Debug/RenderSystem_GL_d.lib

