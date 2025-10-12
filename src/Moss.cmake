# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Root
set(MOSS_ROOT ${REPO_ROOT}/src)


# Define library sources
set(MOSS_SOURCES
    # Platform
    ${MOSS_ROOT}/moss_stdinc.c
    ${MOSS_ROOT}/platform/platform_intern.h
    
    ${MOSS_ROOT}/platform/android/.h
    ${MOSS_ROOT}/platform/ios/.h
    ${MOSS_ROOT}/platform/macos/.h
	
    ${MOSS_ROOT}/platform/linux/linux_platform.h
    ${MOSS_ROOT}/platform/linux/linux_input.c
    ${MOSS_ROOT}/platform/linux/wl_monitor.c
    ${MOSS_ROOT}/platform/linux/wl_window.c
    ${MOSS_ROOT}/platform/linux/x11_monitor.c
    ${MOSS_ROOT}/platform/linux/x11_window.c
    ${MOSS_ROOT}/platform/windows/win32_window.c
    ${MOSS_ROOT}/platform/windows/win32_monitor.c
    ${MOSS_ROOT}/platform/windows/win32_input.c

    # Audio
	${MOSS_ROOT}/audio/audio_intern.h
	${MOSS_ROOT}/audio/linux/alsa_audio.c
	${MOSS_ROOT}/audio/linux/alsa_microphone.c
	${MOSS_ROOT}/audio/linux/alsa_speaker.c
	${MOSS_ROOT}/audio/mac/mac_audio.c
	${MOSS_ROOT}/audio/mac/mac_microphone.c
	${MOSS_ROOT}/audio/mac/mac_speaker.c
	${MOSS_ROOT}/audio/windows/win32_audio.c
	${MOSS_ROOT}/audio/windows/win32_microphone.c
	${MOSS_ROOT}/audio/windows/win32_speaker.c

    # Network
    ${MOSS_ROOT}/network/address.c
    ${MOSS_ROOT}/network/callbacks.c
    ${MOSS_ROOT}/network/compress.c
    ${MOSS_ROOT}/network/host.c
    ${MOSS_ROOT}/network/list.c
    ${MOSS_ROOT}/network/packet.c
    ${MOSS_ROOT}/network/protocol.c
    ${MOSS_ROOT}/network/unix.c
    ${MOSS_ROOT}/network/win32.c

    # Renderer
    ${MOSS_ROOT}/renderer/moss_renderer.c

    # Physics
	${MOSS_ROOT}/physics/moss_physics.c

    # XR <OpenXR>
	${MOSS_ROOT}/XR/moss_xr.c
)

add_library(Moss STATIC ${MOSS_SOURCES})
add_library(Moss::Moss ALIAS Moss)

# Include public headers
target_include_directories(Moss PUBLIC
	$<BUILD_INTERFACE:${REPO_ROOT}>
	$<INSTALL_INTERFACE:include/>)

# You can enforce stricter warnings for internal builds
target_compile_options(Moss PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -Wpedantic>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -Wpedantic -Wno-unused-parameter>
)
