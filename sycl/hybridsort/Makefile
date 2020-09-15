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
  CFLAGS += -g -DDEBUG
endif

# Optimization Flags
ifeq ($(OPTIMIZE),yes)
  CFLAGS += -O3
endif

ifeq ($(DEVICE),gpu)
  CFLAGS +=-DUSE_GPU
endif


ifdef VERIFY
override VERIFY = -DVERIFY
endif

ifdef OUTPUT
override OUTPUT = -DOUTPUT
endif

ifdef TIMER
override TIMER = -DTIMER
endif

hybridsort: hybridsort.c bucketsort.o mergesort.o
	$(CC) $(CFLAGS) -o hybridsort $(VERIFY) $(OUTPUT) $(TIMER) \
		hybridsort.c bucketsort.o mergesort.o $(LDFLAGS)

bucketsort.o: bucketsort.c \
	kernel_bucketprefix.sycl \
	kernel_histogram.sycl \
	kernel_bucketcount.sycl \
       	kernel_bucketsort.sycl  
	$(CC) $(CFLAGS) -o bucketsort.o -c bucketsort.c 

mergesort.o: mergesort.c mergesort.h kernel_mergeSortPass.sycl
	$(CC) $(CFLAGS) -o mergesort.o -c mergesort.c 

run: hybridsort
	./hybridsort r

clean:
	rm -f  bucketsort.o mergesort.o hybridsort
