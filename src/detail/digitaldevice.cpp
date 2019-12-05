#include "digitaldevice.h"
#include <QDebug>

DigitalDevice::DigitalDevice(
    const std::shared_ptr<sigrok::Context> & context,
    const std::shared_ptr<sigrok::InputFormat> & format,
    const std::map<std::__cxx11::string, Glib::VariantBase> & options,
    short * buffer, uint32_t size): m_context(context), m_format(format),
        m_options(options), m_buffer(buffer), m_size(size), m_device_open(false) {
    qDebug() << "Digital Device created!";
}

std::string DigitalDevice::full_name() const
{
    return "digital device";
}

std::string DigitalDevice::display_name(const pv::DeviceManager & /*device*/) const
{
    return "digital device";
}

void DigitalDevice::open()
{
       if (session_) {
           close();
       } else {
           session_ = m_context->create_session();
       }

       m_input = m_format->create_input(m_options);

       short * data = new short[2000000];
       for (int i = 0; i < 2000000; ++i) {
           data[i] = i & 1;
       }

//       m_input->send(m_buffer, m_size);
       m_input->send(data, 2000000);

       try {
           device_ = m_input->device();
       } catch (sigrok::Error& e) {
           throw e;
       }

       m_input->end();

       session_->add_device(device_);
}

void DigitalDevice::close()
{
    if (session_)
        session_->remove_devices();
}

void DigitalDevice::start()
{

}

void DigitalDevice::run()
{

    short * data = new short[2000000];
    for (int i = 0; i < 2000000; ++i) {
        data[i] = i;
    }

//       m_input->send(m_buffer, m_size);
    m_input->send(data, 2000000);

    delete[] data;

    m_input->end();

}

void DigitalDevice::stop()
{

}

