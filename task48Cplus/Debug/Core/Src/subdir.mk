################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Communication.c \
../Core/Src/main.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c 

CPP_SRCS += \
../Core/Src/Button.cpp \
../Core/Src/CliCommand.cpp \
../Core/Src/CliContainer.cpp \
../Core/Src/Led.cpp \
../Core/Src/mymain.cpp 

C_DEPS += \
./Core/Src/Communication.d \
./Core/Src/main.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d 

OBJS += \
./Core/Src/Button.o \
./Core/Src/CliCommand.o \
./Core/Src/CliContainer.o \
./Core/Src/Communication.o \
./Core/Src/Led.o \
./Core/Src/main.o \
./Core/Src/mymain.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o 

CPP_DEPS += \
./Core/Src/Button.d \
./Core/Src/CliCommand.d \
./Core/Src/CliContainer.d \
./Core/Src/Led.d \
./Core/Src/mymain.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/CliCommand.d ./Core/Src/CliCommand.o ./Core/Src/CliCommand.su ./Core/Src/CliContainer.d ./Core/Src/CliContainer.o ./Core/Src/CliContainer.su ./Core/Src/Communication.d ./Core/Src/Communication.o ./Core/Src/Communication.su ./Core/Src/Led.d ./Core/Src/Led.o ./Core/Src/Led.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mymain.d ./Core/Src/mymain.o ./Core/Src/mymain.su ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su

.PHONY: clean-Core-2f-Src

