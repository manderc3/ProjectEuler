#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using raw_nums = unordered_map<int, string>;
using processed_nums = map<int, string>;

raw_nums get_raw_num_map()
{
  return raw_nums(
    {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"},
     {9, "nine"}, {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"},
     {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"}, {30, "thirty"},
     {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"},
     {100, "hundred"}, {1000, "onethousand"}});
}

int get_int_length(int num)
{
  int length = 1;

  while (num /= 10) length++;

  return length;
}

int deduce_int_text_length(int num, const raw_nums& nums)
{
  auto it = nums.find(num);

  if (it != nums.end()) {
    return nums.at(num).length();
  }

  auto int_length = get_int_length(num);
  bool include_and = int_length >= 3 ? true : false;
  auto multiplier = pow(10, int_length - 1);
  string number_string;

  while (multiplier >= 10) {
    if (multiplier == 100) {
      number_string += nums.at(static_cast<int>(num / multiplier));
      number_string += (num % 100 == 0) ? "hundred" : "hundredand";
    }
    else if (multiplier == 10) {
      int trimmed_num = num % 100;

      if (!trimmed_num) break;
      
      if (trimmed_num <= 20 || trimmed_num % 10 == 0) {
	number_string += nums.at(trimmed_num);
      }
      else {
	number_string += nums.at(static_cast<int>(trimmed_num / multiplier) * multiplier);
        number_string += nums.at(trimmed_num % 10);
      }
    }
    
    multiplier /= 10;
  }

  return number_string.length();
}

int process_map(const raw_nums& nums)
{
  int sum = 0;

  for (int i = 1; i <= 1000; i++) {
    sum += deduce_int_text_length(i, nums);
    cout << i << " = " << deduce_int_text_length(i, nums) <<  "\n";
  }

  return sum;
}


int main()
{
  auto raw_num_map = get_raw_num_map();

  auto t1 = chrono::system_clock::now();

  const auto num_sum_total = process_map(raw_num_map);

  auto t2 = chrono::system_clock::now();

  cout << "Total: " << num_sum_total << "\n";

  chrono::duration<double, milli> dur = t2 - t1;
  cout << "Time: " << dur.count() << " milliseconds \n";

  return 0;
}
