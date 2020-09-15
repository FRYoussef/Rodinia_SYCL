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


all: kmeans

kmeans: cluster.o getopt.o read_input.o rmse.o kmeans.cpp
	$(CC) $(KERNEL_DIM) $(CFLAGS) $^ -o kmeans $(LDFLAGS)

%.o: %.[ch]
	$(CC) $(CFLAGS) $< -c

cluster.o: cluster.c kmeans.h
	$(CC) $(CFLAGS) cluster.c -c

getopt.o: getopt.c getopt.h
	$(CC) $(CFLAGS) getopt.c -c

read_input.o: read_input.c 
	$(CC) $(CFLAGS) read_input.c -c

rmse.o: rmse.c
	$(CC) $(CFLAGS) rmse.c -c

clean:
	rm -f *.o *~ kmeans *.linkinfo

run: kmeans
	./kmeans -o -i ../../data/kmeans/kdd_cup


