#ifndef BELLUM_MACROS_H
#define BELLUM_MACROS_H

#define DELETE_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName& copy) = delete; \
  TypeName operator=(const TypeName& copy) = delete

#define DEFINE_EXCEPTION(Name, What) \
  class Name : public std::exception { \
  public: const char* what() const throw() override { \
    return What; \
  } \
  }

#endif
