CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(space-shooter)

SET(SRC
	sources/main.cpp
	sources/Game.cpp
	sources/Scenenode.cpp
	sources/Entity.cpp
	sources/Aircraft.cpp
	sources/World.cpp
	sources/SpriteNode.cpp
	sources/CommandQueue.cpp
	sources/StateStack.cpp
	sources/State.cpp
	sources/GameState.cpp
	sources/MenuState.cpp
	sources/PauseState.cpp
	sources/TitleState.cpp
	sources/TextNode.cpp
	sources/Projectile.cpp
	)

SET(HDRS
	includes/Game.hpp
	includes/ResourceHolder.hpp
	includes/ResourceHolder.inl
	includes/SceneNode.hpp
	includes/Entity.hpp
	includes/Aircraft.hpp
	includes/World.hpp
	includes/SpriteNode.hpp
	includes/Command.hpp
	includes/CommandQueue.hpp
	includes/Category.hpp
	includes/StateStack.hpp
	includes/State.hpp
	includes/GameState.hpp
	includes/MenuState.hpp
	includes/PauseState.hpp
	includes/TitleState.hpp
	includes/ResourceIDs.hpp
	includes/TextNode.hpp
	includes/Projectile.hpp
	)

SET(SFML_STATIC_LIBRARIES TRUE BOOL "Use static SFML librares")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")
SET(SFML_ROOT "E:/SFML-2.3.1" CACHE PATH "SFML top-level directory")

FIND_PACKAGE(SFML 2 COMPONENTS audio graphics window system network)

IF(SFML_FOUND)
	INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
ELSE()
	SET(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	MESSAGE("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	MESSAGE("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/includes)

ADD_DEFINITIONS(/W3)
ADD_EXECUTABLE(space-shooter ${SRC} ${HDRS})

IF(SFML_STATIC_LIBRARIES)
	SET_TARGET_PROPERTIES(space-shooter PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
ENDIF()

SET_TARGET_PROPERTIES(space-shooter PROPERTIES OUTPUT_NAME "Space-Shooter")

TARGET_LINK_LIBRARIES(
	space-shooter
	${SFML_LIBRARIES}
	gdi32
	${GLEW_LIBRARY}
	${JPEG_LIBRARY}
	${FREETYPE_LIBRARY}
	opengl32
	winmm
	)

GET_TARGET_PROPERTY(BIN_LOCATION space-shooter LOCATION)

ADD_CUSTOM_COMMAND(
	TARGET space-shooter
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${BIN_LOCATION} ${PROJECT_SOURCE_DIR}/bin
	)
