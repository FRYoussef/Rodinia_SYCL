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



EXE = hotspot

$(EXE): hotspot.cpp hotspot.h kernel_hotspot.sycl
	$(CC) $(CFLAGS) -o $(EXE) hotspot.cpp $(LDFLAGS)

run: $(EXE)
	./$(EXE) 512 2 2 ../../data/hotspot/temp_512 ../../data/hotspot/power_512 output_512.out
	#./$(EXE) 64 2 2 ../../data/hotspot/temp_64 ../../data/hotspot/power_64 output_64.out

clean:
	rm -f $(EXE)
