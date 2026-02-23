################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AI/App/app_x-cube-ai.c \
../AI/App/npu_cache.c \
../AI/App/npu_init.c 

OBJS += \
./AI/App/app_x-cube-ai.o \
./AI/App/npu_cache.o \
./AI/App/npu_init.o 

C_DEPS += \
./AI/App/app_x-cube-ai.d \
./AI/App/npu_cache.d \
./AI/App/npu_init.d 


# Each subdirectory must supply rules for building sources it contributes
AI/App/%.o AI/App/%.su AI/App/%.cyclo: ../AI/App/%.c AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DLL_ATON_PLATFORM=LL_ATON_PLAT_STM32N6 -DLL_ATON_OSAL=LL_ATON_OSAL_BARE_METAL -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Core/Inc -I"C:/Users/jiperez/OneDrive/STM/N657X_Image_Classification_Demo/N657X_Image_Classification_Demo/AppliNonSecure/Middlewares/ST/AI/Lib" -I"C:/Users/jiperez/OneDrive/STM/N657X_Image_Classification_Demo/N657X_Image_Classification_Demo/AppliNonSecure/Middlewares/ST/AI/Npu" -I"C:/Users/jiperez/OneDrive/STM/N657X_Image_Classification_Demo/N657X_Image_Classification_Demo/AppliNonSecure/Middlewares/ST/AI/Inc" -I"C:/Users/jiperez/OneDrive/STM/N657X_Image_Classification_Demo/N657X_Image_Classification_Demo/AppliNonSecure/AI/App" -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-AI-2f-App

clean-AI-2f-App:
	-$(RM) ./AI/App/app_x-cube-ai.cyclo ./AI/App/app_x-cube-ai.d ./AI/App/app_x-cube-ai.o ./AI/App/app_x-cube-ai.su ./AI/App/npu_cache.cyclo ./AI/App/npu_cache.d ./AI/App/npu_cache.o ./AI/App/npu_cache.su ./AI/App/npu_init.cyclo ./AI/App/npu_init.d ./AI/App/npu_init.o ./AI/App/npu_init.su

.PHONY: clean-AI-2f-App

