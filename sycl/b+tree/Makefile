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
  CFLAGS += -g  
endif

# Optimization Flags
ifeq ($(OPTIMIZE),yes)
  CFLAGS += -O3
endif

ifeq ($(DEVICE),gpu)
  CFLAGS +=-DUSE_GPU
endif


b+tree.out:	./main.o \
		./kernel/kernel_gpu_opencl_wrapper.o \
		./kernel/kernel_gpu_opencl_wrapper_2.o \
		./util/timer/timer.o \
		./util/num/num.o 
	$(CC) $(CFLAGS) ./main.o \
			./kernel/kernel_gpu_opencl_wrapper.o \
			./kernel/kernel_gpu_opencl_wrapper_2.o \
			./util/timer/timer.o \
			./util/num/num.o \
			$(LDFLAGS) \
	                -o b+tree.out
# ========================================================================================================================================================================================================200
#	OBJECTS (COMPILE SOURCE FILES INTO OBJECTS)
# ========================================================================================================================================================================================================200

# ======================================================================================================================================================150
#	MAIN FUNCTION
# ======================================================================================================================================================150

main.o:	./common.h \
	./main.c
	$(CC) $(CFLAGS) $(KERNEL_DIM) ./main.c \
		-c \
		-o ./main.o

# ======================================================================================================================================================150
#	KERNELS
# ======================================================================================================================================================150

./kernel/kernel_gpu_opencl_wrapper.o:	./common.h \
	./kernel/kernel_gpu_opencl_wrapper.h \
	./kernel/kernel_gpu_opencl_wrapper.c \
	./kernel/findK.sycl
	$(CC) $(CFLAGS)	$(KERNEL_DIM) ./kernel/kernel_gpu_opencl_wrapper.c \
		-c \
		-o ./kernel/kernel_gpu_opencl_wrapper.o

./kernel/kernel_gpu_opencl_wrapper_2.o:	./common.h \
	./kernel/kernel_gpu_opencl_wrapper_2.h \
	./kernel/kernel_gpu_opencl_wrapper_2.c \
	./kernel/findRangeK.sycl
	$(CC) $(CFLAGS)	$(KERNEL_DIM) ./kernel/kernel_gpu_opencl_wrapper_2.c \
		-c \
		-o ./kernel/kernel_gpu_opencl_wrapper_2.o 

# ======================================================================================================================================================150
#	UTILITIES
# ======================================================================================================================================================150

./util/timer/timer.o:	./common.h \
	./util/timer/timer.h \
	./util/timer/timer.c
	$(CC)	./util/timer/timer.c \
		-c \
		-o ./util/timer/timer.o \
		-O3

./util/num/num.o:	./common.h \
	./util/num/num.h \
	./util/num/num.c
	$(CC)	./util/num/num.c \
		-c \
		-o ./util/num/num.o \
		-O3

# ======================================================================================================================================================150
#	END
# ======================================================================================================================================================150
#
run: b+tree.out
	./b+tree.out file ../../data/b+tree/mil.txt command ../../data/b+tree/command.txt

# ========================================================================================================================================================================================================200
#	DELETE
# ========================================================================================================================================================================================================200

clean:
	rm -f	*.o *.out \
		./kernel/*.o \
		./util/timer/*.o \
		./util/num/*.o \
		output.txt
	# ========================================================================================================================================================================================================200
	#	END
	# ========================================================================================================================================================================================================200
