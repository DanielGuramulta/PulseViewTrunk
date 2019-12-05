#include "pulseviewtrunk.h"
#include <QApplication>
#include <pv/mainwindow.hpp>
#include <pv/devicemanager.hpp>
#include <pv/devices/device.hpp>
#include <libsigrokcxx/libsigrokcxx.hpp>
#include <QDebug>
#include <QPushButton>
#include <pv/toolbars/mainbar.hpp>

#include "detail/digitaldevice.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	auto context = sigrok::Context::create();

	pv::DeviceManager d(context, "", false);
	pv::MainWindow m(d);
    auto s = m.add_session();

    std::map<std::string, Glib::VariantBase> options;

    options["numchannels"] = Glib::Variant<gint32>(
                g_variant_new_int32(16),true);

    std::string format = "binary";

    const map<string, shared_ptr<sigrok::InputFormat>> formats = context->input_formats();
    const auto iter = find_if(formats.begin(), formats.end(),
                [&](const pair<string, shared_ptr<sigrok::InputFormat> > f) {
                    return f.first == format; });
    if (iter == formats.end()) {
        qDebug() << "Unexpected input format: ";
    }

    std::shared_ptr<sigrok::InputFormat> input_format = (*iter).second;

    shared_ptr<pv::devices::Device> device(new DigitalDevice(context,
                                  input_format,
                                  options,
                                  nullptr, 0));



    s->set_device(device); // Custom data device!

	m.show();

//    m.get_active_view()->hide();
//    m.get_active_view()->show();
    //    m.get_active_view()->show();
//    m.get_active_view()->show();
    QPushButton *btn = new QPushButton("Toogle ToolBar");
    btn->show();
    int j = 1;
    QObject::connect(btn, &QPushButton::clicked, [&](){
        if (j & 1) {
//                m.get_active_view()->hide();
                s->main_bar()->hide();
                for (auto &base: s->signalbases()) {
                    base->set_enabled(false);
                }
        } else {
//                m.get_active_view()->show();
                s->main_bar()->show();
                for (auto &base: s->signalbases()) {
                    base->set_enabled(true);
                }
        }
        ++j;
    });


	return a.exec();
}
