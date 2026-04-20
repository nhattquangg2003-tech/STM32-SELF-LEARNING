################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/STM32F103C8T6_I2C_driver.c \
../Drivers/Src/STM32F103C8T6_SPI_driver.c \
../Drivers/Src/STM32F103C8T6_UART_driver.c \
../Drivers/Src/STM32F103C8T6_gpio_driver.c 

OBJS += \
./Drivers/Src/STM32F103C8T6_I2C_driver.o \
./Drivers/Src/STM32F103C8T6_SPI_driver.o \
./Drivers/Src/STM32F103C8T6_UART_driver.o \
./Drivers/Src/STM32F103C8T6_gpio_driver.o 

C_DEPS += \
./Drivers/Src/STM32F103C8T6_I2C_driver.d \
./Drivers/Src/STM32F103C8T6_SPI_driver.d \
./Drivers/Src/STM32F103C8T6_UART_driver.d \
./Drivers/Src/STM32F103C8T6_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/stm322/STM32F103C8T6 ARM Cortex M3/Drivers/Inc" -I"D:/stm322/STM32F103C8T6 ARM Cortex M3/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

