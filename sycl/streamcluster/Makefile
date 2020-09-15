VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia



# Standard flags
CFLAGS := -std=c++17 -Wall #-DPROFILE_TMP

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

# Enable checksum and output file
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

SRC = streamcluster.cpp
EXE = streamcluster

$(EXE):$(SRC) kernel.sycl
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LDFLAGS)	

run: $(EXE)
	./$(EXE) 10 20 256 65536 65536 1000 none output.txt 1 

clean: 
	rm -f $(EXE) $(EXE).linkinfo result*
