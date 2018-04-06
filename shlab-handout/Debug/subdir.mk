################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../csapp.c \
../fail.c \
../parse.c \
../whoosh.c 

OBJS += \
./csapp.o \
./fail.o \
./parse.o \
./whoosh.o 

C_DEPS += \
./csapp.d \
./fail.d \
./parse.d \
./whoosh.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


