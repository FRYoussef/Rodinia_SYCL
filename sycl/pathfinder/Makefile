VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia
OUTPUT      = no



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

ifeq ($(OUTPUT),yes)
  CFLAGS += -DBENCH_PRINT
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


# link objects(binaries) together
pathfinder: main.o 
	$(CC) $(CFLAGS) main.o $(LDFLAGS) -o pathfinder

# compile main function file into object (binary)
main.o: main.cpp  kernel.sycl
	$(CC) $(CFLAGS) main.cpp -c -o main.o

run: pathfinder
	./pathfinder 100000 100 20

clean:
	@rm -f pathfinder *.o *.out *~ *\#
