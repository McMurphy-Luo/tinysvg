#include "./MiscParser.h"
#include <cctype>
#include <cassert>

using std::vector;
using std::pair;
using std::size_t;
using std::isspace;

NAMESPACE_BEGIN

namespace // unamed namespace for this file static staff
{
  class NumberListParserStateMachine
  {
    enum class NumberListParserState {
      kInit,
      kBad,
      kComma,
      kNumber
    };

  public:
    NumberListParserStateMachine()
    : current_state_(NumberListParserState::kInit)
    , current_value_(0)
    , all_values_()
    , positive_or_negtive_(1)
    {

    }

  public:
    bool Consume(char next_char);

  private:
    bool ConsumeFirst(char next_char);

  private:
    NumberListParserState current_state_;
    SvgLength current_value_;
    vector<SvgLength> all_values_;
    int positive_or_negtive_; // -1 for negtive 1 for positive
  };

  bool NumberListParserStateMachine::ConsumeFirst(char next_char) {
    assert(current_state_ == NumberListParserState::kInit);
    return false;
  }

  bool NumberListParserStateMachine::Consume(char next_char)
  {
    if (current_state_ == NumberListParserState::kBad) {
      return false;
    }

    if (current_state_ == NumberListParserState::kInit) {
      if (!isdigit(next_char) && next_char != '.' && next_char != '-' && next_char != '+') {
        current_state_ = NumberListParserState::kBad;
        return false;
      }
      if (isdigit(next_char)) {
        current_value_ = next_char - '0';
        return true;
      }
      if (next_char == '.') {
        
      }
      if (next_char == '-') {
        positive_or_negtive_ = -1;
      }
    }

    if (current_state_ == NumberListParserState::kNumber) {

    }

    if (current_state_ == NumberListParserState::kComma) {

    }

    return true;
  }
}

pair<bool, vector<SvgLength>> ParseNumberList(const DomString& from)
{
  size_t byte_count = from.ByteCount();
  SvgLength current_value;
  
  for (size_t index = 0; index < byte_count; ++index) {
    char the_byte = from.ByteAt(index);


    isdigit(the_byte);
    
  }
  return { false, vector<SvgLength>() };
}

NAMESPACE_END