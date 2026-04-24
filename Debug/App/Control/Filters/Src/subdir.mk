################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Control/Filters/Src/ComplementaryFilter.cpp \
../App/Control/Filters/Src/KalmanFIlter.cpp 

OBJS += \
./App/Control/Filters/Src/ComplementaryFilter.o \
./App/Control/Filters/Src/KalmanFIlter.o 

CPP_DEPS += \
./App/Control/Filters/Src/ComplementaryFilter.d \
./App/Control/Filters/Src/KalmanFIlter.d 


# Each subdirectory must supply rules for building sources it contributes
App/Control/Filters/Src/%.o App/Control/Filters/Src/%.su App/Control/Filters/Src/%.cyclo: ../App/Control/Filters/Src/%.cpp App/Control/Filters/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Control-2f-Filters-2f-Src

clean-App-2f-Control-2f-Filters-2f-Src:
	-$(RM) ./App/Control/Filters/Src/ComplementaryFilter.cyclo ./App/Control/Filters/Src/ComplementaryFilter.d ./App/Control/Filters/Src/ComplementaryFilter.o ./App/Control/Filters/Src/ComplementaryFilter.su ./App/Control/Filters/Src/KalmanFIlter.cyclo ./App/Control/Filters/Src/KalmanFIlter.d ./App/Control/Filters/Src/KalmanFIlter.o ./App/Control/Filters/Src/KalmanFIlter.su

.PHONY: clean-App-2f-Control-2f-Filters-2f-Src

