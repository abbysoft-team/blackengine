//
// Created by apopov on 16.07.2019.
//

#ifndef BLACKENGINE_MACSHAREDLIBRARY_H
#define BLACKENGINE_MACSHAREDLIBRARY_H

#include <PlatformHeaders.h>
#include <plugins/AbstractSharedLibrary.h>

namespace black::os {
/**
 * MacOS dynamic library class
 */
class MacSharedLibrary : public AbstractSharedLibrary {
private:
  void *handle;

public:
  explicit MacSharedLibrary(const std::string &name);

  void load() override;
  void unload() override;

private:
  void *getFunctionPointer(std::string name) override;
};
}

#endif //BLACKENGINE_MACSHAREDLIBRARY_H
