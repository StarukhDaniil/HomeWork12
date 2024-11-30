#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Task {
private:
	std::string title;
	std::string description;
	int priority;
	std::chrono::system_clock::time_point deadline;
	bool isDone;
	std::chrono::system_clock::time_point createdAt;
public:
	Task(const std::string& title, const std::string& desription, const int& priority,
		std::chrono::system_clock::time_point deadline);
};