#include "Transaction.h"

Transaction::Transaction()
{
	transactionType = "";
	transactionAmount = 0;
	snapshotBalance = 0;
	overdraft = false;
}
Transaction::Transaction(string _transactionType, double transactionAmount, double snapshotBalance, bool overdraft)
{


}