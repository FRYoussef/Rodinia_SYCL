VENDOR      = intel
OPTIMIZE    = yes
DEBUG       = no
GPU         = nvidia

# Matrix library path
MATRIX_DIR = ./meschach_lib

# Standard flags
CFLAGS := -std=c++11 -Wall -I$(MATRIX_DIR)

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

ifeq ($(DEBUG),yes)
  CFLAGS += -g  
  OUTPUT = -DOUTPUT
endif

# Optimization Flags
ifeq ($(OPTIMIZE),yes)
  CFLAGS += -O3
endif

ifeq ($(DEVICE),gpu)
  CFLAGS +=-DUSE_GPU
endif



leukocyte: detect_main.o \
	avilib.o \
	track_ellipse.o \
	track_ellipse_sycl.o \
	find_ellipse.o \
	misc_math.o \
	helper.o \
	$(MATRIX_DIR)/meschach.a
	$(CC) $(CFLAGS) -o leukocyte avilib.o \
		track_ellipse.o \
		track_ellipse_sycl.o \
		find_ellipse.o \
		misc_math.o \
		detect_main.o \
		helper.o \
		$(MATRIX_DIR)/meschach.a $(LDFLAGS)

%.o: %.[c]
	$(CC) $(OUTPUT) $(CFLAGS) $< -c

detect_main.o: detect_main.c \
               kernel_GICOV.sycl kernel_dilated.sycl \
               track_ellipse.h helper.h misc_math.h common.h

find_ellipse.o: find_ellipse.c find_ellipse.h avilib.h misc_math.h

track_ellipse.o: track_ellipse.c find_ellipse.h $(MATRIX_DIR)/matrix.h avilib.h helper.h

track_ellipse_sycl.o: track_ellipse_sycl.c track_ellipse.h common.h kernel_IMGVF.sycl


# Use the sycl compiler to build the library
# Cleanup everything, then clean everything except the static library
$(MATRIX_DIR)/meschach.a:
	cd $(MATRIX_DIR); make cleanup; make all CC=$(CC); make clean

run: leukocyte
	./leukocyte ../../data/leukocyte/testfile.avi 10

clean:
	rm -f *.o *~ leukocyte 
	cd $(MATRIX_DIR); make cleanup
