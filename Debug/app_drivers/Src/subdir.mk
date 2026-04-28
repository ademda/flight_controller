################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app_drivers/Src/bmp280.c \
../app_drivers/Src/esc_pwm.c \
../app_drivers/Src/hmc5883l.c \
../app_drivers/Src/mpu6050.c \
../app_drivers/Src/sbus_rx.c 

OBJS += \
./app_drivers/Src/bmp280.o \
./app_drivers/Src/esc_pwm.o \
./app_drivers/Src/hmc5883l.o \
./app_drivers/Src/mpu6050.o \
./app_drivers/Src/sbus_rx.o 

C_DEPS += \
./app_drivers/Src/bmp280.d \
./app_drivers/Src/esc_pwm.d \
./app_drivers/Src/hmc5883l.d \
./app_drivers/Src/mpu6050.d \
./app_drivers/Src/sbus_rx.d 


# Each subdirectory must supply rules for building sources it contributes
app_drivers/Src/%.o app_drivers/Src/%.su app_drivers/Src/%.cyclo: ../app_drivers/Src/%.c app_drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v3/app_drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app_drivers-2f-Src

clean-app_drivers-2f-Src:
	-$(RM) ./app_drivers/Src/bmp280.cyclo ./app_drivers/Src/bmp280.d ./app_drivers/Src/bmp280.o ./app_drivers/Src/bmp280.su ./app_drivers/Src/esc_pwm.cyclo ./app_drivers/Src/esc_pwm.d ./app_drivers/Src/esc_pwm.o ./app_drivers/Src/esc_pwm.su ./app_drivers/Src/hmc5883l.cyclo ./app_drivers/Src/hmc5883l.d ./app_drivers/Src/hmc5883l.o ./app_drivers/Src/hmc5883l.su ./app_drivers/Src/mpu6050.cyclo ./app_drivers/Src/mpu6050.d ./app_drivers/Src/mpu6050.o ./app_drivers/Src/mpu6050.su ./app_drivers/Src/sbus_rx.cyclo ./app_drivers/Src/sbus_rx.d ./app_drivers/Src/sbus_rx.o ./app_drivers/Src/sbus_rx.su

.PHONY: clean-app_drivers-2f-Src

