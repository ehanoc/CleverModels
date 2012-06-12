################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cs/cs_model_writer.c 

OBJS += \
./cs/cs_model_writer.o 

C_DEPS += \
./cs/cs_model_writer.d 


# Each subdirectory must supply rules for building sources it contributes
cs/%.o: ../cs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


