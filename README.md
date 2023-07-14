# KatFC
Hobby Flight Control software for motors run with KatBot.     

**Note**: *This project is no longer under active development. Another*      
*version is being developed for BeagleBone.*     

## 1. Getting started
Download and install latest toolchain from arm for target    
`AArch32 bare-metal target (arm-none-eabi)`     
     
Or else download latest *none-eabi* [Arm GNU toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) and symlink to /usr/bin     
     
## 2. Download and compile KatFC     
### 2.1 Clone the source:     
     
`git clone --recurse-submodules https://github.com/Vijay-C-Katoch/KatFC.git`
     
This will clone the repository with submodules. If you already cloned the repository      
without the `--recurse-submodules` flag then run below in the KatFCfolder to
     
- clone cmake-utils
- clone thirdparty firmwares
  -  STM32CubeH7
     
`git submodule update --init --recursive`

### 2.2a Building from shell 
- To build KatFC, in the `flightControl` directory run following cmake commands      
     
```
$ BOARD=STM32H750B-DK \
    TP_DIR=$(pwd)/../thirdParty \
    HARDWARE_DIR=$(pwd)/../hardware cmake \
    -DCMAKE_TOOLCHAIN_FILE=../cmake/tools/toolchain/stm32-h750-none-eabi.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -G "Unix Makefiles" \
    -H../flightControl \
    -B../build 

$ cmake --build ../build
```     
     
### 2.2b To Build using Visual Studio Code IDE        
        
In VSCode IDE cmake `Build` can be run directly by clicking *Build* button,  as all of above CMake commands are configured in      
[kfc.code-workspace](https://github.com/Vijay-C-Katoch/KatFC/blob/77ef2fd65d1f2fab7a1d8dbd2e31a89a3ecd6b1c/kfc.code-workspace#L19) file in the project.     

## 3. Profiling

### 3.1 Binary
Install [Google bloaty](https://github.com/google/bloaty).
<br>
<br>    
  
# License
* https://github.com/Vijay-C-Katoch/KatFC/blob/main/LICENSE
