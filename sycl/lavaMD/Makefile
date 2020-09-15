VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia



# Standard flags
CFLAGS := -std=c++11 -Wall

# Linker flags
LDFLAGS = -lm

# Intel DPC++ Compiler
ifneq (,$(findstring intel,$(VENDOR)))
  CC = clang++
  CFLAGS += -fsycl -fsycl-unnamed-lambda
  LDFLAGS +=
endif

# Flags for nvidia gpu
ifneq (,$(findstring nvidia,$(GPU)))
  CFLAGS += -fsycl-targets=nvptx64-nvidia-cuda-sycldevice -DUSE_NVIDIA
endif

# Debug Flags
ifeq ($(DEBUG),yes)
	CFLAGS += -g  -DOUTPUT
endif

# Optimization Flags
ifeq ($(OPTIMIZE),yes)
	CFLAGS += -O3
endif

ifeq ($(DEVICE),gpu)
	CFLAGS +=-DUSE_GPU
endif


# link objects together
lavaMD:	main.o \
	./kernel/kernel_gpu_opencl_wrapper.o \
	./util/num/num.o \
	./util/timer/timer.o 
	$(CC) $(CFLAGS) main.o \
		./kernel/kernel_gpu_opencl_wrapper.o \
		./util/num/num.o \
		./util/timer/timer.o \
		-lm \
		$(LDFLAGS) \
		-o lavaMD

# compile function files into objects
main.o:	main.h main.c 
	$(CC)	$(OUTPUT) main.c \
		-c \
		-o main.o \
		-O3

./kernel/kernel_gpu_opencl_wrapper.o:	./kernel/kernel_gpu_opencl_wrapper.h \
	./kernel/kernel_gpu_opencl_wrapper.c \
	./kernel/kernel.sycl 
	$(CC) $(CFLAGS)	$(KERNEL_DIM) ./kernel/kernel_gpu_opencl_wrapper.c \
		-c \
		-o ./kernel/kernel_gpu_opencl_wrapper.o \
		-O3

./util/num/num.o:	./util/num/num.h ./util/num/num.c
	$(CC) ./util/num/num.c \
		-c \
		-o ./util/num/num.o \
		-O3

./util/timer/timer.o:	./util/timer/timer.h ./util/timer/timer.c
	$(CC) ./util/timer/timer.c \
		-c \
		-o ./util/timer/timer.o \
		-O3

run: lavaMD
	./lavaMD -boxes1d 10

# delete all object and executable files
clean:
	rm *.o lavaMD \
		./kernel/*.o \
		./util/num/*.o \
		./util/timer/*.o \
