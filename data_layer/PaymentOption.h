/*
 * PaymentOption.h
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#ifndef DATA_LAYER_PAYMENTOPTION_H_
#define DATA_LAYER_PAYMENTOPTION_H_
#include <iostream>
#include <string>
#include <functional>

enum PaymentOption{
    paytm,freecharge,cash,netBanking,debitCard,creditCard,empty
};

static std::string PaymentOptionStrArr[] = {"Paytm","Freecharge","Cash","NetBanking","DebitCard","CreditCard" , "EMPTY"};
PaymentOption getEnumValueForString(const std::string& str);
#endif /* DATA_LAYER_PAYMENTOPTION_H_ */
