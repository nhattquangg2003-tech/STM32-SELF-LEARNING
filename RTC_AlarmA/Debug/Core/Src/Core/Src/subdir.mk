################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Core/Src/it.c \
../Core/Src/Core/Src/main.c \
../Core/Src/Core/Src/main_app.c \
../Core/Src/Core/Src/msp.c \
../Core/Src/Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/Core/Src/stm32f4xx_it.c \
../Core/Src/Core/Src/syscalls.c \
../Core/Src/Core/Src/sysmem.c \
../Core/Src/Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Core/Src/it.o \
./Core/Src/Core/Src/main.o \
./Core/Src/Core/Src/main_app.o \
./Core/Src/Core/Src/msp.o \
./Core/Src/Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/Core/Src/stm32f4xx_it.o \
./Core/Src/Core/Src/syscalls.o \
./Core/Src/Core/Src/sysmem.o \
./Core/Src/Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Core/Src/it.d \
./Core/Src/Core/Src/main.d \
./Core/Src/Core/Src/main_app.d \
./Core/Src/Core/Src/msp.d \
./Core/Src/Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/Core/Src/stm32f4xx_it.d \
./Core/Src/Core/Src/syscalls.d \
./Core/Src/Core/Src/sysmem.d \
./Core/Src/Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Core/Src/%.o: ../Core/Src/Core/Src/%.c Core/Src/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

