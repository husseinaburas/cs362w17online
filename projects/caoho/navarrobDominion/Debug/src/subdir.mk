################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cardtest1.c \
../src/cardtest2.c \
../src/cardtest3.c \
../src/cardtest4.c \
../src/dominion.c \
../src/interface.c \
../src/playdom.c \
../src/player.c \
../src/randomtestadventurer.c \
../src/randomtestcard1.c \
../src/randomtestcard2.c \
../src/rngs.c \
../src/rt.c \
../src/testDrawCard.c \
../src/unittest1.c \
../src/unittest2.c \
../src/unittest3.c \
../src/unittest4.c 

OBJS += \
./src/cardtest1.o \
./src/cardtest2.o \
./src/cardtest3.o \
./src/cardtest4.o \
./src/dominion.o \
./src/interface.o \
./src/playdom.o \
./src/player.o \
./src/randomtestadventurer.o \
./src/randomtestcard1.o \
./src/randomtestcard2.o \
./src/rngs.o \
./src/rt.o \
./src/testDrawCard.o \
./src/unittest1.o \
./src/unittest2.o \
./src/unittest3.o \
./src/unittest4.o 

C_DEPS += \
./src/cardtest1.d \
./src/cardtest2.d \
./src/cardtest3.d \
./src/cardtest4.d \
./src/dominion.d \
./src/interface.d \
./src/playdom.d \
./src/player.d \
./src/randomtestadventurer.d \
./src/randomtestcard1.d \
./src/randomtestcard2.d \
./src/rngs.d \
./src/rt.d \
./src/testDrawCard.d \
./src/unittest1.d \
./src/unittest2.d \
./src/unittest3.d \
./src/unittest4.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


