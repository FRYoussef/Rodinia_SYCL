##  Rodinia Benchmark Suite in SYCL

The benchmarks can be used for CPU, GPU, FPGA, or other architectures that support OpenCL and SYCL. It was written with GPUs in mind, so targeting other architectures may require heavy optimization.

##  Prerequisites

You will need to install the DPC++ Compiler to support GPU accelerators. It's available here: https://github.com/intel/llvm/blob/sycl/sycl/doc/GetStartedGuide.md


## Compilation

To compile each benchmark with the default settings, navigate to your selected source directory and use the following command:

```bash
make
```

 You can alter compiler settings in the included Makefile. For example, use the Intel iGPU
```bash
make GPU=intel
```

### Debugging, Optimization 

There are also a number of switches that can be set in the makefile. Here is a sample of the control panel at the top of the makefile:

```bash
OPTIMIZE = no
DEBUG    = yes
```
- Optimization enables the -O3 optimization flag
- Debugging enables the -g and/or -DDEBUG flag 

## Running a benchmark

To run a benchmark, use the following command:
```bash
make run
```

Note the dataset, which is needed for certain benchmarks, can be downloaded at http://lava.cs.virginia.edu/Rodinia/download.htm.

## Running all benchmarks

A bash script is provided to attempt to run all the benchmarks:
```bash
./run_all.sh
```

## The original repository
This repository is a fork from https://github.com/zjin-lcf/Rodinia_SYCL
