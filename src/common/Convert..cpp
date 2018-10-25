#include "./Convert.h"

#include <cstdlib>
#include <string>

using std::atoi;

NAMESPACE_BEGIN

std::pair<bool, int> ToInt(const DomString& value)
{
  atoi(value.Data());
}

std::pair<bool, double> ToDouble(const DomString& value)
{

}

NAMESPACE_END