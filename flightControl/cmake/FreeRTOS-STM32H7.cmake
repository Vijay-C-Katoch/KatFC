#[=======================================================================[.rst:
FreeRTOS static library creation for STM32
----------------------------------------------------

This cmake script is for building and creating static library from
thirdParty FreeRTOS source for ST Microelectronics based boards.

#]=======================================================================]

add_library(FreeRTOS-STM32 STATIC)

target_compile_options(FreeRTOS-STM32 PUBLIC
-DDEBUG
-fdata-sections
-ffunction-sections
)

# include directories from STM32CubeH7 MCU Firmware repo
target_include_directories(FreeRTOS-STM32 PUBLIC

${TP_DIR}/CANopen/CANopenNode
${TP_DIR}/CANopen/CANopenNode_STM32
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 

"${TP_DIR}/CANopen/CANopenNode_STM32/CO_driver_STM32.c"

)

target_sources(FreeRTOS-STM32 PUBLIC 
${SOURCE_FILES} 
)

# Link thirdparty libraries
target_link_libraries(FreeRTOS-STM32
  framework-stm32cubeh7
)