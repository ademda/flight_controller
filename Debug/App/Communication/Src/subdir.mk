################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../App/Communication/Src/DesktopTelemetryManager.cpp \
../App/Communication/Src/GPSReceiver_Neo_6M.cpp \
../App/Communication/Src/IBUSReceiver.cpp \
../App/Communication/Src/MCUTelemetryManager.cpp \
../App/Communication/Src/RCReceiver.cpp \
../App/Communication/Src/RC_Receiver_IA6_B.cpp \
../App/Communication/Src/TelemetryManager.cpp 

OBJS += \
./App/Communication/Src/DesktopTelemetryManager.o \
./App/Communication/Src/GPSReceiver_Neo_6M.o \
./App/Communication/Src/IBUSReceiver.o \
./App/Communication/Src/MCUTelemetryManager.o \
./App/Communication/Src/RCReceiver.o \
./App/Communication/Src/RC_Receiver_IA6_B.o \
./App/Communication/Src/TelemetryManager.o 

CPP_DEPS += \
./App/Communication/Src/DesktopTelemetryManager.d \
./App/Communication/Src/GPSReceiver_Neo_6M.d \
./App/Communication/Src/IBUSReceiver.d \
./App/Communication/Src/MCUTelemetryManager.d \
./App/Communication/Src/RCReceiver.d \
./App/Communication/Src/RC_Receiver_IA6_B.d \
./App/Communication/Src/TelemetryManager.d 


# Each subdirectory must supply rules for building sources it contributes
App/Communication/Src/%.o App/Communication/Src/%.su App/Communication/Src/%.cyclo: ../App/Communication/Src/%.cpp App/Communication/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/app_drivers/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Blogic/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Communication/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Controller/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Filters/Inc" -I"C:/Users/dalya/STM32CubeIDE/Project_ws/flight_controller_v2/App/Control/Sensors/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Communication-2f-Src

clean-App-2f-Communication-2f-Src:
	-$(RM) ./App/Communication/Src/DesktopTelemetryManager.cyclo ./App/Communication/Src/DesktopTelemetryManager.d ./App/Communication/Src/DesktopTelemetryManager.o ./App/Communication/Src/DesktopTelemetryManager.su ./App/Communication/Src/GPSReceiver_Neo_6M.cyclo ./App/Communication/Src/GPSReceiver_Neo_6M.d ./App/Communication/Src/GPSReceiver_Neo_6M.o ./App/Communication/Src/GPSReceiver_Neo_6M.su ./App/Communication/Src/IBUSReceiver.cyclo ./App/Communication/Src/IBUSReceiver.d ./App/Communication/Src/IBUSReceiver.o ./App/Communication/Src/IBUSReceiver.su ./App/Communication/Src/MCUTelemetryManager.cyclo ./App/Communication/Src/MCUTelemetryManager.d ./App/Communication/Src/MCUTelemetryManager.o ./App/Communication/Src/MCUTelemetryManager.su ./App/Communication/Src/RCReceiver.cyclo ./App/Communication/Src/RCReceiver.d ./App/Communication/Src/RCReceiver.o ./App/Communication/Src/RCReceiver.su ./App/Communication/Src/RC_Receiver_IA6_B.cyclo ./App/Communication/Src/RC_Receiver_IA6_B.d ./App/Communication/Src/RC_Receiver_IA6_B.o ./App/Communication/Src/RC_Receiver_IA6_B.su ./App/Communication/Src/TelemetryManager.cyclo ./App/Communication/Src/TelemetryManager.d ./App/Communication/Src/TelemetryManager.o ./App/Communication/Src/TelemetryManager.su

.PHONY: clean-App-2f-Communication-2f-Src

