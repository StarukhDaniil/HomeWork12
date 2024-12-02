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
	std::string& getTitle();
	std::string& getDescription();
	int& getPriority();
	std::chrono::system_clock::time_point& getDeadline();
	void makeDone();

	const std::chrono::system_clock::time_point& getCreatedAt() const;
	const std::string& getTitle() const;
	const std::string& getDescription() const;
	const int& getPriority() const;
	const std::chrono::system_clock::time_point& getDeadline() const;
	const bool& done() const;

	Task(const std::string& title, const std::string& desription, const int& priority,
		std::chrono::system_clock::time_point deadline);

	Task(const Task&) = default;
	Task& operator=(const Task&) = default;
	~Task() = default;
};