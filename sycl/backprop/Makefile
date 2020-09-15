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


backprop: backprop_sycl.o backprop.o imagenet.o facetrain.o
	$(CC) $(CFLAGS) backprop_sycl.o backprop.o imagenet.o facetrain.o -o backprop $(LDFLAGS)

%.o: %.[ch]
	$(CC) $(CFLAGS) $< -c

backprop_sycl.o: backprop_sycl.cpp bpnn_adjust_weights.sycl  bpnn_layerforward.sycl
	$(CC) $(CFLAGS) backprop_sycl.cpp -c
	
backprop.o: backprop.c 
	$(CC) $(CFLAGS) backprop.c -c
	
facetrain.o: facetrain.c
	$(CC) $(CFLAGS) facetrain.c -c

imagenet.o: imagenet.c
	$(CC) $(CFLAGS) imagenet.c -c

run: backprop
	./backprop 65536

clean:
	rm -f *.o *~ backprop *.linkinfo
