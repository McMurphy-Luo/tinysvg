#include "./MiscParser.h"
#include <cctype>

using std::vector;
using std::pair;
using std::size_t;
using std::isspace;


namespace // unamed namespace for this file static staff
{
  class NumberListParserStateMachine
  {
    enum class NumberListParserState {
      kInit,
      kBad,
      k
    };

  public:
    bool Consume(char next_char);

  private:
    NumberListParserState current_state_;
  };

  bool NumberListParserStateMachine::Consume(char next_char)
  {
    if (current_state_ == NumberListParserState::kBad) {
      return false;
    }

    if (current_state_ == NumberListParserState::kInit) {
      
    }
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