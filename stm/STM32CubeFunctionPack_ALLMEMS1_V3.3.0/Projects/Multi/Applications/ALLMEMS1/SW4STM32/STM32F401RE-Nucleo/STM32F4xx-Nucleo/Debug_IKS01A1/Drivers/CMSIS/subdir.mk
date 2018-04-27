################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Projects/Multi/Applications/ALLMEMS1/Src/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Projects/Multi/Applications/ALLMEMS1/Src/system_stm32f4xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32_NUCLEO -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DIKS01A1 -DALLMEMS1 -DDISABLE_FOTA -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Projects/Multi/Applications/ALLMEMS1/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_BlueNRG/SimpleBlueNRG_HCI/includes" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_BlueNRG/Interface" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/STM32F4xx-Nucleo" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/X-NUCLEO-CCA02M1" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/X-NUCLEO-IDB0xA1" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/X_NUCLEO_IKS01A1" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/Common" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/hts221" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/lis3mdl" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/lps22hb" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/lps25hb" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_MotionAR_Library/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_MotionFX_Library/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_AcousticBF_Library/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_AcousticSL_Library/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_BlueVoiceADPCM_Library/Inc" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_MetaDataManager" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Middlewares/ST/STM32_Audio/Addons/PDM" -I"C:/Users/a0h72490/WAc6-WorkSpace/STM32CubeFunctionPack_ALLMEMS1_V3.3.0/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


