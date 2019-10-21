#ifndef DIGITAL_DEVICE_HPP
#define DIGITAL_DEVICE_HPP

#include <atomic>

#include <libsigrokcxx/libsigrokcxx.hpp>

#include <pv/devices/device.hpp>

class DigitalDevice : public pv::devices::Device
{

public:
        DigitalDevice(const std::shared_ptr<sigrok::Context> &context,
                      const std::shared_ptr<sigrok::InputFormat> &format,
                      const std::map<std::string, Glib::VariantBase> &options,
                      short *buffer, uint32_t size);
        ~DigitalDevice();

        // Copy
        DigitalDevice(const DigitalDevice &other);
        DigitalDevice &operator=(const DigitalDevice &other);

        // Move
        DigitalDevice(DigitalDevice &&other);
        DigitalDevice &operator=(DigitalDevice &&other);

public:
	std::string full_name() const override;
	std::string display_name(const pv::DeviceManager &device) const override;

	void open() override;
	void close() override;
	void start() override;
	void run() override;
	void stop() override;

private:
        const std::shared_ptr<sigrok::Context> m_context;
        const std::shared_ptr<sigrok::InputFormat> m_format;

        std::map<std::string, Glib::VariantBase> m_options;

        short *m_buffer;
        uint32_t m_size;

        std::shared_ptr<sigrok::Input> m_input;
};


#endif // DIGITAL_DEVICE_HPP
