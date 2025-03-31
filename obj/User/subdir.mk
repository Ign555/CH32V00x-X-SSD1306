################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/SSD1306.c \
../User/ch32v00x_it.c \
../User/example.c \
../User/system_ch32v00x.c 

C_DEPS += \
./User/SSD1306.d \
./User/ch32v00x_it.d \
./User/example.d \
./User/system_ch32v00x.d 

OBJS += \
./User/SSD1306.o \
./User/ch32v00x_it.o \
./User/example.o \
./User/system_ch32v00x.o 



# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/netwo/Documents/GitHub/CH32V003F4P6-X-SSD1306/Debug" -I"c:/Users/netwo/Documents/GitHub/CH32V003F4P6-X-SSD1306/Core" -I"c:/Users/netwo/Documents/GitHub/CH32V003F4P6-X-SSD1306/User" -I"c:/Users/netwo/Documents/GitHub/CH32V003F4P6-X-SSD1306/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
