#[=======================================================================[.rst:
STM32H750B-DK discovery board project specefic settings
----------------------------------------------------

This cmake script is for applying thirdparty hardware specefic settings
such as compiler, linker options to generate an executable binary for
a particular board.

#]=======================================================================]

include_guard()

include(boards/stm32/${BOARD})

# Include Thirdparty, Hardware and boards
target_include_directories(${CMAKE_PROJECT_NAME} 
  PUBLIC
  $<BUILD_INTERFACE:${HARDWARE_DIR}/boards/stm32/STM32H750B-DK/Inc>
  )

  
# Link thirdparty libraries
target_link_libraries(${CMAKE_PROJECT_NAME} framework-stm32cubeh7)

# Executable linker flags and options
target_link_libraries(${CMAKE_PROJECT_NAME}
  -lc
  -lm
)

# Linker options for executable
target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
-T${HARDWARE_DIR}/boards/stm32/STM32H750B-DK/STM32H750XBHX_FLASH.ld
-specs=nosys.specs
-specs=nano.specs
-static 
-Wl,--gc-sections 
-Wl,--no-warn-rwx-segment
-Wl,-Map=${CMAKE_PROJECT_NAME}.map
-Wl,--print-memory-usage
)
