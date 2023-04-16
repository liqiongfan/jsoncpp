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
  leadingDecimalPoint: .8675309, /*Hello comments*/andTrailing: 8675309.,
  positiveSign: +1,
  trailingComma: 'in objects', andIn: ['arrays',],
  "backwardsCompatible": 'with JSON',
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