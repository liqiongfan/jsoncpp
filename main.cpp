#include <iostream>
#include "json_language.hh"

int main()
{
  json::object obj;
  obj.insert({"program", "jsoncpp"});  
  obj.insert({"version", "v1.0.0"});
  obj.insert({"is_ok", false});

  json::array vec;
  vec.push_back("c++");
  vec.push_back("linux");
  vec.push_back("make");
  vec.push_back(1);
  vec.push_back(json::boolean(true));
  vec.push_back(json::null());

  obj.insert({"items", vec});

  json p = obj;
  std::cout << p.toString() << std::endl;
  return 0;
}
