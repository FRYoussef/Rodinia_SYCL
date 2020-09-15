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


SRC = nearestNeighbor.cpp utils.cpp

EXE = nn

$(EXE): $(SRC) kernel_nn.sycl
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LDFLAGS)

run: $(EXE)
	./$(EXE) filelist.txt -r 5 -lat 30 -lng 90  -t
	
clean: 
	rm -f $(EXE) 
