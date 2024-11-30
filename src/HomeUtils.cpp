#include <HomeUtils.hpp>

String formatDate(DateTime dateTime) {
  return String(dateTime.year()) + "-" + formatNumber(dateTime.month()) + "-" +
         formatNumber(dateTime.day());
}

String formatTime(DateTime dateTime) {
  return formatNumber(dateTime.hour()) + ":" + formatNumber(dateTime.minute()) +
         ":" + formatNumber(dateTime.second());
}

String formatNumber(int number) {
  return number < 10 ? "0" + String(number) : String(number);
}
