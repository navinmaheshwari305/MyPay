/*
 * MyPayUtils.cpp
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#include "MyPayUtils.h"

namespace myPay
{
std::string getJsonForVector(std::vector<Transaction>& vec)
{
	std::string rStr;
	rStr = "[\n";

	for(auto it = vec.begin();it != vec.end() ; it++)
	{
		if(it != vec.begin()) rStr += ",\n";
		rStr += it->toJson();
	}

	rStr += "\n]";
	return rStr;
}

void removeJunkChars(std::string& str)
{
	std::cout << "String ---| " << str << "|---" << std::endl;
	auto pos = str.find_last_of('}');
	str = str.substr(0, pos+1);
}

} /* namespace myPay */
