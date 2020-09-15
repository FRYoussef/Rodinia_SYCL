VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia


# turning the work-group size
BLOCK_SIZE=256

# Standard flags
CFLAGS := -std=c++11 -Wall -DBLOCK_SIZE=$(BLOCK_SIZE)

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


ALL: SYCL_particlefilter_single

SYCL_particlefilter_single: ex_particle_SYCL_single_seq.o \
	kernel_find_index.sycl  \
	kernel_likelihood.sycl  \
	kernel_normalize_weights.sycl  \
	kernel_sum.sycl
	$(CC) $(CFLAGS) ex_particle_SYCL_single_seq.o $(LDFLAGS)  -o SYCL_particlefilter_single 

%.o: %.[ch]
	$(CC) $(CFLAGS) $< -c

ex_particle_SYCL_single_seq.o: ex_particle_SYCL_single_seq.cpp
	$(CC) $(CFLAGS) ex_particle_SYCL_single_seq.cpp -c

run: SYCL_particlefilter_single
	./SYCL_particlefilter_single -x 128 -y 128 -z 10 -np 400000

clean:
	rm -f *.o *~ SYCL_particlefilter_single 
