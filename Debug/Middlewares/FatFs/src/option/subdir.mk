################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FatFs/src/option/ccsbcs.c \
../Middlewares/FatFs/src/option/syscall.c 

OBJS += \
./Middlewares/FatFs/src/option/ccsbcs.o \
./Middlewares/FatFs/src/option/syscall.o 

C_DEPS += \
./Middlewares/FatFs/src/option/ccsbcs.d \
./Middlewares/FatFs/src/option/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/src/option/%.o Middlewares/FatFs/src/option/%.su Middlewares/FatFs/src/option/%.cyclo: ../Middlewares/FatFs/src/option/%.c Middlewares/FatFs/src/option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/FATFS/App" -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/FATFS/Target" -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/Middlewares/FatFs/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-src-2f-option

clean-Middlewares-2f-FatFs-2f-src-2f-option:
	-$(RM) ./Middlewares/FatFs/src/option/ccsbcs.cyclo ./Middlewares/FatFs/src/option/ccsbcs.d ./Middlewares/FatFs/src/option/ccsbcs.o ./Middlewares/FatFs/src/option/ccsbcs.su ./Middlewares/FatFs/src/option/syscall.cyclo ./Middlewares/FatFs/src/option/syscall.d ./Middlewares/FatFs/src/option/syscall.o ./Middlewares/FatFs/src/option/syscall.su

.PHONY: clean-Middlewares-2f-FatFs-2f-src-2f-option

