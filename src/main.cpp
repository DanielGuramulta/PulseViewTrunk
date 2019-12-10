#include "pulseviewtrunk.h"
#include <QApplication>
#include <pv/mainwindow.hpp>
#include <pv/devicemanager.hpp>
#include <pv/devices/device.hpp>
#include <libsigrokcxx/libsigrokcxx.hpp>
#include <QDebug>
#include <QPushButton>
#include <pv/toolbars/mainbar.hpp>
#include <pv/views/trace/view.hpp>
#include <pv/views/trace/ruler.hpp>

#include "detail/digitaldevice.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	auto context = sigrok::Context::create();

    // Initialise libsigrokdecode
    if (srd_init(nullptr) != SRD_OK) {
        qDebug() << "ERROR: libsigrokdecode init failed.";
    }

    // Load the protocol decoders
    srd_decoder_load_all();

    // create pv::DeviceManager
	pv::DeviceManager d(context, "", false);

    // create pv::MainWindow
	pv::MainWindow m(d);

    // add session
    auto s = m.add_session();


    // search for input format
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

    // end format search

    // create custom device
    shared_ptr<pv::devices::Device> device(new DigitalDevice(context,
                                  input_format,
                                  options,
                                  nullptr, 0)); // -> (nullptr, 0) <-> (buffer, buffer_size)



    s->set_device(device); // Custom data device!

    // end create custom device

    // show pv::MainWindow
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
//                s->main_bar()->hide();
                int count = 0;
                for (auto &base: s->signalbases()) {
                    if (count & 1)
                        base->set_enabled(false);
                    count ++;
                }
                auto active_view = m.get_active_view();
                auto ViewInUse = std::dynamic_pointer_cast<pv::views::trace::View>(active_view);
                ViewInUse->show_cursors(false);
                const_cast<pv::views::trace::Ruler *>(ViewInUse->ruler())->hide();
        } else {
//                m.get_active_view()->show();
//                s->main_bar()->show();
                int count = 0;
                for (auto &base: s->signalbases()) {
                    if (count & 1)
                        base->set_enabled(true);
                    count++;
                }
                auto active_view = m.get_active_view();
                auto ViewInUse = std::dynamic_pointer_cast<pv::views::trace::View>(active_view);
                ViewInUse->show_cursors(true);
                const_cast<pv::views::trace::Ruler *>(ViewInUse->ruler())->show();

        }
        ++j;
    });


	return a.exec();
}
