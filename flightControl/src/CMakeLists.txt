# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SRC_APP
    ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app/bsp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/app/app_canopen.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/app/app_freertos.c
)

set(SRC_AO
    ${CMAKE_CURRENT_SOURCE_DIR}/ao/os/ao_freertos.cpp
)

set(CORE_INCLUDE_DIRS  
    ${CMAKE_CURRENT_SOURCE_DIR}/ao/os 
    ${CMAKE_CURRENT_SOURCE_DIR}/ao 
    ${CMAKE_CURRENT_SOURCE_DIR}/app 
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
  ${CORE_INCLUDE_DIRS}
  )

#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
${SRC_APP}
${SRC_AO}
)
