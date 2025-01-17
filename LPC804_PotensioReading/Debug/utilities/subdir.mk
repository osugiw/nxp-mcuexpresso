################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC804M101JDH24 -DCPU_LPC804M101JDH24_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\board" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\source" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\drivers" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\CMSIS" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\device" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\component\uart" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PotensioReading\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

