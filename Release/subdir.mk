################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../clever_models.c \
../helper_functions.c \
../languages.c \
../main.c \
../model_builder.c 

OBJS += \
./clever_models.o \
./helper_functions.o \
./languages.o \
./main.o \
./model_builder.o 

C_DEPS += \
./clever_models.d \
./helper_functions.d \
./languages.d \
./main.d \
./model_builder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


