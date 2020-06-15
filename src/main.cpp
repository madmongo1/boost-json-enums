#include "config.hpp"
#include "explain.hpp"
#include <boost/json.hpp>
#include <boost/optional.hpp>
#include <iostream>

#define ENABLE_ENUM_IO(Enum)                                                   \
  inline void tag_invoke(boost::json::value_from_tag, boost::json::value &jv,  \
                         Enum f) {                                             \
    auto sv = to_string(f);                                                    \
    jv = boost::json::string(sv.begin(), sv.end());                            \
  }                                                                            \
                                                                               \
  Enum tag_invoke(boost::json::value_to_tag<Enum>,                             \
                  boost::json::value const &jv) {                              \
    auto s = jv.as_string();                                                   \
    auto opt = from_string(s);                                                 \
    if (!opt)                                                                  \
      throw std::invalid_argument(s.c_str());                                  \
    return *opt;                                                               \
  }

namespace program {

enum Fruit { Apple, Pear };

boost::string_view to_string(Fruit f) {
  switch (f) {
  case Apple:
    return "Apple";
  case Pear:
    return "Pear";
  }
  return "Unknown";
}

boost::optional<Fruit> from_string(boost::string_view sv) {
  boost::optional<Fruit> result;
  if (sv == "Apple")
    result = Apple;
  else if (sv == "Pear")
    result = Pear;
  return result;
}

ENABLE_ENUM_IO(Fruit)

int run() {

  auto f = Fruit::Apple;
  auto j = boost::json::value{{"fruit", f}};
  std::cout << j << std::endl;
  f = boost::json::value_to<Fruit>(j.as_object().at("fruit"));
  std::cout << to_string(f) << std::endl;

  return 0;
}
} // namespace program

int main() {
  try {
    return program::run();
  } catch (...) {
    std::cerr << program::explain() << std::endl;
    return 127;
  }
}