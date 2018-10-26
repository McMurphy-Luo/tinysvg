#include "./Convert.h"

#include <cstdlib>
#include <cerrno>
#include <climits>

using std::strtol;
using std::strtod;
using std::make_pair;
using std::pair;

NAMESPACE_BEGIN

pair<bool, int> ToInt(const DomString& value)
{
  int previous_error = errno;
  char* string_end = 0;
  errno = 0;
  bool succeeded = false;
  long result = strtol(value.Data(), &string_end, 10);

  if (result == 0 && string_end == value.Data()) {
    // no conversion can be performed
    succeeded = false;
  }
  else if (errno == ERANGE && (result == LONG_MAX || result == LONG_MIN)) {
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

pair<bool, double> ToDouble(const DomString& value)
{
  int previous_error = errno;

  return make_pair(true, 0);
}

NAMESPACE_END