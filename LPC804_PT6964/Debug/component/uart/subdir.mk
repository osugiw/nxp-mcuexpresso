################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_miniusart.c 

C_DEPS += \
./component/uart/fsl_adapter_miniusart.d 

OBJS += \
./component/uart/fsl_adapter_miniusart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC804M101JDH24 -DCPU_LPC804M101JDH24_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\board" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\source" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\drivers" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\CMSIS" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\device" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\component\uart" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_miniusart.d ./component/uart/fsl_adapter_miniusart.o

.PHONY: clean-component-2f-uart

