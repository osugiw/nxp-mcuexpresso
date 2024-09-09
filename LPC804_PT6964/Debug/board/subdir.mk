################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/PT6964.c \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

C_DEPS += \
./board/PT6964.d \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 

OBJS += \
./board/PT6964.o \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC804M101JDH24 -DCPU_LPC804M101JDH24_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\board" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\source" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\drivers" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\CMSIS" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\device" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\component\uart" -I"C:\Users\KDS-LTP-0415\Documents\MCUXpressoIDE_11.6.0_8187\workspace\LPC804_PT6964\utilities" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/PT6964.d ./board/PT6964.o ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/peripherals.d ./board/peripherals.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

