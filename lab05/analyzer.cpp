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

// Uses linear search to find specified element in container.
// Returns index of element, or -1 if not found.
int linear_search(const std::vector<std::string>& container, const std::string& element)
{
  for (unsigned int i = 0; i < container.size(); i++)
    if (container[i] == element)
      return i;
  return -1;
}

// Uses binary search to find specified element in container.
// Returns index of element, or -1 if not found.
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
// A simplified data generator that I made.
//
std::vector<std::string> generate_data()
{
  char str[6];
  int i = 0;
  str[5] = '\0';

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
// This function tests both search methods.
//
void profile_search(const std::vector<std::string>& container, const std::string& element)
{
  typename std::chrono::system_clock::time_point start_time, end_time;
  std::chrono::duration<double, std::milli> delta_time;
  int index;

  std::cout << "Searching for '" << element << "':" << std::endl;

  start_time = std::chrono::system_clock::now();
  index = linear_search(container, element);
  end_time = std::chrono::system_clock::now();
  delta_time = std::chrono::duration_cast<decltype(delta_time)>(end_time - start_time);
  std::cout << "  linear search: found " << index << " in " << delta_time.count() << "ms" << std::endl;

  start_time = std::chrono::system_clock::now();
  index = binary_search(container, element);
  end_time = std::chrono::system_clock::now();
  delta_time = std::chrono::duration_cast<decltype(delta_time)>(end_time - start_time);
  std::cout << "  binary search: found " << index << " in " << delta_time.count() << "ms" << std::endl;
}

//--------------------------------------
// Entry Point (main)
//--------------------------------------

int main()
{
  typename std::chrono::system_clock::time_point start_time, end_time;
  std::chrono::duration<double, std::milli> delta_time;

  std::cout << "Generating dataset..." << std::endl;
  start_time = std::chrono::system_clock::now();
  std::vector<std::string> dataset = generate_data();
  end_time = std::chrono::system_clock::now();
  delta_time = std::chrono::duration_cast<decltype(delta_time)>(end_time - start_time);
  std::cout << "Generated " << dataset.size() << " values in " << delta_time.count() << "ms" << std::endl;

  profile_search(dataset, "not_here");
  profile_search(dataset, "mzzzz");
  profile_search(dataset, "aaaaa");

  return 0;
}
