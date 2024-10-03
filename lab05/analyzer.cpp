/***************************************
 * File: analyzer.py
 *
 *  ------------------------------------
 *  Lab 05: Software Engineering
 *  ------------------------------------
 *
 *  Author: Daniel Li
 *  Course: COP3504C
 *  Section: 25452 (Tavassoli)
 *  Date: Oct 01 2024
 *
 **************************************/

#include <chrono>
#include <iostream>
#include <vector>

//--------------------------------------
// Search Methods
//--------------------------------------

//
// Uses linear search to find specified element in container.
// Returns index of element, or -1 if not found.
//
int linear_search(const std::vector<std::string>& container, const std::string& element)
{
  for (unsigned int i = 0; i < container.size(); i++)
    if (container[i] == element)
      return i;
  return -1;
}

//
// Uses binary search to find specified element in container.
// Returns index of element, or -1 if not found.
//
int binary_search(const std::vector<std::string>& container, const std::string& element)
{
  int lower = 0;
  int upper = container.size();
  while (lower < upper) {
    int mid = (lower + upper) / 2;
    int cmp = element.compare(container[mid]);
    if (cmp < 0)
      upper = mid;
    else if (cmp > 0)
      lower = mid + 1;
    else
      return mid;
  }
  return -1;
}

//--------------------------------------
// Other Methods
//--------------------------------------

//
// A simplified data generator.
//
std::vector<std::string> generate_data()
{
  char str[6];
  int i = 0;
  str[5] = '\0'; // terminate with null byte

  std::vector<std::string> dataset(26*26*26*26*26);
  for (str[0] = 'a'; str[0] <= 'z'; str[0]++)
    for (str[1] = 'a'; str[1] <= 'z'; str[1]++)
      for (str[2] = 'a'; str[2] <= 'z'; str[2]++)
        for (str[3] = 'a'; str[3] <= 'z'; str[3]++)
          for (str[4] = 'a'; str[4] <= 'z'; str[4]++)
            dataset[i++] = str;

  return dataset;
}

//
// Calls a function and records the time in milliseconds that it takes the
// function to complete, storing it in the `time` parameter.
//
template<class Ret, class... Args>
Ret measure_time(double& time, Ret (*fn)(Args...), Args&&... args)
{
  typename std::chrono::system_clock::time_point start_time, end_time;
  std::chrono::duration<double, std::milli> delta_time;

  start_time = std::chrono::system_clock::now();
  Ret ret = fn(std::forward<Args>(args)...);
  end_time = std::chrono::system_clock::now();
  delta_time = std::chrono::duration_cast<decltype(delta_time)>(end_time - start_time);

  time = delta_time.count();
  return std::move(ret);
}

//
// Tests both search methods by searching for an element in a container.
//
void profile_search(const std::vector<std::string>& container, const std::string& element)
{
  int index;
  double time;

  std::cout << "Searching for '\e[1m" << element << "\e[0m':" << std::endl;

  index = measure_time(time, linear_search, container, element);
  std::cout << "  linear search: found \e[1m" << index << "\e[0m in " << time << "ms" << std::endl;

  index = measure_time(time, binary_search, container, element);
  std::cout << "  binary search: found \e[1m" << index << "\e[0m in " << time << "ms" << std::endl;
}

//--------------------------------------
// Entry Point (main)
//--------------------------------------

int main()
{
  double time;

  std::cout << "Generating dataset..." << std::endl;
  std::vector<std::string> dataset = measure_time(time, generate_data);
  std::cout << "Generated " << dataset.size() << " values in " << time << "ms" << std::endl;

  profile_search(dataset, "not_here");
  profile_search(dataset, "mzzzz");
  profile_search(dataset, "aaaaa");

  return 0;
}
