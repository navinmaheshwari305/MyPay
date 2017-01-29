/*
 * Transaction.h
 *
 *  Created on: 28-Jan-2017
 *      Author: navin
 */

#ifndef DATA_LAYER_TRANSACTION_H_
#define DATA_LAYER_TRANSACTION_H_

#include "PaymentOption.h"
#include "../json/json.hpp"
#include <ctime>
#include <iostream>
#include <vector>

namespace myPay
{

class Transaction {
	int sno;
	PaymentOption paymentOption;
	double amount;
	std::string remarks;
	std::string dateOfTransaction;
public:
	Transaction();

	Transaction(int,PaymentOption,double,std::string,std::string);

	virtual ~Transaction();

	std::string toJson();

	void getTrasactionFromJson(std::string& js_);

	bool insertTrasaction();

	static std::vector<Transaction> getTrasaction();

	bool getTransaction(int sno_);

	static bool deleteTransaction(int sno_);

	bool updateTransaction();

	double getAmount() const {
		return amount;
	}

	void setAmount(double amount) {
		this->amount = amount;
	}

	std::string getDateOfTransaction() const {
		return dateOfTransaction;
	}

	void setDateOfTransaction(std::string dateOfTransaction) {
		this->dateOfTransaction = dateOfTransaction;
	}

	PaymentOption getPaymentOption() const {
		return paymentOption;
	}

	void setPaymentOption(PaymentOption paymentOption) {
		this->paymentOption = paymentOption;
	}

	const std::string& getRemarks() const {
		return remarks;
	}

	void setRemarks(const std::string& remarks) {
		this->remarks = remarks;
	}

	int getSno() const {
		return sno;
	}

	void setSno(int sno) {
		this->sno = sno;
	}

};
};
#endif /* DATA_LAYER_TRANSACTION_H_ */
