#ifndef BELLUM_MACROS_H
#define BELLUM_MACROS_H

#define DELETE_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName& copy) = delete; \
  TypeName operator=(const TypeName& copy) = delete

#define DEFINE_EXCEPTION(Name, What) \
  class Name : public std::exception { \
  private: std::string msg_; \
  public: \
  Name() : msg_(What) {} \
  Name(const std::string& msg) : msg_(msg) {  } \
  const char* what() const throw() override { \
      return msg_.c_str(); \
  } \
  }

#endif
