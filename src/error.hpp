#if !defined(__ERROR_HPP__)
#define __ERROR_HPP__

#include <exception>
#include <string>

/*************************************************
* \author Ayrton Lachat
* \file error.hpp
* \date 10.03.22 at 20:01
*************************************************/

class Error : std::exception
{
	public:
		Error(const std::string &msg) : _msg {msg}
		{

		}

		virtual const char *what()
		{
			return _msg.c_str();
		}

	private:
		std::string _msg;
};

#endif