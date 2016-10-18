#include "standalone_application.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace bellum {

void StandaloneApplication::start(int argc, const char* argv[]) {
  logger_ = std::make_unique<Logger>("Bellum");

  int32 width = 480;
  int32 height = 360;
  bool vsync = false;
  double targetUps = 60.0;
  {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("width", po::value<int32>(), "window width")
      ("height", po::value<int32>(), "window height");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("width")) {
      width = vm["width"].as<int32>();
    }

    if (vm.count("height")) {
      height = vm["height"].as<int32>();
    }
  }

  Time::setTargetUps(targetUps);

  window_ = std::make_unique<Window>(width, height);

  logger_->info("Application started");
  is_running_ = true;

  try {
    window_->show();


  } catch (const std::exception& e) {
    logger_->error(e.what());
    std::terminate();
  }
}

void StandaloneApplication::exit() {
  logger_->info("Application exited");
}

}
