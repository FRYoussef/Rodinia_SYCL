#include <CL/sycl.hpp>

using namespace cl::sycl;

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