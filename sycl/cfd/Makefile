VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia
DUMP        = yes



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

ifeq ($(DUMP),yes)
  CFLAGS += -DOUTPUT
endif

SRC = euler3d.cpp
EXE = euler3d

$(EXE):$(SRC) kernel_compute_flux.sycl  \
               kernel_compute_step_factor.sycl  \
	       kernel_initialize_variables.sycl \
	       kernel_memset.sycl \
	       kernel_time_step.sycl
	$(CC) $(CFLAGS) $(KERNEL_DIM) $(SRC) -o $(EXE) $(LDFLAGS)

run: $(EXE)
	./euler3d ../../data/cfd/fvcorr.domn.097K 
	#./euler3d ../../data/cfd/fvcorr.domn.193K   
	#./euler3d ../../data/cfd/missile.domn.0.2M  


clean: 
	rm -f $(EXE) $(EXE).linkinfo result*  density momentum density_energy
