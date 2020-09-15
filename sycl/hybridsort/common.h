#ifndef __COMMON
#define __COMMON
#include <CL/sycl.hpp>

using namespace cl::sycl;
constexpr access::mode sycl_read       = access::mode::read;
constexpr access::mode sycl_write      = access::mode::write;
constexpr access::mode sycl_read_write = access::mode::read_write;
constexpr access::mode sycl_atomic     = access::mode::atomic;
constexpr access::mode sycl_discard_read_write = access::mode::discard_read_write;
constexpr access::mode sycl_discard_write = access::mode::discard_write;

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

#endif
