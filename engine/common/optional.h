#ifndef BELLUM_OPTIONAL_H
#define BELLUM_OPTIONAL_H

#include <boost/optional.hpp>

namespace bellum {
  template <typename T>
  using Optional = boost::optional<T>;
}

#endif
