#ifndef __BELLUM_RESOURCE_H__
#define __BELLUM_RESOURCE_H__

namespace bellum {

class Resource {
  friend class ResourceLoader;

protected:
  virtual void dispose() = 0;
};

}

#endif
