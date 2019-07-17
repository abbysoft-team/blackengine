//
// Created by apopov on 16.07.2019.
//

#include "MacSharedLibrary.h"

namespace black::os {

MacSharedLibrary::MacSharedLibrary(const std::string &name)
    : AbstractSharedLibrary(name) {

}

void MacSharedLibrary::load() {
  auto name = this->name + ".dylib";

  this->handle = dlopen(name.c_str(), RTLD_LAZY);

  if (!this->handle) {
    throw LibraryNotFoundException(name);
  }
}

void MacSharedLibrary::unload() {
  if (this->handle) {
    dlclose(this->handle);
  }
}

void *MacSharedLibrary::getFunctionPointer(std::string name) {
  return dlsym(this->handle, name.c_str());
}
}
