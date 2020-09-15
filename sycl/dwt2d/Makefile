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
  CFLAGS += -g -DOUTPUT -DDEBUG
endif

# Optimization Flags
ifeq ($(OPTIMIZE),yes)
  CFLAGS += -O3
endif

ifeq ($(DEVICE),gpu)
  CFLAGS +=-DUSE_GPU
endif


dwt2d: main.cpp \
       kernel_CopySrcToComponent.sycl \
       kernel_CopySrcToComponents.sycl \
       kernel_fdwt53.sycl
	$(CC) $(CFLAGS) -o dwt2d \
		main.cpp \
		$(LDFLAGS)
		
run: dwt2d
	./dwt2d 192.bmp -d 192x192 -f -5 -l 3
	./dwt2d rgb.bmp -d 1024x1024 -f -5 -l 3

clean:	
	rm -rf *.o dwt2d
	rm -rf *.bmp.dwt.*

