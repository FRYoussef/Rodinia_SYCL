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


ifdef TESTING 
override TESTING = -DTESTING
endif

ifdef CACHECWLUT
override TESTING = -DCACHECWLUT
endif

EXE = pavle
OBJ =	main.o stats_logger.o cpuencode.o

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(TESTING) $(CACHECWLUT) $(OBJ) -o $(EXE) $(LDFLAGS)

main.o: main.cpp scan.cpp hist.cpp \
	      load_data.h huffTree.h common.h comparison_helpers.h print_helpers.h \
        kernel_pack2.sycl  kernel_vlc_encode.sycl 
	$(CC) $(CFLAGS) -c $< -o $@ 

stats_logger.o: stats_logger.cpp stats_logger.h
	$(CC) $(CFLAGS) -c $< -o $@

cpuencode.o: cpuencode.cpp cpuencode.h print_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE) ../../data/huffman/test1024_H2.206587175259.in

clean:
	rm -f $(OBJ) $(EXE) 
