cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

# ────────────────────────────────────────────────────────────────────────────────
# 🔖 Project Metadata Setup
# ────────────────────────────────────────────────────────────────────────────────
set(REVC_PROJECT_NAME "reVC")
set(REVC_VERSION 0.0.1)
set(REVC_DESCRIPTION "reVC Android Edition")

project(${REVC_PROJECT_NAME}
        VERSION ${REVC_VERSION}
        LANGUAGES C CXX
        DESCRIPTION ${REVC_DESCRIPTION}
)

# Enforce 16KB Page Size Alignment for Android 15 / 16
add_link_options("-Wl,-z,max-page-size=16384")

# ────────────────────────────────────────────────────────────────────────────────
# 📂 Define Important Directory Paths
# ────────────────────────────────────────────────────────────────────────────────
get_filename_component(REVC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(REVC_GAME_DIR "${REVC_ROOT_DIR}/../../../")

# ────────────────────────────────────────────────────────────────────────────────
# ⚙️ Core reVC & librw Engine Settings
# ────────────────────────────────────────────────────────────────────────────────
set(REVC_AUDIO "OAL" CACHE STRING "Audio engine" FORCE)
set(LIBRW_PLATFORM "GL3" CACHE STRING "librw platform" FORCE)
set(LIBRW_GL3_GFXLIB "SDL2" CACHE STRING "librw GFX lib" FORCE)
set(RW_GL3 ON CACHE BOOL "Enable GL3" FORCE)
set(ANDROID_x32 0 CACHE BOOL "Disable 32-bit" FORCE)

# Disable desktop samples/tools inside librw
set(LIBRW_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(LIBRW_SAMPLES OFF CACHE BOOL "" FORCE)
set(LIBRW_EXAMPLES OFF CACHE BOOL "" FORCE)

# ────────────────────────────────────────────────────────────────────────────────
# 📦 Vendor Prebuilt Libraries Configuration
# ────────────────────────────────────────────────────────────────────────────────

# 1. OpenAL
set(OPENAL_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/openal-soft/include" CACHE PATH "OpenAL include directory" FORCE)
set(OPENAL_INCLUDE_DIRS "${REVC_GAME_DIR}/vendor/openal-soft/include" CACHE PATH "OpenAL include directory" FORCE)
set(OPENAL_LIBRARY "${REVC_GAME_DIR}/vendor/openal-soft/libs/Android/${ANDROID_ABI}/libopenal.so" CACHE FILEPATH "OpenAL library" FORCE)
set(OPENAL_LIBRARIES "${REVC_GAME_DIR}/vendor/openal-soft/libs/Android/${ANDROID_ABI}/libopenal.so" CACHE FILEPATH "OpenAL library" FORCE)
set(OPENAL_FOUND TRUE CACHE BOOL "" FORCE)
set(OpenAL_FOUND TRUE CACHE BOOL "" FORCE)

if(NOT TARGET OpenAL::OpenAL)
    add_library(OpenAL::OpenAL SHARED IMPORTED GLOBAL)
    set_target_properties(OpenAL::OpenAL PROPERTIES
        IMPORTED_LOCATION "${OPENAL_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${OPENAL_INCLUDE_DIR}"
    )
endif()

# 2. SDL2
set(SDL2_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/sdl2/include" CACHE PATH "SDL2 include directory" FORCE)
set(SDL2_INCLUDE_DIRS "${REVC_GAME_DIR}/vendor/sdl2/include" CACHE PATH "SDL2 include directory" FORCE)
set(SDL2_LIBRARY "${REVC_GAME_DIR}/vendor/sdl2/libs/Android/${ANDROID_ABI}/libSDL2.so" CACHE FILEPATH "SDL2 library" FORCE)
set(SDL2_LIBRARIES "${REVC_GAME_DIR}/vendor/sdl2/libs/Android/${ANDROID_ABI}/libSDL2.so" CACHE FILEPATH "SDL2 library" FORCE)
set(SDL2_FOUND TRUE CACHE BOOL "" FORCE)
set(SDL2_DIR "${REVC_GAME_DIR}/vendor/sdl2" CACHE PATH "" FORCE)

if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 SHARED IMPORTED GLOBAL)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION "${SDL2_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
    )
endif()

# 3. mpg123 (All three: libmpg123, libout123, libsyn123)
set(MPG123_DIR "${REVC_GAME_DIR}/vendor/mpg123/lib/Android/${ANDROID_ABI}")
set(MPG123_ALL_LIBS
    "${MPG123_DIR}/libmpg123.so"
    "${MPG123_DIR}/libout123.so"
    "${MPG123_DIR}/libsyn123.so"
)

set(mpg123_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/mpg123/include" CACHE PATH "mpg123 include directory" FORCE)
set(MPG123_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/mpg123/include" CACHE PATH "mpg123 include directory" FORCE)
set(mpg123_INCLUDE_DIRS "${REVC_GAME_DIR}/vendor/mpg123/include" CACHE PATH "mpg123 include directory" FORCE)
set(MPG123_INCLUDE_DIRS "${REVC_GAME_DIR}/vendor/mpg123/include" CACHE PATH "mpg123 include directory" FORCE)

set(mpg123_LIBRARY "${MPG123_DIR}/libmpg123.so" CACHE FILEPATH "mpg123 library" FORCE)
set(MPG123_LIBRARY "${MPG123_DIR}/libmpg123.so" CACHE FILEPATH "mpg123 library" FORCE)
set(mpg123_LIBRARIES "${MPG123_ALL_LIBS}" CACHE FILEPATH "mpg123 libraries" FORCE)
set(MPG123_LIBRARIES "${MPG123_ALL_LIBS}" CACHE FILEPATH "mpg123 libraries" FORCE)

set(mpg123_FOUND TRUE CACHE BOOL "" FORCE)
set(MPG123_FOUND TRUE CACHE BOOL "" FORCE)

# ────────────────────────────────────────────────────────────────────────────────
# ➕ Add Main Game Subdirectory
# ────────────────────────────────────────────────────────────────────────────────
if(IS_DIRECTORY "${REVC_GAME_DIR}" AND EXISTS "${REVC_GAME_DIR}/CMakeLists.txt")
    add_subdirectory(${REVC_GAME_DIR} ${CMAKE_BINARY_DIR}/game_build)
else()
    message(FATAL_ERROR "reVC root CMakeLists.txt not found at: ${REVC_GAME_DIR}")
endif()
