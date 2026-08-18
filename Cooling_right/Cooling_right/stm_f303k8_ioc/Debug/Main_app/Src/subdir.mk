################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main_app/Src/cooler_left_app.c \
../Main_app/Src/cooler_test.c 

OBJS += \
./Main_app/Src/cooler_left_app.o \
./Main_app/Src/cooler_test.o 

C_DEPS += \
./Main_app/Src/cooler_left_app.d \
./Main_app/Src/cooler_test.d 


# Each subdirectory must supply rules for building sources it contributes
Main_app/Src/%.o Main_app/Src/%.su Main_app/Src/%.cyclo: ../Main_app/Src/%.c Main_app/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Inc/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Inc/MY_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Src/EKO_LIB" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Src/MY_LIB" -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Inc" -I"E:/Pulpit/PCB/SOFT_Nie_Git/Cooling_right/Cooling_right/stm_f303k8_ioc/Main_app/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Main_app-2f-Src

clean-Main_app-2f-Src:
	-$(RM) ./Main_app/Src/cooler_left_app.cyclo ./Main_app/Src/cooler_left_app.d ./Main_app/Src/cooler_left_app.o ./Main_app/Src/cooler_left_app.su ./Main_app/Src/cooler_test.cyclo ./Main_app/Src/cooler_test.d ./Main_app/Src/cooler_test.o ./Main_app/Src/cooler_test.su

.PHONY: clean-Main_app-2f-Src

