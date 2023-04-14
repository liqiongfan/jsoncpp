# jsoncpp
A C++ library for interacting with `JSON` & `JSON5`.

`JSON` is a lightweight data-interchange format. It can represent numbers, strings, list, key-value pairs and so on.

`jsoncpp` is a c++ library that allows manipulating JSON values, including serialization and deserialization to and from strings. 

# C Language

C Language press this to obtain: [Zua](https://github.com/liqiongfan/Zua)
<https://github.com/liqiongfan/Zua>

# Requirements
+ `make`
+ `re2c`
+ `bison`
+ `g++` or `clang++` with compile arg: `-std=c++11`


# Build & Test
A simple example for running the jsoncpp is to clone the repository and then open the terminal running the commands: `make`

```shell
$ cd jsoncpp
$ make

output:
{"backwardsCompatible":"with JSON","andIn":["arrays"],"positiveSign":1,"andTrailing":8675309.000000,"leadingDecimalPoint":0.867531,"trailingComma":"in objects","hexadecimal":0xdecaf,"lineBreaks":"Look, Mom! No \\n's!","singleQuotes":"I can use \"double quotes\" here","unquoted":"and you can quote me on that"}
```

# APIs

+ `json fromJson(const std::string &str)`

   decoding json string into json structure, if error occured, jsoncpp will `throw std::string exception`, so you should try catch the exception forever.



+ `std::string toString(bool hex=false)`

    encoding json structure into string, if you set the parameter hex to true, the output string will contain hex value for it's original style. if not it will change into integer for result.


# Data value

+ C++: `long` store json `integer` value.
+ C++: `double` store json `floating` value.
+ C++: struct `boolean` or C++ `true` or `false` store the json `bool` value
+ C++: struct `null` store json `null` value
+ C++: struct `infinity` store the `+Inf` or `-Inf`
+ C++: struct `hex` store the `hex` value
+ C++: `std::vector<json>` store the `array` value
+ C++: `std::unordered_map<std::string, json>` store the `object` value

# Encoding example

```c++
#include <iostream>
#include "json_language.hh"

int main()
{
  json::object obj;
  obj.insert({"program", "jsoncpp"});  
  obj.insert({"version", "v1.0.0"});
  obj.insert({"is_ok", json::boolean(true)});

  json::array vec;
  vec.push_back("c++");
  vec.push_back("linux");
  vec.push_back("make");
  vec.push_back(1);
  vec.push_back(json::boolean(false));
  vec.push_back(json::null());

  obj.insert({"items", vec});

  json p = obj;
  std::cout << p.toString() << std::endl;
  
  return 0;
}

output:
{"items":["c++","linux","make",1,true,null],"is_ok":false,"version":"v1.0.0","program":"jsoncpp"}
```


# Decoding Example

```c++
#include <iostream>
#include "json_language.hh"

int main()
{
    
    std::string str(R"(
{
  // comments
  unquoted: 'and you can quote me on that',
  singleQuotes: 'I can use "double quotes" here',
  lineBreaks: "Look, Mom! \
No \\n's!",
  hexadecimal: 0xdecaf,
  leadingDecimalPoint: .8675309, andTrailing: 8675309.,
  positiveSign: +1,
  trailingComma: 'in objects', andIn: ['arrays',],
  "backwardsCompatible": "with JSON",
}
    )");

    try {
        json v = fromJson(str);
        std::cout << v.toString(true) << std::endl;
    } catch (const std::string &msg) {
        std::cout << msg << std::endl;
    }

    return 0;
}

output:
{"backwardsCompatible":"with JSON","andIn":["arrays"],"positiveSign":1,"andTrailing":8675309.000000,"leadingDecimalPoint":0.867531,"trailingComma":"in objects","hexadecimal":0xdecaf,"lineBreaks":"Look, Mom! No \\n's!","singleQuotes":"I can use \"double quotes\" here","unquoted":"and you can quote me on that"}
```


# Quick way access data

```C++

#include <iostream>
#include "json_language.hh"


  json::array vec;
  vec.push_back("c++");
  vec.push_back("linux");
  vec.push_back("make");
  vec.push_back(1);
  vec.push_back(json::boolean(true));
  vec.push_back(json::null());


  json x = vec;
  if (!x[0].is_not_found()) {
    std::cout << x[0].get_string() << std::endl;
  }


  json::object obj;
  obj.insert({"program", "jsoncpp"});  
  obj.insert({"version", "v1.0.0"});
  obj.insert({"is_ok", false});

  json p = obj;
  if (!p["is_ok"].is_not_found()) {
    std::cout << p["is_ok"].get_bool() << std::endl;
  }
```


# End

Have fun.