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

${TP_DIR}/middlewares/stm32_mw_freertos/Source/CMSIS_RTOS_V2
${TP_DIR}/middlewares/stm32_mw_freertos/Source/include
${TP_DIR}/middlewares/stm32_mw_freertos/Source/portable/GCC/ARM_CM4F

)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 

"${TP_DIR}/middlewares/stm32_mw_freertos/Source/CMSIS_RTOS_V2/cmsis_os2.c"

"${TP_DIR}/middlewares/stm32_mw_freertos/Source/croutine.c"      
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/stream_buffer.c"
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/event_groups.c"  
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/tasks.c"
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/list.c"          
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/timers.c"
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/queue.c"

"${TP_DIR}/middlewares/stm32_mw_freertos/Source/portable/GCC/ARM_CM4F/port.c"
"${TP_DIR}/middlewares/stm32_mw_freertos/Source/portable/MemMang/heap_4.c" 

)

target_sources(FreeRTOS-STM32 PUBLIC 
${SOURCE_FILES} 
)

# Link thirdparty libraries
# target_link_libraries(FreeRTOS-STM32
#   framework-stm32cubeh7
# )