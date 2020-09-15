VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia



# Standard flags (profiling is enabled to measure device offloading time)
CFLAGS := -std=c++11 -Wall -DPROFILING

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

SRC = bfs.cpp timer.cc

EXE = bfs

$(EXE):$(SRC)
	$(CC) $(CFLAGS)   $(SRC) -o $(EXE)  $(LDFLAGS) 

run: $(EXE)
	./$(EXE) ../../data/bfs/graph1MW_6.txt
	#./$(EXE) ../../data/bfs/graph4096.txt
	#./$(EXE) ../../data/bfs/graph65536.txt


clean: 
	rm -f $(EXE) $(EXE).linkinfo result*
