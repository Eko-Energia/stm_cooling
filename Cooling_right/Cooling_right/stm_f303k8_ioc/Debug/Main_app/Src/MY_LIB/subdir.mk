################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main_app/Src/MY_LIB/MY_driver_can.c \
../Main_app/Src/MY_LIB/MY_driver_fan.c \
../Main_app/Src/MY_LIB/MY_driver_i2c.c \
../Main_app/Src/MY_LIB/MY_driver_serwo.c 

OBJS += \
./Main_app/Src/MY_LIB/MY_driver_can.o \
./Main_app/Src/MY_LIB/MY_driver_fan.o \
./Main_app/Src/MY_LIB/MY_driver_i2c.o \
./Main_app/Src/MY_LIB/MY_driver_serwo.o 

C_DEPS += \
./Main_app/Src/MY_LIB/MY_driver_can.d \
./Main_app/Src/MY_LIB/MY_driver_fan.d \
./Main_app/Src/MY_LIB/MY_driver_i2c.d \
./Main_app/Src/MY_LIB/MY_driver_serwo.d 


# Each subdirectory must supply rules for building sources it contributes
Main_app/Src/MY_LIB/%.o Main_app/Src/MY_LIB/%.su Main_app/Src/MY_LIB/%.cyclo: ../Main_app/Src/MY_LIB/%.c Main_app/Src/MY_LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Inc/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Inc/MY_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Src/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Src/MY_LIB" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Inc" -I"E:/Pulpit/PCB/SOFT_Nie_Git/work_2/Cooling_right/stm_f303k8_ioc/Main_app/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Main_app-2f-Src-2f-MY_LIB

clean-Main_app-2f-Src-2f-MY_LIB:
	-$(RM) ./Main_app/Src/MY_LIB/MY_driver_can.cyclo ./Main_app/Src/MY_LIB/MY_driver_can.d ./Main_app/Src/MY_LIB/MY_driver_can.o ./Main_app/Src/MY_LIB/MY_driver_can.su ./Main_app/Src/MY_LIB/MY_driver_fan.cyclo ./Main_app/Src/MY_LIB/MY_driver_fan.d ./Main_app/Src/MY_LIB/MY_driver_fan.o ./Main_app/Src/MY_LIB/MY_driver_fan.su ./Main_app/Src/MY_LIB/MY_driver_i2c.cyclo ./Main_app/Src/MY_LIB/MY_driver_i2c.d ./Main_app/Src/MY_LIB/MY_driver_i2c.o ./Main_app/Src/MY_LIB/MY_driver_i2c.su ./Main_app/Src/MY_LIB/MY_driver_serwo.cyclo ./Main_app/Src/MY_LIB/MY_driver_serwo.d ./Main_app/Src/MY_LIB/MY_driver_serwo.o ./Main_app/Src/MY_LIB/MY_driver_serwo.su

.PHONY: clean-Main_app-2f-Src-2f-MY_LIB

