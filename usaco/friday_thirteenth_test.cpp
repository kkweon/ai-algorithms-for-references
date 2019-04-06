#define CATCH_CONFIG_MAIN
#include "../headers/catch.hpp"
#include "./friday_thirteenth.cpp"


TEST_CASE("is_leap", "[is_leap]") {
  REQUIRE(is_leap(2000));
  REQUIRE(is_leap(2016));
  REQUIRE(!is_leap(1700));
  REQUIRE(!is_leap(1800));
  REQUIRE(is_leap(1992));
  REQUIRE(!is_leap(1990));
}


TEST_CASE("get_day(year)") {
  REQUIRE(get_day(1900) == Mon);
  REQUIRE(get_day(1901) == Tue);
  REQUIRE(get_day(2015) == Thu);
  REQUIRE(get_day(2016) == Fri);
  REQUIRE(get_day(2017) == Sun);
  REQUIRE(get_day(2018) == Mon);
  REQUIRE(get_day(2019) == Tue);
}

TEST_CASE("get_day(year, month)") {
  REQUIRE(get_day(1900, 1) == Mon);
  REQUIRE(get_day(2016, 3) == Tue);
  REQUIRE(get_day(2019, 2) == Fri);
  REQUIRE(get_day(2019, 3) == Fri);
  REQUIRE(get_day(2019, 5) == Wed);
}

TEST_CASE("get_day(year, month, day)") {
  REQUIRE(get_day(2019, 2, 13) == Wed);
  REQUIRE(get_day(2018, 5, 16) == Wed);
  REQUIRE(get_day(2018, 6, 4) == Mon);

  REQUIRE(get_day(2016, 2, 3) == Wed);
  REQUIRE(get_day(2016, 2, 29) == Mon);
}
