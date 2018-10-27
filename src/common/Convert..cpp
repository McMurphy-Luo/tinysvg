#include "./Convert.h"

#include <cstdlib>
#include <cerrno>
#include <climits>
#include <string>

using std::strtol;
using std::strtod;
using std::make_pair;
using std::pair;

NAMESPACE_BEGIN

pair<bool, int> StringToInt(const DomString& value)
{
  int previous_error = errno;
  char* string_end = 0;
  errno = 0;
  bool succeeded = false;
  long result = strtol(value.Data(), &string_end, 10);

  if (string_end == value.Data()) {
    // no conversion can be performed
    succeeded = false;
  }
  else if (errno == ERANGE) {
    succeeded = false;
  }
  else if (result > INT_MAX || result < INT_MIN) {
    succeeded = false;
  }
  errno = previous_error;
  if (succeeded) {
    return make_pair(true, result);
  }
  return make_pair(false, 0);
}

pair<bool, double> StringToDouble(const DomString& value)
{
  int previous_error = errno;
  char* string_end = 0;
  errno = 0;
  bool succeeded = false;
  double result = strtod(value.Data(), &string_end);

  std::stod("fucker");

  if (string_end == value.Data()) {
    succeeded = false;
  }
  else if (errno == ERANGE) {
    succeeded = false;
  }
  errno = previous_error;

  if (succeeded) {
    return make_pair(true, result);
  }
  return make_pair(false, 0.0);
}

NAMESPACE_END