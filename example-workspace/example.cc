#include <fcntl.h>
#include <unistd.h>

#include <ostream>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"
#include "foo/bar.pb.h"
#include "foo/bar.pb.validate.h"

int main(int nargs, char** args) {
  if (nargs <= 1) {
    std::cout << "No inputs provided; exiting" << std::endl;
    return 0;
  }

  int success_count = 0;
  for (int i = 1; i < nargs; ++i) {
    pgv::example::foo::Bars bars;
    auto filename = args[i];
    auto fd = ::open(filename, O_RDONLY);
    if (fd < 0) {
      std::cerr << "Failed to open file '" << filename << "'" << std::endl;
      continue;
    }
    google::protobuf::io::FileInputStream input(fd);
    input.SetCloseOnDelete(true);

    if (!google::protobuf::TextFormat::Parse(&input, &bars)) {
      std::cerr << "Failed to parse file '" << filename << "' as a "
                << bars.GetDescriptor()->full_name() << " textproto" << std::endl;
      return 3;
    }

    pgv::ValidationMsg error_message;
    if (Validate(bars, &error_message)) {
      std::cout << "Successfully validated file '" << filename << "' as a "
                << bars.GetDescriptor()->full_name() << " textproto"
                << std::endl;
      ++success_count;
    } else {
      std::cerr << "Failed to validate file '" << filename << "' as a "
                << bars.GetDescriptor()->full_name()
                << " textproto: " << error_message << std::endl;
    }
  }

  int failure_count = nargs - 1 - success_count;
  if (failure_count != 0) {
    std::cerr << "Failed to validate " << failure_count << " file"
              << (failure_count == 1 ? "" : "s") << std::endl;
    return 1;
  }
  return 0;
}