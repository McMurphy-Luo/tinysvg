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
    , succeeded_(false)
    , look_forward_(source.Data())
    , current_numeric_begin_(look_forward_)
    , current_numeric_end_(look_forward_)
    {
      
    }

    pair<bool, vector<SvgLength>> GetResult();

  private:
    bool CheckAndPushSingleUnit(const DomString& suppose_to_be_numeric);
    void ConsumeWhiteSpaceAndComma();
    void ConsumeNumber();

  private:
    const DomString& source_;
    vector<SvgLength> result_;
    bool succeeded_;
    const char* look_forward_;
    const char* current_numeric_begin_;
    const char* current_numeric_end_;
  };

  void NumericListParser::ConsumeWhiteSpaceAndComma()
  {
    if (isspace(*look_forward_)) {
      ++look_forward_;
      ConsumeWhiteSpaceAndComma();
    }
    else if (*look_forward_ == u8',') {
      ++look_forward_;
      ConsumeWhiteSpaceAndComma();
    }
    else {
      current_numeric_begin_ = look_forward_;
      current_numeric_end_ = look_forward_;
    }
  }

  bool NumericListParser::CheckAndPushSingleUnit(const DomString& suppose_to_be_numeric)
  {
    pair<bool, double> result = StringToDouble(suppose_to_be_numeric);
    if (!result.first) {
      succeeded_ = false;
      return false;
    }
    result_.push_back(result.second);
    return true;
  }

  void NumericListParser::ConsumeNumber()
  {
    if (isspace(*look_forward_) || *look_forward_ == u8',') {
      if (!CheckAndPushSingleUnit(DomString(current_numeric_begin, current_numeric_end - current_numeric_begin + 1))) {
        return make_pair(false, vector<SvgLength>());
      }
      is_during_a_numeric = false;
    }
    else {
      current_numeric_end = look_forward;
    }
  }

  pair<bool, vector<SvgLength>> NumericListParser::GetResult()
  {
    vector<DomString> numeric_string;

    const char* look_forward = source_.Data();
    const char* current_numeric_begin = look_forward;
    const char* current_numeric_end = look_forward;
    bool is_during_a_numeric = false;
    for (; look_forward < source_.Data() + source_.ByteCount(); ++look_forward) {
      if (is_during_a_numeric) {
        
      }
      else {
        
      }
    }

    if (is_during_a_numeric) {
      CheckAndPushSingleUnit(DomString(current_numeric_begin, current_numeric_end - current_numeric_begin + 1));
    }

    return result_;
  }
}

pair<bool, vector<SvgLength>> ParseNumericList(const DomString& source)
{
  

}

NAMESPACE_END