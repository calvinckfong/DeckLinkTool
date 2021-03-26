################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DecklinkAPI/DeckLinkAPIDispatch.cpp 

OBJS += \
./DecklinkAPI/DeckLinkAPIDispatch.o 

CPP_DEPS += \
./DecklinkAPI/DeckLinkAPIDispatch.d 


# Each subdirectory must supply rules for building sources it contributes
DecklinkAPI/%.o: ../DecklinkAPI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/calvin.fong/source/DeckLinkTool/DecklinkAPI -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


