set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -DGLM_SWIZZLE -DGLM_FORCE_RADIANS")

find_package(SDL REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(OggVorbis REQUIRED)
find_package(OpenAL REQUIRED)
find_package(PNG REQUIRED)

include_directories(
	${SDL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
	${GLM_INCLUDE_DIRS}
	${VORBIS_INCLUDE_DIR}
	${OGG_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${PNG_INCLUDE_DIRS})

link_directories(${CMAKE_BINARY_DIR}/ggl)

set(INTRO_SOURCES
	util.cc
	programs.cc
	logo.cc
	blob.cc
	main.cc)

add_executable(intro ${INTRO_SOURCES})

target_link_libraries(
	intro
	ggl
	${SDL_LIBRARY}
	${GLEW_LIBRARY}
	${OPENGL_LIBRARIES}
	${VORBIS_LIBRARY}
	${OGG_LIBRARY}
	${VORBISFILE_LIBRARY}
	${OPENAL_LIBRARY}
	${PNG_LIBRARIES})
