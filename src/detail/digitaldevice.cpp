#include "digitaldevice.h"

DigitalDevice::DigitalDevice(
    const std::shared_ptr<sigrok::Context> &/*context*/,
    const std::shared_ptr<sigrok::InputFormat> &/*format*/,
		const std::map<std::__cxx11::string, Glib::VariantBase> &/*options*/,
		short */*buffer*/, uint32_t /*size*/) {}

DigitalDevice::~DigitalDevice()
{

}

DigitalDevice::DigitalDevice(const DigitalDevice &/*other*/)
{

}

DigitalDevice &DigitalDevice::operator=(const DigitalDevice &/*other*/)
{

}

DigitalDevice::DigitalDevice(DigitalDevice &&/*other*/)
{

}

DigitalDevice &DigitalDevice::operator=(DigitalDevice &&/*other*/)
{

}

std::string DigitalDevice::full_name() const
{

}

std::string DigitalDevice::display_name(const pv::DeviceManager &/*device*/) const
{

}

void DigitalDevice::open()
{

}

void DigitalDevice::close()
{

}

void DigitalDevice::start()
{

}

void DigitalDevice::run()
{

}

void DigitalDevice::stop()
{

}
