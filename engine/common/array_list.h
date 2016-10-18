#ifndef BELLUM_ARRAY_LIST_H
#define BELLUM_ARRAY_LIST_H

#include <vector>
#include "../common/common.h"

namespace bellum {

template<typename T>
class ArrayList {
private:
  std::vector<T> vector_;
public:
  ArrayList() {}

  ArrayList(std::initializer_list<T> list)
    : vector_(list) {}

  ArrayList(const std::vector& vector)
    : vector_(vector) {}

  ArrayList(const ArrayList& arrayList)
    : vector_(arrayList.vector_) {}
};

}

#endif
