################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TinyXML/tinystr.cpp \
../TinyXML/tinyxml.cpp \
../TinyXML/tinyxmlerror.cpp \
../TinyXML/tinyxmlparser.cpp 

OBJS += \
./TinyXML/tinystr.o \
./TinyXML/tinyxml.o \
./TinyXML/tinyxmlerror.o \
./TinyXML/tinyxmlparser.o 

CPP_DEPS += \
./TinyXML/tinystr.d \
./TinyXML/tinyxml.d \
./TinyXML/tinyxmlerror.d \
./TinyXML/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
TinyXML/%.o: ../TinyXML/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\cygwin64\lib\gcc\x86_64-pc-cygwin\4.9.3\include\c++" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\TADs" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\Parametros" -I"C:\cygwin64\home\Claudinho\workspace\CaixeiroViajante\TinyXML" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


