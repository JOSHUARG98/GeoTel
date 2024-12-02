################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CANx.c \
../Src/GPIOx.c \
../Src/I2Cx.c \
../Src/NVIC.c \
../Src/USARTx.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/CANx.o \
./Src/GPIOx.o \
./Src/I2Cx.o \
./Src/NVIC.o \
./Src/USARTx.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/CANx.d \
./Src/GPIOx.d \
./Src/I2Cx.d \
./Src/NVIC.d \
./Src/USARTx.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L452RETxP -DSTM32L4 -DSTM32 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/CANx.cyclo ./Src/CANx.d ./Src/CANx.o ./Src/CANx.su ./Src/GPIOx.cyclo ./Src/GPIOx.d ./Src/GPIOx.o ./Src/GPIOx.su ./Src/I2Cx.cyclo ./Src/I2Cx.d ./Src/I2Cx.o ./Src/I2Cx.su ./Src/NVIC.cyclo ./Src/NVIC.d ./Src/NVIC.o ./Src/NVIC.su ./Src/USARTx.cyclo ./Src/USARTx.d ./Src/USARTx.o ./Src/USARTx.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32l4xx.cyclo ./Src/system_stm32l4xx.d ./Src/system_stm32l4xx.o ./Src/system_stm32l4xx.su

.PHONY: clean-Src

