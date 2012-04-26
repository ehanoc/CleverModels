################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../objc/objc_model_write.c 

OBJS += \
./objc/objc_model_write.o 

C_DEPS += \
./objc/objc_model_write.d 


# Each subdirectory must supply rules for building sources it contributes
objc/%.o: ../objc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


