CPP_SRCS += \
../src/irtu/IRTU.cpp \
../src/irtu/IRTUByte.cpp \
../src/irtu/IRTUDouble.cpp \
../src/irtu/IRTUElement.cpp \
../src/irtu/IRTUFloat.cpp \
../src/irtu/IRTUInt.cpp \
../src/irtu/IRTUList.cpp \
../src/irtu/IRTULong.cpp \
../src/irtu/IRTUObject.cpp \
../src/irtu/IRTUShort.cpp 

OBJS += \
./irtu/IRTU.o \
./irtu/IRTUByte.o \
./irtu/IRTUDouble.o \
./irtu/IRTUElement.o \
./irtu/IRTUFloat.o \
./irtu/IRTUInt.o \
./irtu/IRTUList.o \
./irtu/IRTULong.o \
./irtu/IRTUObject.o \
./irtu/IRTUShort.o 

CPP_DEPS += \
./irtu/IRTU.d \
./irtu/IRTUByte.d \
./irtu/IRTUDouble.d \
./irtu/IRTUElement.d \
./irtu/IRTUFloat.d \
./irtu/IRTUInt.d \
./irtu/IRTUList.d \
./irtu/IRTULong.d \
./irtu/IRTUObject.d \
./irtu/IRTUShort.d 


# Each subdirectory must supply rules for building sources it contributes
irtu/IRTU.o: ../src/irtu/IRTU.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUByte.o: ../src/irtu/IRTUByte.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUDouble.o: ../src/irtu/IRTUDouble.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUElement.o: ../src/irtu/IRTUElement.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUFloat.o: ../src/irtu/IRTUFloat.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUInt.o:../src/irtu/IRTUInt.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUList.o: ../src/irtu/IRTUList.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTULong.o: ../src/irtu/IRTULong.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUObject.o: ../src/irtu/IRTUObject.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

irtu/IRTUShort.o: ../src/irtu/IRTUShort.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


