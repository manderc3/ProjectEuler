#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using raw_nums = unordered_map<int, string>;

/*
 * Author: Chris Mander @manderc3
 * Description: Solution to Project Euler's seventeenth problem. Url is 'https://projecteuler.net/problem=17'.
 *
 * Would be nice to account for ranges with an upper bound of over a thousand. Perhaps a story for another day?
 */
raw_nums get_raw_num_map() noexcept
{
  return raw_nums(
    {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"},
     {9, "nine"}, {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"},
     {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"}, {30, "thirty"},
     {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"},
     {100, "hundred"}, {1000, "thousand"}});
}

int get_int_length(int num) noexcept
{
  int length = 1;
  while (num /= 10) length++;
  return length;
}

int deduce_int_text_length(int num, const raw_nums& nums)
{
  auto it = nums.find(num);
  if (it != nums.end() && num < 100) {
    return nums.at(num).length();
  }

  auto int_length = get_int_length(num);
  bool include_and = int_length >= 3 ? true : false;
  auto multiplier = static_cast<int>(pow(10, int_length - 1));
  string number_string;

  while (multiplier >= 10) {
    switch (multiplier) {
      case 1000: {
        number_string += nums.at(abs(num / multiplier)) + nums.at(multiplier);
	break;
      }
      case 100: {
        number_string += nums.at(abs(num / multiplier)) + nums.at(multiplier);
        if (num % multiplier != 0) number_string += "and";
	break;
      }
      case 10: {
	int trimmed_num = num % 100;
	if (!trimmed_num) break;
	if (trimmed_num <= 20 || trimmed_num % 10 == 0) {
	  number_string += nums.at(trimmed_num);
	}
	else {
	  number_string += nums.at(abs(trimmed_num / multiplier) * multiplier) + nums.at(trimmed_num % 10);
	}
	break;
      }
      default: {
	break;
      }
    }

    if (!(num % multiplier)) break;
    multiplier /= 10;
  }

  return number_string.length();
}

int process_map(const raw_nums& nums)
{
  int sum = 0;
  for (int i = 1; i <= 1000; i++) {
    sum += deduce_int_text_length(i, nums);;
  }
  return sum;
}

int main()
{
  auto t1 = chrono::system_clock::now();
  const auto num_sum_total = process_map(get_raw_num_map());
  auto t2 = chrono::system_clock::now();
  
  cout << "Total Letters in Range: " << num_sum_total << "\n";
  chrono::duration<double, milli> dur = t2 - t1;
  cout << "Time Taken: " << dur.count() << " milliseconds \n";

  return 0;
}
