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

  /**
   * @author McMurphy.Luo
   * @date Oct/28/2018
   * parse a list of double defined as EBNF grammar:
   * list-of-Ts ::= T | T, list-of-Ts
   */
  class NumericListParser
  {
  public:
    explicit NumericListParser(const DomString& source)
    : result_()
    , succeeded_(true)
    , look_forward_(source.Data())
    , c_string_end_(source.Data() + source.ByteCount())
    , current_numeric_begin_(look_forward_)
    {
      
    }

    pair<bool, vector<SvgLength>> GetResult()
    {
      Consume();
      return make_pair(succeeded_, result_);
    }

  private:
    void Consume();
    void ConsumeWhiteSpace();
    void ConsumeNumberList();
    void ConsumeNumber();
    void ConsumeComma();
    void ConsumeOptionalNumberList();

  private:
    vector<SvgLength> result_;
    bool succeeded_;
    const char* look_forward_;
    const char* c_string_end_;
    const char* current_numeric_begin_;
  };

  void NumericListParser::ConsumeWhiteSpace()
  {
    while(
      look_forward_ < c_string_end_
      &&
      isspace(*look_forward_)
    ) {
      ++look_forward_;
    }
  }

  void NumericListParser::ConsumeOptionalNumberList()
  {
    ConsumeWhiteSpace();
    if (look_forward_ == c_string_end_) {
      return;
    }
    if (look_forward_ < c_string_end_ && *look_forward_ == ',') {
      ConsumeComma();
      ConsumeWhiteSpace();
    }
    ConsumeNumberList();
  }

  void NumericListParser::ConsumeComma()
  {
    assert(look_forward_ < c_string_end_ && *look_forward_ == u8',');
    if (look_forward_ < c_string_end_ && *look_forward_ == u8',') {
      ++look_forward_;
    }
  }

  void NumericListParser::ConsumeNumber()
  {
    current_numeric_begin_ = look_forward_;
    while (
      look_forward_ < c_string_end_
      &&
      !isspace(*look_forward_) && *look_forward_ != u8','
    ) {
      ++look_forward_;
    }

    pair<bool, double> may_be_double = StringToDouble(DomString(current_numeric_begin_, look_forward_ - current_numeric_begin_));
    if (!may_be_double.first) {
      succeeded_ = false;
      return;
    }
    result_.push_back(may_be_double.second);
    return;
  }

  void NumericListParser::ConsumeNumberList()
  {
    ConsumeNumber();
    if (!succeeded_) {
      return;
    }
    ConsumeOptionalNumberList();
  }

  void NumericListParser::Consume()
  {
    ConsumeWhiteSpace();
    ConsumeNumberList();
  }
}

pair<bool, vector<SvgLength>> ParseNumericList(const DomString& source)
{
  return NumericListParser(source).GetResult();
}

pair<bool, SvgLength> ParseNumeric(const DomString& source)
{
  return StringToDouble(source);
}

NAMESPACE_END