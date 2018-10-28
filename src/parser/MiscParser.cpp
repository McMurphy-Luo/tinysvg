#include "./MiscParser.h"

#include <cctype>
#include <cassert>

#include "../common/Convert.h"

using std::vector;
using std::pair;
using std::size_t;
using std::isspace;
using std::make_pair;

NAMESPACE_BEGIN

namespace
{
  class NumericListParser
  {
  public:
    explicit NumericListParser(const DomString& source)
    : source_(source)
    , result_()
    , succeeded_(true)
    , look_forward_(source.Data())
    , c_string_end_(c_string_end_ + source.ByteCount())
    , current_numeric_begin_(look_forward_)
    {
      
    }

    pair<bool, vector<SvgLength>> GetResult() {
      Consume();
      return make_pair(succeeded_, result_);
    }

  private:
    void ConsumeWhiteSpaceAndComma();
    DomString ConsumeNumber();
    void CheckAndPushSingleUnit(const DomString& suppose_to_be_numeric);
    void Consume();

  private:
    const DomString& source_;
    vector<SvgLength> result_;
    bool succeeded_;
    const char* look_forward_;
    const char* c_string_end_;
    const char* current_numeric_begin_;
  };

  void NumericListParser::ConsumeWhiteSpaceAndComma()
  {
    if (look_forward_ == c_string_end_) {
      return;
    }
    if (isspace(*look_forward_)) {
      ++look_forward_;
      ConsumeWhiteSpaceAndComma();
    }
    else if (*look_forward_ == u8',') {
      ++look_forward_;
      ConsumeWhiteSpaceAndComma();
    }
  }

  void NumericListParser::CheckAndPushSingleUnit(const DomString& suppose_to_be_numeric)
  {
    pair<bool, double> result = StringToDouble(suppose_to_be_numeric);
    if (!result.first) {
      succeeded_ = false;
      return;
    }
    result_.push_back(result.second);
  }

  DomString NumericListParser::ConsumeNumber()
  {
    if (look_forward_ == c_string_end_) {
      return DomString();
    }
    assert(!isspace(*look_forward_) && *look_forward_ != u8',');
    current_numeric_begin_ = look_forward_;
    while (!isspace(*look_forward_) && *look_forward_ != u8',') {
      ++look_forward_;
    }
    return DomString(current_numeric_begin_, look_forward_ - current_numeric_begin_);
  }

  void NumericListParser::Consume()
  {
    if (look_forward_ == c_string_end_ || !succeeded_) {
      return;
    }
    ConsumeWhiteSpaceAndComma();
    DomString number_string_represent = ConsumeNumber();
    if (!number_string_represent.IsEmpty()) {
      CheckAndPushSingleUnit(number_string_represent);
    }
    Consume();
  }
}

pair<bool, vector<SvgLength>> ParseNumericList(const DomString& source)
{
  return NumericListParser(source).GetResult();
}

NAMESPACE_END