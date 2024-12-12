#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Task {
private:
	std::string title;
	std::string description;
	int priority;
	std::time_t deadline;
	bool isDone;
	std::time_t createdAt;
public:
	std::string& getTitle();
	std::string& getDescription();
	int& getPriority();
	std::time_t& getDeadline();
	void makeDone();

	const std::time_t& getCreatedAt() const;
	const std::string& getTitle() const;
	const std::string& getDescription() const;
	const int& getPriority() const;
	const std::time_t& getDeadline() const;
	const bool& done() const;

	Task(const std::string& title, const std::string& description, const int& priority,
		std::time_t deadline);

	Task(const Task&) = default;
	Task& operator=(const Task&) = default;
	~Task() = default;
};