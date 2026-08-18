################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main_app/Src/EKO_LIB/I2C_driver.c \
../Main_app/Src/EKO_LIB/can_driver.c 

OBJS += \
./Main_app/Src/EKO_LIB/I2C_driver.o \
./Main_app/Src/EKO_LIB/can_driver.o 

C_DEPS += \
./Main_app/Src/EKO_LIB/I2C_driver.d \
./Main_app/Src/EKO_LIB/can_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Main_app/Src/EKO_LIB/%.o Main_app/Src/EKO_LIB/%.su Main_app/Src/EKO_LIB/%.cyclo: ../Main_app/Src/EKO_LIB/%.c Main_app/Src/EKO_LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_back/Cooling_back/f303_perla_blank/Main_app/Inc/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_back/Cooling_back/f303_perla_blank/Main_app/Inc/MY_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_back/Cooling_back/f303_perla_blank/Main_app/Src/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_back/Cooling_back/f303_perla_blank/Main_app/Src/MY_LIB" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Main_app-2f-Src-2f-EKO_LIB

clean-Main_app-2f-Src-2f-EKO_LIB:
	-$(RM) ./Main_app/Src/EKO_LIB/I2C_driver.cyclo ./Main_app/Src/EKO_LIB/I2C_driver.d ./Main_app/Src/EKO_LIB/I2C_driver.o ./Main_app/Src/EKO_LIB/I2C_driver.su ./Main_app/Src/EKO_LIB/can_driver.cyclo ./Main_app/Src/EKO_LIB/can_driver.d ./Main_app/Src/EKO_LIB/can_driver.o ./Main_app/Src/EKO_LIB/can_driver.su

.PHONY: clean-Main_app-2f-Src-2f-EKO_LIB

