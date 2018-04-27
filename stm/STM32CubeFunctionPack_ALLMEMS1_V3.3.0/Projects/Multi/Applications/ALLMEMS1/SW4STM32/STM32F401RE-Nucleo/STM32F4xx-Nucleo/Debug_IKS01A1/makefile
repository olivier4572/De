################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/STM32_BlueNRG/Utils/subdir.mk
-include Middlewares/STM32_BlueNRG/Interface/subdir.mk
-include Middlewares/STM32_BlueNRG/HCI/controller/subdir.mk
-include Middlewares/STM32_BlueNRG/HCI/subdir.mk
-include Middlewares/MetaDataManager/subdir.mk
-include FP-SNS-ALLMEMS1/User/subdir.mk
-include FP-SNS-ALLMEMS1/SW4STM32/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/X-NUCLEO-IKS01A1/subdir.mk
-include Drivers/BSP/X-NUCLEO-IDB0xA1/subdir.mk
-include Drivers/BSP/X-NUCLEO-CCA02M1/subdir.mk
-include Drivers/BSP/STM32F4xx-Nucleo/subdir.mk
-include Drivers/BSP/Components/IKS01A1/subdir.mk
-include Drivers/BSP/Components/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ALLMEMS1_IKS01A1_NucleoF401.elf

# Tool invocations
ALLMEMS1_IKS01A1_NucleoF401.elf: $(OBJS) $(USER_OBJS) ../LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_MotionAR_Library\Lib" -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_MotionFX_Library\Lib" -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_AcousticBF_Library\Lib" -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_AcousticSL_Library\Lib" -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_BlueVoiceADPCM_Library\Lib" -L"C:\Users\a0h72490\WAc6-WorkSpace\STM32CubeFunctionPack_ALLMEMS1_V3.3.0\Middlewares\ST\STM32_Audio\Addons\PDM"  -specs=nano.specs -T"../LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "ALLMEMS1_IKS01A1_NucleoF401.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "ALLMEMS1_IKS01A1_NucleoF401.elf" "ALLMEMS1_IKS01A1_NucleoF401.bin"
	arm-none-eabi-size "ALLMEMS1_IKS01A1_NucleoF401.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
