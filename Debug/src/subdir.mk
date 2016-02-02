################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CaixeiroViajante.cpp 

OBJS += \
./src/CaixeiroViajante.o 

CPP_DEPS += \
./src/CaixeiroViajante.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cygwin64\lib\gcc\x86_64-pc-cygwin\4.9.3\include\c++" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\TADs" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\Parametros" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\TinyXML" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


