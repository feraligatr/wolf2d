
ROOT_DIR = ../../..
GAMEHALL_DIR = ..
CLIENT_DIR = $${ROOT_DIR}/client

WOLF_GAME_DIR = $${CLIENT_DIR}/Game/wolf
PHYSICS_DIR = $${CLIENT_DIR}/Game/physics
RENDERER_DIR = $${CLIENT_DIR}/Game/renderer

QMAKE_LIBDIR += $(BOOST_ROOT)/stage/lib

CONFIG += qt

QT += opengl

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

DEFINES += _FAKE_

INCLUDEPATH += $${GAMEHALL_DIR}/include
INCLUDEPATH += $(OGRE_INCLUDE)
INCLUDEPATH += $(OGRE_BUILD_INCLUDE)
INCLUDEPATH += $(BOOST_ROOT)
INCLUDEPATH += $(LUA_PATH)/include
INCLUDEPATH += $${GAMEHALL_DIR}/../../common/include
INCLUDEPATH += $${ROOT_DIR}/dependencies/logging
INCLUDEPATH += $${ROOT_DIR}/dependencies
INCLUDEPATH += $${ROOT_DIR}/common
INCLUDEPATH += $${ROOT_DIR}/common/include
INCLUDEPATH += $${GAMEHALL_DIR}/build
INCLUDEPATH += $${CLIENT_DIR}/include
INCLUDEPATH += $${CLIENT_DIR}/Game/Renderer
INCLUDEPATH += $${CLIENT_DIR}/Game
INCLUDEPATH += $${CLIENT_DIR}
INCLUDEPATH += $(BULLET_ROOT)/src
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
HEADERS += $${GAMEHALL_DIR}/include/GameGLWidget.h

HEADERS += $${CLIENT_DIR}/include/Client.h
HEADERS += $${CLIENT_DIR}/include/Connection.h
HEADERS += $${CLIENT_DIR}/include/ConnectionManager.h

HEADERS += $${ROOT_DIR}/common/include/common.h
HEADERS += $${ROOT_DIR}/common/include/Logger.h
HEADERS += $${ROOT_DIR}/common/include/trStream.h
HEADERS += $${ROOT_DIR}/common/include/trFStream.h

HEADERS += $${PHYSICS_DIR}/trCollisionObject.h
HEADERS += $${PHYSICS_DIR}/trCollisionShape.h
HEADERS += $${PHYSICS_DIR}/trCollisionWorld.h
HEADERS += $${PHYSICS_DIR}/trPhysicsWorld.h
HEADERS += $${PHYSICS_DIR}/trRigidBody.h

SOURCES += $${GAMEHALL_DIR}/src/GameHallWindow.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameHallApplication.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallLoginState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallStateManager.cpp
SOURCES += $${GAMEHALL_DIR}/src/LoginForm.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameHallService.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallHallState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallGameState.cpp
SOURCES += $${GAMEHALL_DIR}/src/HallWindow.cpp
SOURCES += $${GAMEHALL_DIR}/src/GameGLWidget.cpp
SOURCES += $${GAMEHALL_DIR}/src/main.cpp
SOURCES += $${GAMEHALL_DIR}/src/Logger.cpp

SOURCES += $${PHYSICS_DIR}/trCollisionObject.cpp
SOURCES += $${PHYSICS_DIR}/trCollisionShape.cpp
SOURCES += $${PHYSICS_DIR}/trCollisionWorld.cpp
SOURCES += $${PHYSICS_DIR}/trPhysicsWorld.cpp
SOURCES += $${PHYSICS_DIR}/trRigidBody.cpp

SOURCES += $${CLIENT_DIR}/src/Connection.cpp
SOURCES += $${CLIENT_DIR}/src/SimpleClient.cpp
SOURCES += $${CLIENT_DIR}/GameHall/src/AsioConnectionManager.cpp

SOURCES += $${RENDERER_DIR}/OgreGraphicsWorld.cpp
SOURCES += $${RENDERER_DIR}/OgreRenderContext.cpp
SOURCES += $${RENDERER_DIR}/OgreGWEntity.cpp
SOURCES += $${RENDERER_DIR}/OgreGWCamera.cpp

SOURCES += $${WOLF_GAME_DIR}/WolfGame.cpp
SOURCES += $${WOLF_GAME_DIR}/GameObject.cpp
SOURCES += $${WOLF_GAME_DIR}/WolfGameObject.cpp


SOURCES += $${ROOT_DIR}/common/msg/Message.cpp
SOURCES += $${ROOT_DIR}/common/msg/MessageManager.cpp
SOURCES += $${ROOT_DIR}/common/msg/MessageParser.cpp
SOURCES += $${ROOT_DIR}/common/msg/MessageParsers.cpp

SOURCES += $${ROOT_DIR}/common/src/Random.cpp
SOURCES += $${ROOT_DIR}/common/src/Session.cpp
SOURCES += $${ROOT_DIR}/common/src/SessionManager.cpp
SOURCES += $${ROOT_DIR}/common/src/trFStream.cpp

SOURCES += $${ROOT_DIR}/common/utils/RandomUtil.cpp

win32:LIBS += $(OGRE_LIB)/OgreMain_d.lib
win32:LIBS += $(OGRE_LIB)/RenderSystem_GL_d.lib
win32:LIBS += $(OGRE_LIB)/Plugin_ParticleFX_d.lib
win32:LIBS += $(OGRE_LIB)/Plugin_BSPSceneManager_d.lib
win32:LIBS += $(OGRE_LIB)/Plugin_CgProgramManager_d.lib
win32:LIBS += $(OGRE_LIB)/Plugin_PCZSceneManager_d.lib
win32:LIBS += $(OGRE_LIB)/Plugin_OctreeSceneManager_d.lib
win32:LIBS += $(OGRE_LIB)/RenderSystem_GL_d.lib
win32:LIBS += $(BULLET_ROOT)/lib/LinearMath_debug.lib
win32:LIBS += $(BULLET_ROOT)/lib/BulletCollision_debug.lib
win32:LIBS += $(BULLET_ROOT)/lib/BulletDynamics_debug.lib
win32:LIBS += $(LUA_PATH)/lua5.1.lib

