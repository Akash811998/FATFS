################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FatFs/src/diskio.c \
../Middlewares/FatFs/src/ff.c \
../Middlewares/FatFs/src/ff_gen_drv.c 

OBJS += \
./Middlewares/FatFs/src/diskio.o \
./Middlewares/FatFs/src/ff.o \
./Middlewares/FatFs/src/ff_gen_drv.o 

C_DEPS += \
./Middlewares/FatFs/src/diskio.d \
./Middlewares/FatFs/src/ff.d \
./Middlewares/FatFs/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/src/%.o Middlewares/FatFs/src/%.su Middlewares/FatFs/src/%.cyclo: ../Middlewares/FatFs/src/%.c Middlewares/FatFs/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/FATFS/App" -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/FATFS/Target" -I"C:/Users/virendra/OneDrive - STMicroelectronics/Documents/FATFS_UDEMY/FATFS/Middlewares/FatFs/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-src

clean-Middlewares-2f-FatFs-2f-src:
	-$(RM) ./Middlewares/FatFs/src/diskio.cyclo ./Middlewares/FatFs/src/diskio.d ./Middlewares/FatFs/src/diskio.o ./Middlewares/FatFs/src/diskio.su ./Middlewares/FatFs/src/ff.cyclo ./Middlewares/FatFs/src/ff.d ./Middlewares/FatFs/src/ff.o ./Middlewares/FatFs/src/ff.su ./Middlewares/FatFs/src/ff_gen_drv.cyclo ./Middlewares/FatFs/src/ff_gen_drv.d ./Middlewares/FatFs/src/ff_gen_drv.o ./Middlewares/FatFs/src/ff_gen_drv.su

.PHONY: clean-Middlewares-2f-FatFs-2f-src

