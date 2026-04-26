################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Blogic/Src/Config.cpp \
../App/Blogic/Src/Drone.cpp \
../App/Blogic/Src/FlightController.cpp \
../App/Blogic/Src/FlightControllerInit.cpp 

C_SRCS += \
../App/Blogic/Src/pid_tuning_cmd.c \
../App/Blogic/Src/tuning.c 

C_DEPS += \
./App/Blogic/Src/pid_tuning_cmd.d \
./App/Blogic/Src/tuning.d 

OBJS += \
./App/Blogic/Src/Config.o \
./App/Blogic/Src/Drone.o \
./App/Blogic/Src/FlightController.o \
./App/Blogic/Src/FlightControllerInit.o \
./App/Blogic/Src/pid_tuning_cmd.o \
./App/Blogic/Src/tuning.o 

CPP_DEPS += \
./App/Blogic/Src/Config.d \
./App/Blogic/Src/Drone.d \
./App/Blogic/Src/FlightController.d \
./App/Blogic/Src/FlightControllerInit.d 


# Each subdirectory must supply rules for building sources it contributes
App/Blogic/Src/%.o App/Blogic/Src/%.su App/Blogic/Src/%.cyclo: ../App/Blogic/Src/%.cpp App/Blogic/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
App/Blogic/Src/%.o App/Blogic/Src/%.su App/Blogic/Src/%.cyclo: ../App/Blogic/Src/%.c App/Blogic/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Blogic-2f-Src

clean-App-2f-Blogic-2f-Src:
	-$(RM) ./App/Blogic/Src/Config.cyclo ./App/Blogic/Src/Config.d ./App/Blogic/Src/Config.o ./App/Blogic/Src/Config.su ./App/Blogic/Src/Drone.cyclo ./App/Blogic/Src/Drone.d ./App/Blogic/Src/Drone.o ./App/Blogic/Src/Drone.su ./App/Blogic/Src/FlightController.cyclo ./App/Blogic/Src/FlightController.d ./App/Blogic/Src/FlightController.o ./App/Blogic/Src/FlightController.su ./App/Blogic/Src/FlightControllerInit.cyclo ./App/Blogic/Src/FlightControllerInit.d ./App/Blogic/Src/FlightControllerInit.o ./App/Blogic/Src/FlightControllerInit.su ./App/Blogic/Src/pid_tuning_cmd.cyclo ./App/Blogic/Src/pid_tuning_cmd.d ./App/Blogic/Src/pid_tuning_cmd.o ./App/Blogic/Src/pid_tuning_cmd.su ./App/Blogic/Src/tuning.cyclo ./App/Blogic/Src/tuning.d ./App/Blogic/Src/tuning.o ./App/Blogic/Src/tuning.su

.PHONY: clean-App-2f-Blogic-2f-Src

