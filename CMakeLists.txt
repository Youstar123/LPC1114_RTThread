CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m0)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "E:/env-windows-v2.0.0/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_ASM_COMPILER "E:/env-windows-v2.0.0/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-gcc.exe")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections -Wall -O0 -gdwarf-2")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections -x assembler-with-cpp -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "E:/env-windows-v2.0.0/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-g++.exe")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections -Wall -O0 -gdwarf-2")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "E:/env-windows-v2.0.0/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-objcopy.exe")
SET(CMAKE_SIZE "E:/env-windows-v2.0.0/env-windows/tools/bin/../../tools/gnu_gcc/arm_gcc/mingw/bin/arm-none-eabi-size.exe")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m0 -mthumb -ffunction-sections -fdata-sections -nostartfiles -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/link.lds -Wl,--gc-sections,--print-memory-usage")

SET(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)

PROJECT(rtthread C CXX ASM)

INCLUDE_DIRECTORIES(
	.
	applications
	driver
	driver/nxp_drivers
	driver/drivers
	driver/modules/led
	driver/modules/key
	rt-thread/include
	rt-thread/libcpu/arm/common
	rt-thread/libcpu/arm/cortex-m0
	rt-thread/components/drivers/phy
	rt-thread/components/drivers/include
	rt-thread/components/drivers/smp_call
)

ADD_DEFINITIONS(
	-D__RTTHREAD__
)

# Library source files
SET(RT_APPLICATIONS_SOURCES
	applications/syscalls.c
	applications/sysmem.c
	applications/main.c
)

SET(RT_DEVICEDRIVERS_SOURCES
)

SET(RT_DRIVERS_SOURCES
	driver/modules/key/key.c
	driver/modules/led/led.c
	driver/drivers/gpio.c
	driver/board.c
	driver/startup_gcc.s
)

SET(RT_KERNEL_SOURCES
	rt-thread/src/clock.c
	rt-thread/src/components.c
	rt-thread/src/cpu_up.c
	rt-thread/src/defunct.c
	rt-thread/src/idle.c
	rt-thread/src/ipc.c
	rt-thread/src/irq.c
	rt-thread/src/kservice.c
	rt-thread/src/mem.c
	rt-thread/src/mempool.c
	rt-thread/src/object.c
	rt-thread/src/scheduler_comm.c
	rt-thread/src/scheduler_up.c
	rt-thread/src/thread.c
	rt-thread/src/timer.c
)

SET(RT_KLIBC_SOURCES
	rt-thread/src/klibc/kerrno.c
	rt-thread/src/klibc/rt_vsscanf.c
	rt-thread/src/klibc/kstring.c
	rt-thread/src/klibc/kstdio.c
	rt-thread/src/klibc/rt_vsnprintf_tiny.c
)

SET(RT_LIBCPU_SOURCES
	rt-thread/libcpu/arm/common/div0.c
	rt-thread/libcpu/arm/common/showmem.c
	rt-thread/libcpu/arm/cortex-m0/context_gcc.S
	rt-thread/libcpu/arm/cortex-m0/cpuport.c
)

SET(RT_UTC_UTEST_SOURCES
)

SET(RT_UTESTCASES_SOURCES
)

# Library search paths
# Library local macro definitions
SET(RT_KERNEL_DEFINES
	__RT_KERNEL_SOURCE__
)

# Library dependencies
# Libraries
ADD_LIBRARY(rtt_Drivers OBJECT ${RT_DRIVERS_SOURCES})
ADD_LIBRARY(rtt_Kernel OBJECT ${RT_KERNEL_SOURCES})
ADD_LIBRARY(rtt_klibc OBJECT ${RT_KLIBC_SOURCES})
ADD_LIBRARY(rtt_libcpu OBJECT ${RT_LIBCPU_SOURCES})

# Interface libraries
ADD_LIBRARY(rtt_DeviceDrivers INTERFACE)
ADD_LIBRARY(rtt_utc_UTest INTERFACE)
ADD_LIBRARY(rtt_utestcases INTERFACE)

# Private macros
TARGET_COMPILE_DEFINITIONS(rtt_Kernel PRIVATE ${RT_KERNEL_DEFINES})

# Interface library search paths

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${RT_APPLICATIONS_SOURCES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}.elf
	rtt_Drivers
	rtt_Kernel
	rtt_klibc
	rtt_libcpu
	rtt_DeviceDrivers
	rtt_utc_UTest
	rtt_utestcases
)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
	COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf rtthread.bin
	COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
)

# if custom.cmake is exist, add it
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/custom.cmake)
endif()
