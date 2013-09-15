-include sources.mk
-include irtu/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

ifeq ($(OS),Windows_NT)
    BUILD_PATH := ../win_build
	RM := del /Q
else
    BUILD_PATH := ../linux_build
	RM := rm -rf
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Infinite-Reality.exe

# Tool invocations
Infinite-Reality.exe: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	g++ -L"../include" -L"../src" -L"../libs" -o "$(BUILD_PATH)/Infinite-Reality.exe" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) "$(BUILD_PATH)Infinite Reality.exe"
	-@echo ' '

.PHONY: all clean dependents

