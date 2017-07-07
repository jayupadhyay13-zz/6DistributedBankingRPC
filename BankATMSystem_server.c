/*
 * SERVER_FILE
 */

#include "BankATMSystem.h"

/* STRUCTURE to store the ACCOUNT DETAILS */
struct ACCOUNT_DETAILS{
	int ACCOUNT_NUMBER;
	int AMMOUNT;
}ACCOUNTS[60];
int COUNTER; /* This will be used by for loop */

int *
create_an_account_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;
	/*
	 * insert server code here
	 */
	int ACCOUNT = *argp;
	int INDEX;

	/*	Check whether the account number that user has entered,
		belongs to our list of account numbers
		which is stored in an ARRAY STRUCTURE named ACCOUNTS[] or not

		if ACCOUNT_NUMBER belongs to this new user account will be created (result = 0)
		else ACCOUNT_NUMBER will not be created (result = 1)
	*/
	for(INDEX=0; INDEX<sizeof(ACCOUNTS); INDEX++){
		if(ACCOUNTS[INDEX].ACCOUNT_NUMBER == ACCOUNT){
			result = 0;
			return &result;
		}
	}
	ACCOUNTS[COUNTER].ACCOUNT_NUMBER = ACCOUNT;
	ACCOUNTS[COUNTER].AMMOUNT = 0;
	printf("\n--- ACCOUNT CREATED WITH ACCOUNT NUMBER: %d ---\n", ACCOUNT);
	COUNTER++;
	result = 1;
	//fflush(stdout);
	return &result;
}

int *
add_money_to_an_account_1_svc(STRUCTURE *argp, struct svc_req *rqstp)
{
	static int  result;
	/*
	 * insert server code here
	 */
	int INDEX;
	STRUCTURE S = *argp;

	/*	Check whether the account number entered by user is exists in our array
		ACCOUNTS[] or not

		if ACCOUNT_NUMBER matches then, DIPOSIT that respective amount
		to that ACCOUNT_NUMBER (result > 0)
		else money will not be deposited because,
		that ACCOUNT_NUMBER does not exists (result = 0)
	*/
	for(INDEX=0; INDEX<COUNTER; INDEX++){
		if(ACCOUNTS[INDEX].ACCOUNT_NUMBER == S.AccountID){
			ACCOUNTS[INDEX].AMMOUNT = ACCOUNTS[INDEX].AMMOUNT + S.Ammount;
			printf("DEPOSIT REQUEST OF AMMOUNT %d FOR ACCOUNT NUMBER %d\n", S.Ammount, S.AccountID);
			return &ACCOUNTS[INDEX].AMMOUNT;
		}
	}
	result = 0;
	return &result;
}

int *
withdraw_money_from_an_account_1_svc(STRUCTURE *argp, struct svc_req *rqstp)
{
	static int  result;
	/*
	 * insert server code here
	 */
	int INDEX;
	STRUCTURE S = *argp;

	/*	First check whether the account number mathes with our list of ACCOUNT_NUMBERS or not
		if the ACCOUNT_NUMBER belongs to that array
			then check whether that ACCOUNT_NUMBER have enough balance to withdraw or not
			if AMOUNT_OF_ACCOUNT > WITHDRAW_AMOUNT
				then withdraw money from that account
			else
				unable to withdraw money because of insufficient credit
				into that ACCOUNT (result = -1)
	*/
	for(INDEX=0; INDEX<COUNTER; INDEX++){
		if(ACCOUNTS[INDEX].ACCOUNT_NUMBER == S.AccountID){
			int BALANCE = ACCOUNTS[INDEX].AMMOUNT - S.Ammount;
			if(BALANCE >= 0){
				ACCOUNTS[INDEX].AMMOUNT = BALANCE;
				printf("WITHDRAW REQUEST OF AMMOUNT %d FOR ACCOUNT NUMBER %d\n", S.Ammount, S.AccountID);
				return &ACCOUNTS[INDEX].AMMOUNT;
			}
			else{
				result = -1;
				return &result;
			}
		}
	}
	result = -2;
	return &result;
}

int *
inquiry_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;
	/*
	 * insert server code here
	 */
	int INDEX;
	int ACCOUNT = *argp;
	
	/*	Check whether the account number belongs to list of ACCOUNTS array or not
		if it belongs to that account then return the ammount
		else that ACCOUNT_NUMBER does not exists (result = -1)
		
	*/
	for(INDEX=0; INDEX<COUNTER; INDEX++){
		if(ACCOUNTS[INDEX].ACCOUNT_NUMBER == ACCOUNT){
			printf("BALANCE REQUEST FOR ACCOUNT NUMBER %d\n", ACCOUNT);
			return &ACCOUNTS[INDEX].AMMOUNT;
		}
	}	
	result = -1;
	return &result;
}
