############# Makefile for APSP ##############

# Const environments
NVCC=nvcc
CPPFLAGS= -O3 -std=c++11

# Define paths
OBJS := \
./main.o \
./lib/cuda/cuda_ssp.o \
./lib/ssp.o

CPP_SRCS := \
main.cpp \
lib/ssp.cpp

CPP_DEPS := \
./main.d \
./lib/ssp.d

CU_SRCS := \
lib/cuda/cuda_ssp.cu

CU_DEPS := \
./lib/cuda/cuda_ssp.d


# Build cpp files in root folder
%.o: %.cpp
	@echo 'NVCC compiler building file: $<'
	$(NVCC) $(CPPFLAGS) -gencode arch=compute_61,code=sm_61  -odir "." -M -o "$(@:%.o=%.d)" "$<"
	$(NVCC) $(CPPFLAGS) --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Building cu files lib/cuda
lib/cuda/%.o: lib/cuda/%.cu
	@echo 'NVCC compiler building file: $<'
	$(NVCC) $(CPPFLAGS) -gencode arch=compute_61,code=sm_61  -odir "lib/cuda" -M -o "$(@:%.o=%.d)" "$<"
	$(NVCC) $(CPPFLAGS) --compile --relocatable-device-code=false -gencode arch=compute_61,code=compute_61 -gencode arch=compute_61,code=sm_61  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# Build cpp files in lib
lib/%.o: lib/%.cpp
	@echo 'NVCC compiler building file: $<'
	$(NVCC) $(CPPFLAGS) -gencode arch=compute_61,code=sm_61  -odir "lib" -M -o "$(@:%.o=%.d)" "$<"
	$(NVCC) $(CPPFLAGS) --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


# All Target
all: stochastic_shortest_path

stochastic_shortest_path: $(OBJS) $(USER_OBJS)
	@echo 'Linker building target: $@'
	$(NVCC) --cudart static --relocatable-device-code=false -gencode arch=compute_61,code=compute_61 -gencode arch=compute_61,code=sm_61 -link -o  "stochastic_shortest_path" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'

clean:
	-rm -fr $(OBJS) $(CU_DEPS) $(CPP_DEPS) stochastic_shortest_path
	-@echo ' '
