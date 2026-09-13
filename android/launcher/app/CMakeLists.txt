# ==================================================================================================
# 📱 reVC – Mobile Edition (Android) – Root CMake Configuration
#
# Description:
# This file defines the root CMake configuration for the reVC – Mobile Edition,
# targeting the Android platform via the Android NDK. It initializes the build system
# for the mobile game, integrates shared cross-platform sources, configures compiler settings,
# and handles dependency resolution.
# ==================================================================================================

cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

message(" ")
message("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
message(" *  🌐  reVC – Build Configuration Initialized")
message(" *  🔧  Preparing Android platform modules and environment configuration...")
message("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
message(" ")

# ────────────────────────────────────────────────────────────────────────────────
# 🔖 Project Metadata Setup
# ────────────────────────────────────────────────────────────────────────────────
set(REVC_PROJECT_NAME "reVC")
set(REVC_VERSION 0.0.1)
set(REVC_DESCRIPTION "reverted ${REVC_PROJECT_NAME}")
set(REVC_LIB_NAME revc)

project(${REVC_PROJECT_NAME}
        VERSION ${REVC_VERSION}
        LANGUAGES C CXX
        DESCRIPTION ${REVC_DESCRIPTION}
)

# ────────────────────────────────────────────────────────────────────────────────
# 📂 Define Important Directory Paths
# ────────────────────────────────────────────────────────────────────────────────
get_filename_component(REVC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(REVC_GAME_DIR "${REVC_ROOT_DIR}/../../../")
message(" *  📂 Game source directory set to: ${REVC_GAME_DIR}")

# ────────────────────────────────────────────────────────────────────────────────
# ➕ Add Game Subdirectory If Available
# ────────────────────────────────────────────────────────────────────────────────
if(IS_DIRECTORY "${REVC_GAME_DIR}" AND EXISTS "${REVC_GAME_DIR}/CMakeLists.txt")
    message(" *  ➕ Including Game module from: ${REVC_GAME_DIR}")
    message(" ")
    message("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
    message(" *  🚀 Initiating Game module build configuration...")
    message("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━")
    message(" ")
    # Explicitly provide prebuilt vendor paths for Android
    set(OPENAL_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/openal-soft/include" CACHE PATH "OpenAL include directory" FORCE)
    set(OPENAL_LIBRARY "${REVC_GAME_DIR}/vendor/openal-soft/libs/Android/${ANDROID_ABI}/libopenal.so" CACHE FILEPATH "OpenAL library" FORCE)

    set(SDL2_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/sdl2/include" CACHE PATH "SDL2 include directory" FORCE)
    set(SDL2_LIBRARY "${REVC_GAME_DIR}/vendor/sdl2/libs/Android/${ANDROID_ABI}/libSDL2.so" CACHE FILEPATH "SDL2 library" FORCE)

    set(MPG123_INCLUDE_DIR "${REVC_GAME_DIR}/vendor/mpg123/include" CACHE PATH "mpg123 include directory" FORCE)
    set(MPG123_LIBRARY "${REVC_GAME_DIR}/vendor/mpg123/lib/Android/${ANDROID_ABI}/libmpg123.so" CACHE FILEPATH "mpg123 library" FORCE)
    set(MPG123_LIBRARIES "${REVC_GAME_DIR}/vendor/mpg123/lib/Android/${ANDROID_ABI}/libmpg123.so" CACHE FILEPATH "mpg123 libraries" FORCE)

    add_subdirectory(${REVC_GAME_DIR} ${CMAKE_BINARY_DIR}/game_build)
else()
    message(" *  ⚠️ Game source directory or CMakeLists.txt not found at: ${REVC_GAME_DIR}")
    message(FATAL_ERROR " *  ❗ Please ensure the game module sources are available for the build.")
endif()
