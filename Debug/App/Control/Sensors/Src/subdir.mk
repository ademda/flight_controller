################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Control/Sensors/Src/Barometer.cpp \
../App/Control/Sensors/Src/Barometer_bmp280.cpp \
../App/Control/Sensors/Src/Filter.cpp \
../App/Control/Sensors/Src/IMU.cpp \
../App/Control/Sensors/Src/IMU_MPU6050.cpp \
../App/Control/Sensors/Src/Magnetometer.cpp \
../App/Control/Sensors/Src/Magnetometer_GY273.cpp \
../App/Control/Sensors/Src/StateEstimator.cpp 

OBJS += \
./App/Control/Sensors/Src/Barometer.o \
./App/Control/Sensors/Src/Barometer_bmp280.o \
./App/Control/Sensors/Src/Filter.o \
./App/Control/Sensors/Src/IMU.o \
./App/Control/Sensors/Src/IMU_MPU6050.o \
./App/Control/Sensors/Src/Magnetometer.o \
./App/Control/Sensors/Src/Magnetometer_GY273.o \
./App/Control/Sensors/Src/StateEstimator.o 

CPP_DEPS += \
./App/Control/Sensors/Src/Barometer.d \
./App/Control/Sensors/Src/Barometer_bmp280.d \
./App/Control/Sensors/Src/Filter.d \
./App/Control/Sensors/Src/IMU.d \
./App/Control/Sensors/Src/IMU_MPU6050.d \
./App/Control/Sensors/Src/Magnetometer.d \
./App/Control/Sensors/Src/Magnetometer_GY273.d \
./App/Control/Sensors/Src/StateEstimator.d 


# Each subdirectory must supply rules for building sources it contributes
App/Control/Sensors/Src/%.o App/Control/Sensors/Src/%.su App/Control/Sensors/Src/%.cyclo: ../App/Control/Sensors/Src/%.cpp App/Control/Sensors/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Control-2f-Sensors-2f-Src

clean-App-2f-Control-2f-Sensors-2f-Src:
	-$(RM) ./App/Control/Sensors/Src/Barometer.cyclo ./App/Control/Sensors/Src/Barometer.d ./App/Control/Sensors/Src/Barometer.o ./App/Control/Sensors/Src/Barometer.su ./App/Control/Sensors/Src/Barometer_bmp280.cyclo ./App/Control/Sensors/Src/Barometer_bmp280.d ./App/Control/Sensors/Src/Barometer_bmp280.o ./App/Control/Sensors/Src/Barometer_bmp280.su ./App/Control/Sensors/Src/Filter.cyclo ./App/Control/Sensors/Src/Filter.d ./App/Control/Sensors/Src/Filter.o ./App/Control/Sensors/Src/Filter.su ./App/Control/Sensors/Src/IMU.cyclo ./App/Control/Sensors/Src/IMU.d ./App/Control/Sensors/Src/IMU.o ./App/Control/Sensors/Src/IMU.su ./App/Control/Sensors/Src/IMU_MPU6050.cyclo ./App/Control/Sensors/Src/IMU_MPU6050.d ./App/Control/Sensors/Src/IMU_MPU6050.o ./App/Control/Sensors/Src/IMU_MPU6050.su ./App/Control/Sensors/Src/Magnetometer.cyclo ./App/Control/Sensors/Src/Magnetometer.d ./App/Control/Sensors/Src/Magnetometer.o ./App/Control/Sensors/Src/Magnetometer.su ./App/Control/Sensors/Src/Magnetometer_GY273.cyclo ./App/Control/Sensors/Src/Magnetometer_GY273.d ./App/Control/Sensors/Src/Magnetometer_GY273.o ./App/Control/Sensors/Src/Magnetometer_GY273.su ./App/Control/Sensors/Src/StateEstimator.cyclo ./App/Control/Sensors/Src/StateEstimator.d ./App/Control/Sensors/Src/StateEstimator.o ./App/Control/Sensors/Src/StateEstimator.su

.PHONY: clean-App-2f-Control-2f-Sensors-2f-Src

