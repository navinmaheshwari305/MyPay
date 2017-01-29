#include "PaymentOption.h"

PaymentOption getEnumValueForString(const std::string& str)
{
	if( str =="Paytm")
	{
		return paytm;

	}
	else if( str =="Freecharge")
	{
		return freecharge;

	}
	else if( str =="Cash")
	{
		return cash;

	}
	else if( str =="NetBanking")
	{
		return netBanking;

	}
	else if( str =="DebitCard")
	{
		return debitCard;

	}
	else if( str =="CreditCard")
	{
		return creditCard;

	}
	else
	{
		return empty;

	}

}
