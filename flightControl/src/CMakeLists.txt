# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------

set(SRC_APP
    ${CMAKE_CURRENT_SOURCE_DIR}/app/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app/app_freertos.c
)

set(CORE_INCLUDE_DIRS
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
)
