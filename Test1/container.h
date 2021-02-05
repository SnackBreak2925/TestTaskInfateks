#pragma once
#ifndef CONTENT_H
#define CONTENT_H
#include <string>
#include <mutex>
#include<atomic>

class container
{
public:
	container();
	container(const char*);
	container(std::string&);
	void correct_content();
	void to_buf(std::string&) const;
	void from_buf(std::string&);
	void clear_buf() const;
	int core_thr1();
	int core_thr2();
	bool content_check_digits(std::string&) const;
private:
	std::string content;
	mutable std::mutex locker;
	static std::atomic<bool> done;
};
#endif