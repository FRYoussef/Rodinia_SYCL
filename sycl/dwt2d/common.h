#ifndef _COMMON_H
#define _COMMON_H

#include <CL/sycl.hpp>

using namespace cl::sycl;
constexpr access::mode sycl_read       = access::mode::read;
constexpr access::mode sycl_write      = access::mode::write;
constexpr access::mode sycl_read_write = access::mode::read_write;
constexpr access::mode sycl_discard_read_write = access::mode::discard_read_write;
constexpr access::mode sycl_discard_write = access::mode::discard_write;
constexpr access::target sycl_global_buffer = access::target::global_buffer;
constexpr access::target sycl_local_buffer = access::target::local;

// NVIDIA device selector
class CUDASelector : public device_selector {
    public:
        int operator()(const device &Device) const override {
            const std::string DriverVersion = Device.get_info<info::device::driver_version>();

            if (Device.is_gpu() && (DriverVersion.find("CUDA") != std::string::npos))
                //std::cout << " CUDA device found " << std::endl;
                return 1;

            return -1;
        }
};

// Intel iGPU
class NEOGPUDeviceSelector : public device_selector {
    public:
        int operator()(const device &Device) const override {
            const std::string DeviceName = Device.get_info<info::device::name>();
            //const std::string DeviceVendor = Device.get_info<info::device::vendor>();
            return Device.is_gpu() && (DeviceName.find("HD Graphics NEO") != std::string::npos);
        }
};

//24-bit multiplication is faster on G80,
//but we must be sure to multiply integers
//only within [-8M, 8M - 1] range
#define IMUL(a, b) __mul24(a, b)

#define DIVANDRND(a, b) ((((a) % (b)) != 0) ? ((a) / (b) + 1) : ((a) / (b)))

#endif
