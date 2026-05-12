################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f401ceux.s 

OBJS += \
./Core/Startup/startup_stm32f401ceux.o 

S_DEPS += \
./Core/Startup/startup_stm32f401ceux.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/ACER/STM32CubeIDE/workspace_1.13.2/BTL_lthtn_Ex1/APP" -I"C:/Users/ACER/STM32CubeIDE/workspace_1.13.2/BTL_lthtn_Ex1/BSP" -I"C:/Users/ACER/STM32CubeIDE/workspace_1.13.2/BTL_lthtn_Ex1/BSP/Src" -I"C:/Users/ACER/STM32CubeIDE/workspace_1.13.2/BTL_lthtn_Ex1/BSP/Inc" -I"C:/Users/ACER/STM32CubeIDE/workspace_1.13.2/BTL_lthtn_Ex1/APP/Inc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f401ceux.d ./Core/Startup/startup_stm32f401ceux.o

.PHONY: clean-Core-2f-Startup

