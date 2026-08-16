################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EKO_LIB/I2C_driver.c \
../Core/Src/EKO_LIB/can_driver.c 

OBJS += \
./Core/Src/EKO_LIB/I2C_driver.o \
./Core/Src/EKO_LIB/can_driver.o 

C_DEPS += \
./Core/Src/EKO_LIB/I2C_driver.d \
./Core/Src/EKO_LIB/can_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EKO_LIB/%.o Core/Src/EKO_LIB/%.su Core/Src/EKO_LIB/%.cyclo: ../Core/Src/EKO_LIB/%.c Core/Src/EKO_LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Src/EKO_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Inc/EKO_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Src/MY_LIB" -I"E:/Pulpit/PCB/Plytki_chlodzenia_SOFTWARE/Cooling_left/stm_f303k8_ioc/Core/Inc/MY_LIB" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-EKO_LIB

clean-Core-2f-Src-2f-EKO_LIB:
	-$(RM) ./Core/Src/EKO_LIB/I2C_driver.cyclo ./Core/Src/EKO_LIB/I2C_driver.d ./Core/Src/EKO_LIB/I2C_driver.o ./Core/Src/EKO_LIB/I2C_driver.su ./Core/Src/EKO_LIB/can_driver.cyclo ./Core/Src/EKO_LIB/can_driver.d ./Core/Src/EKO_LIB/can_driver.o ./Core/Src/EKO_LIB/can_driver.su

.PHONY: clean-Core-2f-Src-2f-EKO_LIB

