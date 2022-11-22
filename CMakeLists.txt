cmake_minimum_required(VERSION 3.8)

project(LittleEngine)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)
set(DLC_DIR ${PROJECT_SOURCE_DIR}/src/DLC/)
set(SHADER_DIR ${PROJECT_SOURCE_DIR}/src/Shaders/)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
set(RUNTIME_DIR ${PROJECT_SOURCE_DIR}/runtime/)


set(SRC_DLC
    ${INCLUDE_DIR}glad4.6/src/glad.c
    ${DLC_DIR}stb_image.h
    ${DLC_DIR}stb_image.cpp
	${DLC_DIR}mesh.h
    ${DLC_DIR}model.h
    ${DLC_DIR}model.cpp
    ${DLC_DIR}Camera.h
    ${DLC_DIR}Pnt3f.h
    ${DLC_DIR}Pnt3f.cpp
    ${DLC_DIR}Light.h
    ${DLC_DIR}Light.cpp)

set(SRC_SHADER
    ${SHADER_DIR}Shader.h
    ${SHADER_DIR}Shader.cpp
    ${SHADER_DIR}ModelShader.h
	${SHADER_DIR}LightShader.h
	${SHADER_DIR}LightShader.cpp
	${SHADER_DIR}FontShader.h
	${SHADER_DIR}ImageShader.h
	${SHADER_DIR}ParticleShader.h
	${SHADER_DIR}SkyBoxShader.h
	${SHADER_DIR}SkyBoxShader.cpp
	${SHADER_DIR}Simple3DShader.h)

include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}glad4.6/include/)
include_directories(${INCLUDE_DIR}glm-0.9.8.5/glm/)

add_Definitions("-D_XKEYCHECK_H")

add_executable(LittleEngine

    ${SRC_DIR}main.cpp

    ${SRC_DIR}GameWindow.h
    ${SRC_DIR}GameWindow.cpp
    ${SRC_DIR}GameManager.h
    ${SRC_DIR}GameManager.cpp
	
	${SRC_DIR}Scene.h
    ${SRC_DIR}Scene.cpp
	${SRC_DIR}TestScene.h
    ${SRC_DIR}TestScene.cpp
	
	${SRC_DIR}GameObject.h
	${SRC_DIR}GameObject.cpp
	${SRC_DIR}Component.h
	${SRC_DIR}Component.cpp
	${SRC_DIR}RenderComponent.h
	${SRC_DIR}RenderComponent.cpp
	
	${SRC_DIR}Animator.h
    ${SRC_DIR}Animator.cpp
	${SRC_DIR}Animation.h
    ${SRC_DIR}Animation.cpp
    ${SRC_DIR}TestAnimation.h
	
	${SRC_DIR}UI.h
    ${SRC_DIR}UI.cpp
	${SRC_DIR}TextBox.h
    ${SRC_DIR}TextBox.cpp
	${SRC_DIR}ImageBox.h
    ${SRC_DIR}ImageBox.cpp
	
	${SRC_DIR}ParticleSystem.h
    ${SRC_DIR}ParticleSystem.cpp
	
    ${SRC_DLC}
    ${SRC_SHADER}
	${MMD_FORMAT}
)

source_group("DLC" FILES ${SRC_DLC})
source_group("Shaders" FILES ${SRC_SHADER})
source_group("MMDFormat" FILES ${MMD_FORMAT})

target_link_libraries(LittleEngine 
    debug ${LIB_DIR}Debug/fltk_formsd.lib      optimized ${LIB_DIR}Release/fltk_forms.lib
    debug ${LIB_DIR}Debug/fltk_gld.lib         optimized ${LIB_DIR}Release/fltk_gl.lib
    debug ${LIB_DIR}Debug/fltk_imagesd.lib     optimized ${LIB_DIR}Release/fltk_images.lib
    debug ${LIB_DIR}Debug/fltk_jpegd.lib       optimized ${LIB_DIR}Release/fltk_jpeg.lib
    debug ${LIB_DIR}Debug/fltk_pngd.lib        optimized ${LIB_DIR}Release/fltk_png.lib
    debug ${LIB_DIR}Debug/fltk_zd.lib          optimized ${LIB_DIR}Release/fltk_z.lib
    debug ${LIB_DIR}Debug/fltkd.lib            optimized ${LIB_DIR}Release/fltk.lib)

target_link_libraries(LittleEngine
    ${LIB_DIR}OpenGL32.lib
    ${LIB_DIR}OpenAL32.lib
    ${LIB_DIR}glu32.lib
    ${LIB_DIR}alut.lib
    ${LIB_DIR}alut_static.lib
    ${LIB_DIR}assimp/assimp-vc142-mtd.lib
	${LIB_DIR}freetype.lib
	${LIB_DIR}unicode/icudt.lib
	${LIB_DIR}unicode/icuin.lib
	${LIB_DIR}unicode/icuio.lib
	${LIB_DIR}unicode/icutest.lib
	${LIB_DIR}unicode/icutu.lib
	${LIB_DIR}unicode/icuuc.lib)

target_link_libraries(LittleEngine)

add_custom_command(
    TARGET LittleEngine
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_directory ${RUNTIME_DIR} $<TARGET_FILE_DIR:LittleEngine>
)
set_property(TARGET LittleEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:LittleEngine>)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LittleEngine)