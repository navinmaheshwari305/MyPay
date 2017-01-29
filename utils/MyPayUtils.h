/*
 * MyPayUtils.h
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#ifndef UTILS_MYPAYUTILS_H_
#define UTILS_MYPAYUTILS_H_

#include <vector>
#include <iostream>
#include "../data_layer/Transaction.h"

namespace myPay
{

std::string getJsonForVector(std::vector<Transaction>& vec);
static std::string sucess = "{\"Result\":\"Sucess\"}";
static std::string failure = "{\"Result\":\"Failure\"}";
static std::string no_data = "{\"Result\":\"No Data\"}";
void removeJunkChars(std::string& str);

} /* namespace myPay */

#endif /* UTILS_MYPAYUTILS_H_ */
