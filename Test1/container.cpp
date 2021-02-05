#include "container.h"
#include "client.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;
atomic<bool> container::done(false);

container::container()
{
	cin >> content;
	correct_content();
}

container::container(const char* in)
{
	content = in;
	correct_content();
}

container::container(string& in)
{
	content = in;
	correct_content();
}

void container::correct_content()
{
	while((content.size() != 64 || !content_check_digits(content)) && !done)
	{
		if(content == "Exit" || content == "exit" || (content == "0" && content.size() == 1))
		{
			done = true;
			exit(0);
		}
		cout << "Invalid input data. Try again." << endl;
		content.clear();
		cin >> content;
	}
}

int container::core_thr1()
{
	locker.lock();
	if(done)
	{
		locker.unlock();
		exit(0);
	}
	sort(content.begin(), content.end(), greater<char>());
	string processed;
	processed.resize(content.size() * 2);
	int counter = 0;
	for(size_t i = 0; i < content.size(); i++)
	{
		if(i % 2)
		{
			processed[counter++] = content[i];
		}
		else
		{
			processed[counter++] = 'K';
			processed[counter++] = 'B';
		}
	}
	to_buf(processed);
	locker.unlock();
	return 0;
}

int container::core_thr2()
{
	locker.lock();
	if(done)
	{
		locker.unlock();
		exit(0);
	}
	string input;
	from_buf(input);
	clear_buf();
	int sum = 0;
	for(size_t i = 0; i < input.size(); i++)
	{
		if(isdigit(input[i]))
			sum += (int)input[i] - '0';
	}
	client c;
	string in = to_string(sum);
	c.to_buf(in);
	c.csend();
	locker.unlock();
	return 0;
}

void  container::to_buf(string& str) const
{
	ofstream tmp("buffer.tmp");
	tmp << str;
	tmp.close();
}

void container::from_buf(string& input)
{
	ifstream buffer("buffer.tmp");
	buffer >> input;
	buffer.close();
}

void  container::clear_buf() const
{
	ofstream clear_buffer("buffer.tmp");
	clear_buffer.close();
}

bool container::content_check_digits(std::string& in) const
{
	return std::all_of(in.begin(), in.end(), ::isdigit);
}