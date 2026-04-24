################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Control/Controller/Src/ControlSystem.cpp \
../App/Control/Controller/Src/MotorController.cpp \
../App/Control/Controller/Src/PIDController.cpp 

OBJS += \
./App/Control/Controller/Src/ControlSystem.o \
./App/Control/Controller/Src/MotorController.o \
./App/Control/Controller/Src/PIDController.o 

CPP_DEPS += \
./App/Control/Controller/Src/ControlSystem.d \
./App/Control/Controller/Src/MotorController.d \
./App/Control/Controller/Src/PIDController.d 


# Each subdirectory must supply rules for building sources it contributes
App/Control/Controller/Src/%.o App/Control/Controller/Src/%.su App/Control/Controller/Src/%.cyclo: ../App/Control/Controller/Src/%.cpp App/Control/Controller/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Control-2f-Controller-2f-Src

clean-App-2f-Control-2f-Controller-2f-Src:
	-$(RM) ./App/Control/Controller/Src/ControlSystem.cyclo ./App/Control/Controller/Src/ControlSystem.d ./App/Control/Controller/Src/ControlSystem.o ./App/Control/Controller/Src/ControlSystem.su ./App/Control/Controller/Src/MotorController.cyclo ./App/Control/Controller/Src/MotorController.d ./App/Control/Controller/Src/MotorController.o ./App/Control/Controller/Src/MotorController.su ./App/Control/Controller/Src/PIDController.cyclo ./App/Control/Controller/Src/PIDController.d ./App/Control/Controller/Src/PIDController.o ./App/Control/Controller/Src/PIDController.su

.PHONY: clean-App-2f-Control-2f-Controller-2f-Src

