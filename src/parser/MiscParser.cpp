#include "./MiscParser.h"
#include <cctype>

using std::vector;
using std::pair;
using std::size_t;


namespace // unamed namespace for this file static staff
{

  enum class NumberListParserState {
    kInit,
    kBad,
    k
  };

  class NumberListParserStateMachine
  {
  public:
    bool Consume(char next_char);

  private:
    
  };

  bool NumberListParserStateMachine::Consume(char next_char)
  {
    return true;
  }
}

NAMESPACE_BEGIN

pair<bool, vector<SvgLength>> ParseNumberList(const DomString& from)
{
  size_t byte_count = from.ByteCount();
  SvgLength current_value;
  
  for (size_t index = 0; index < byte_count; ++index) {
    char the_byte = from.ByteAt(index);


    isdigit(the_byte);
    
  }
}

NAMESPACE_END