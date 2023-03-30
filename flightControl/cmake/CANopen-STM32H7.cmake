#[=======================================================================[.rst:
STM32H750B-DK discovery board static library creation
----------------------------------------------------

This cmake script is for building and creating static library from
STM32CubeH7 MCU Firmware Package source for STM32H750B-DK discovery 
board from ST Microelectronics.

#]=======================================================================]

add_library(CANopen STATIC)

target_compile_options(CANopen PUBLIC
-DDEBUG
-fdata-sections
-ffunction-sections
)

# include directories from STM32CubeH7 MCU Firmware repo
target_include_directories(CANopen PUBLIC

${TP_DIR}/CANopen/CANopenNode
${TP_DIR}/CANopen/CANopenNode_STM32
)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 

"${TP_DIR}/CANopen/CANopenNode_STM32/CO_driver_STM32.c"
"${TP_DIR}/CANopen/CANopenNode_STM32/CO_storageBlank.c"
"${TP_DIR}/CANopen/CANopenNode_STM32/OD.c"

"${TP_DIR}/CANopen/CANopenNode/301/CO_ODinterface.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_NMT_Heartbeat.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_HBconsumer.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_Emergency.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_SDOserver.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_TIME.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_SYNC.c"
"${TP_DIR}/CANopen/CANopenNode/301/CO_PDO.c"
"${TP_DIR}/CANopen/CANopenNode/303/CO_LEDs.c"
"${TP_DIR}/CANopen/CANopenNode/305/CO_LSSslave.c"
"${TP_DIR}/CANopen/CANopenNode/storage/CO_storage.c"
"${TP_DIR}/CANopen/CANopenNode/CANopen.c"

"${TP_DIR}/CANopen/CANopenNode_STM32/CO_app_STM32.c"

)

target_sources(CANopen PUBLIC 
${SOURCE_FILES} 
)

# Link thirdparty libraries
target_link_libraries(CANopen
  framework-stm32cubeh7
)