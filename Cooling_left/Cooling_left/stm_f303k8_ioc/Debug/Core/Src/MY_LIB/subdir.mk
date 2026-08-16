################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MY_LIB/MY_driver_can.c \
../Core/Src/MY_LIB/MY_driver_fan.c \
../Core/Src/MY_LIB/MY_driver_i2c.c \
../Core/Src/MY_LIB/MY_driver_serwo.c 

OBJS += \
./Core/Src/MY_LIB/MY_driver_can.o \
./Core/Src/MY_LIB/MY_driver_fan.o \
./Core/Src/MY_LIB/MY_driver_i2c.o \
./Core/Src/MY_LIB/MY_driver_serwo.o 

C_DEPS += \
./Core/Src/MY_LIB/MY_driver_can.d \
./Core/Src/MY_LIB/MY_driver_fan.d \
./Core/Src/MY_LIB/MY_driver_i2c.d \
./Core/Src/MY_LIB/MY_driver_serwo.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/MY_LIB/%.o Core/Src/MY_LIB/%.su Core/Src/MY_LIB/%.cyclo: ../Core/Src/MY_LIB/%.c Core/Src/MY_LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Src/EKO_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Inc/EKO_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Src/MY_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Inc/MY_LIB" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-MY_LIB

clean-Core-2f-Src-2f-MY_LIB:
	-$(RM) ./Core/Src/MY_LIB/MY_driver_can.cyclo ./Core/Src/MY_LIB/MY_driver_can.d ./Core/Src/MY_LIB/MY_driver_can.o ./Core/Src/MY_LIB/MY_driver_can.su ./Core/Src/MY_LIB/MY_driver_fan.cyclo ./Core/Src/MY_LIB/MY_driver_fan.d ./Core/Src/MY_LIB/MY_driver_fan.o ./Core/Src/MY_LIB/MY_driver_fan.su ./Core/Src/MY_LIB/MY_driver_i2c.cyclo ./Core/Src/MY_LIB/MY_driver_i2c.d ./Core/Src/MY_LIB/MY_driver_i2c.o ./Core/Src/MY_LIB/MY_driver_i2c.su ./Core/Src/MY_LIB/MY_driver_serwo.cyclo ./Core/Src/MY_LIB/MY_driver_serwo.d ./Core/Src/MY_LIB/MY_driver_serwo.o ./Core/Src/MY_LIB/MY_driver_serwo.su

.PHONY: clean-Core-2f-Src-2f-MY_LIB

