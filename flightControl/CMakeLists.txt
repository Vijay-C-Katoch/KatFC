cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/tools")

project(KATFC VERSION 0.0.1)
message(STATUS "Configuring ${PROJECT_NAME}")

project(${CMAKE_PROJECT_NAME} LANGUAGES C CXX ASM)

# Set required standard level
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 17)

include(common)

# Default to installing in build directory
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${KATFC_BINARY_DIR}/install
    CACHE PATH "Default install path" FORCE)
endif()

message(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR is ${CMAKE_SYSTEM_PROCESSOR}")

# update compiler flag with FORCE, as are already set in toolchain cmake
set(CMAKE_C_FLAGS 
  "${CMAKE_C_FLAGS} -O0 -ffunction-sections -fdata-sections  \
  --param max-inline-insns-single=500" 
  CACHE STRING "" FORCE
  )
set(CMAKE_CXX_FLAGS 
  "${CMAKE_CXX_FLAGS} -O0 -fno-threadsafe-statics -fno-rtti -fno-exceptions \
  -fno-use-cxa-atexit -ffunction-sections -fdata-sections \
  --param max-inline-insns-single=500" 
  CACHE STRING "" FORCE)


# Generate version numbers
configure_file (
  version.h.in
  ${KATFC_BINARY_DIR}/src/include/version.h
  )

# Add platform-dependent targets early, so they can be configured by
# platform
#add_library(${CMAKE_PROJECT_NAME}  "")
add_executable(${CMAKE_PROJECT_NAME}  "")


# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths. BUILD_INTERFACE refer build tree and used for building
# project. INSTALL_INTERFACE refers install tree install(EXPORT)
# use things listed in install interface
target_include_directories(${CMAKE_PROJECT_NAME} 
  #PUBLIC
  #$<BUILD_INTERFACE:${XILINX_DEMO_SOURCE_DIR}>/src
  #$<BUILD_INTERFACE:${XILINX_DEMO_BINARY_DIR}/include>
  #$<INSTALL_INTERFACE:include>
  PRIVATE
  ${KATFC_BINARY_DIR}/src/include
  )


# add directory to find sources in build tree
add_subdirectory (src)

# Build for desired board/hardware
include(${BOARD})

install (
  TARGETS
  ${CMAKE_PROJECT_NAME} 
  DESTINATION bin)

  # Post build command to analyze elf file
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
      POST_BUILD
      COMMAND arm-none-eabi-objdump -C -x -S ${CMAKE_PROJECT_NAME}.elf > "${CMAKE_PROJECT_NAME}.objdump"
      COMMAND bloaty ${CMAKE_PROJECT_NAME}.elf > "${CMAKE_PROJECT_NAME}.out.bloaty"
      )

# this module to search for compiler-provided system runtime libraries
# and add install rules for them  all library files listed in the variable
# CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS will be installed with install(PROGRAMS …)
# into bin for WIN32 and lib for non-WIN32.
include (InstallRequiredSystemLibraries)
