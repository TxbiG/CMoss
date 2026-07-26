set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(CMOSS_ENABLE_JOLT_PHYSICS "Build the experimental C++/Jolt physics bindings" OFF)

set(MOSS_ROOT "${REPO_ROOT}/src")

set(MOSS_SOURCES
    ${MOSS_ROOT}/renderer/moss_renderer.c
    ${MOSS_ROOT}/physics/moss_physics.c
    ${MOSS_ROOT}/network/address.c
    ${MOSS_ROOT}/network/callbacks.c
    ${MOSS_ROOT}/network/compress.c
    ${MOSS_ROOT}/network/host.c
    ${MOSS_ROOT}/network/list.c
    ${MOSS_ROOT}/network/packet.c
    ${MOSS_ROOT}/network/peer.c
    ${MOSS_ROOT}/network/protocol.c
)

if(WIN32)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/network/win32.c
        ${MOSS_ROOT}/platform/windows/win32_window.c
        ${MOSS_ROOT}/platform/windows/win32_monitor.c
        ${MOSS_ROOT}/platform/windows/win32_input.c
        ${MOSS_ROOT}/audio/windows/win32_audio.c
        ${MOSS_ROOT}/audio/windows/win32_microphone.c
        ${MOSS_ROOT}/audio/windows/win32_speaker.c
    )
elseif(APPLE)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/network/unix.c
        ${MOSS_ROOT}/audio/mac/mac_audio.c
        ${MOSS_ROOT}/audio/mac/mac_microphone.c
        ${MOSS_ROOT}/audio/mac/mac_speaker.c
    )
elseif(UNIX)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/network/unix.c
        ${MOSS_ROOT}/platform/linux/linux_input.c
        ${MOSS_ROOT}/platform/linux/wl_monitor.c
        ${MOSS_ROOT}/platform/linux/wl_window.c
        ${MOSS_ROOT}/platform/linux/x11_monitor.c
        ${MOSS_ROOT}/platform/linux/x11_window.c
        ${MOSS_ROOT}/audio/linux/alsa_audio.c
        ${MOSS_ROOT}/audio/linux/alsa_microphone.c
        ${MOSS_ROOT}/audio/linux/alsa_speaker.c
    )
endif()

if(ANDROID)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/platform/android/android_window.c
        ${MOSS_ROOT}/platform/android/android_monitor.c
        ${MOSS_ROOT}/platform/android/android_input.c
    )
endif()

if(IOS)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/platform/ios/ios_window.c
        ${MOSS_ROOT}/platform/ios/ios_monitor.c
        ${MOSS_ROOT}/platform/ios/ios_input.c
    )
endif()

if(CMOSS_ENABLE_JOLT_PHYSICS)
    enable_language(CXX)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    list(APPEND MOSS_SOURCES
        ${MOSS_ROOT}/physics/moss_physics.cpp
        ${MOSS_ROOT}/physics/physics_intern.cpp
    )
endif()

add_library(Moss STATIC ${MOSS_SOURCES})
add_library(Moss::Moss ALIAS Moss)

target_include_directories(Moss PUBLIC
    $<BUILD_INTERFACE:${REPO_ROOT}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(Moss PRIVATE /W4)
else()
    target_compile_options(Moss PRIVATE -Wall -Wextra -Wpedantic)
endif()
