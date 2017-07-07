/*
 * CLIENT_FILE
 */

#include "BankATMSystem.h"
#include <stdio.h>
#include <stdlib.h>

/* Methods declaration */
void CreateAnAccount();
void AddMoneyToAnAccount();
void WithdrawMoneyFromAnAccount();
void InquiryAccount();

/* This was generated by rpcgen */
	CLIENT *clnt;			// CLIENT pointer which connects to SERVER using Remote Procedure Call
	int  *result_1;
	//int  create_an_account_1_arg;
	int  *result_2;
	STRUCTURE  add_money_to_an_account_1_arg;
	int  *result_3;
	STRUCTURE  withdraw_money_from_an_account_1_arg;
	int  *result_4;
	int  inquiry_1_arg;

/* This was created by me */
	int SELECTION;
	//char *SERVER;

void
bankatmsystem_1(char *host)
{

#ifndef	DEBUG
	clnt = clnt_create (host, BankATMSystem, VERSION1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	while(1){
		printf("\nPLEASE SELECT A MENU ITEM\n");
		printf("(1) CREATE AN ACCOUNT\n");
		printf("(2) ADD MONEY TO AN ACCOUNT\n");
		printf("(3) WITHDRAW MONEY FROM AN ACCOUNT\n");
		printf("(4) ACCOUNT INQUIRY\n");
		printf("(5) EXIT\n");
		printf("SELECT YOUR CHOICE");
		scanf("%d",&SELECTION);

		switch(SELECTION){
			case 1:
				CreateAnAccount();
			break;

			case 2:
				AddMoneyToAnAccount();
			break;

			case 3:
				WithdrawMoneyFromAnAccount();
			break;

			case 4:
				InquiryAccount();
			break;

			case 5:
				printf("\nEXITTING...\nTHANK YOU FOR BANKING WITH US\n\n");
				exit(1);
			break;

			default:
				printf("\nERROR: PLEASE ENTER VALID CHOISE\n");
			break;

				 } /* End switch case*/
		} /* End while loop */
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

/* ------ create an account ------ */
void CreateAnAccount(){
	int ACCOUNT_NUMBER;

	GO_TO_LOOP:
	printf("\n----- CREATE AN ACCOUNT -----\n");
	printf("PLEASE ENTER 4 DIGIT ACCOUNT NUMBER:\n");
	scanf("%d",&ACCOUNT_NUMBER);

	/*	Check whether the account number is 4 digit or not
		if account number is 4 digit then do nothing
		else repeat the process of getting user input using GO_TO_LOOP	 
	*/
	int COUNT1, COUNT2;
	COUNT1 = ACCOUNT_NUMBER;
	while(COUNT1 != 0){
		COUNT1 /= 10;
		COUNT2++;
	}	
	if(COUNT2 != 4){
		printf("\nERROR: INVALID ACCOUNT NUMBER\n");
		//printf("COUNT2 = %d\n", COUNT2);
		COUNT2 = 0;
		goto GO_TO_LOOP;
	}

	//create_an_account_1_arg = ACCOUNT_NUMBER;

	/*	Send request for creating account number with
		passing parameter as ACCOUNT_NUMBER to SERVER
		SERVER will do the thing and result will be return to result_1
	*/
	result_1 = create_an_account_1(&ACCOUNT_NUMBER, clnt);

	if(result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");			
	}

	if(*result_1 > 0){
		printf("ACCOUNT CREATED SUCCESSFULLY...\n");
		printf("YOUR ACCOUNT NUMBER IS: %d\n", ACCOUNT_NUMBER);
	}	
	else{
		printf("THIS ACCOUNT IS ALREADY EXISTS...\n");
	}
	printf("-----------------------------\n");
}

/* ------ deposit money into an account ------ */
void AddMoneyToAnAccount(){
	struct STRUCTURE S;
	int ACCOUNT_NUMBER_TO_DEPOSIT_MONEY;
	int AMMOUNT_OF_DEPOSIT;

	printf("\n----- ADD MONEY TO AN ACCOUNT -----\n");
	printf("ENTER ACCOUNT NUMBER:\n");
	scanf("%d", &ACCOUNT_NUMBER_TO_DEPOSIT_MONEY);
	printf("ENTER AMOUNT OF MONEY TO DEPOSIT:\n");
	scanf("%d", &AMMOUNT_OF_DEPOSIT);

	S.AccountID = ACCOUNT_NUMBER_TO_DEPOSIT_MONEY;
	S.Ammount = AMMOUNT_OF_DEPOSIT;

	/*	Send request for money deposit using structure S which contains
		ACCOUNT NUMBER in which the money going to be deposited and
		AMMOUNT OF DEPOSIT for that ACCOUNT
		The request will go to server and will return the value of result to result_2			
	*/
	result_2 = add_money_to_an_account_1(&S, clnt);

	if(result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if(*result_2 == 0){
		printf("ACCCOUNT DOES NOT EXIXTS...\n");
	}

	if(*result_2 > 0){
		printf("AMMOUNT %d ADDED SUCCESSFULLY IN ACCOUNT %d\n", AMMOUNT_OF_DEPOSIT, ACCOUNT_NUMBER_TO_DEPOSIT_MONEY);
	}
}

/* ------ Withdraw money from an account ------ */
void WithdrawMoneyFromAnAccount(){
	struct STRUCTURE S;
	int ACCOUNT_NUMBER_TO_WITHDRAW_MONEY;
	int AMMOUNT_OF_WITHDRAW;

	printf("\n----- WITHDRAW MONEY FROM AN ACCOUNT -----\n");
	printf("ENTER ACCOUNT NUMBER:\n");
	scanf("%d", &ACCOUNT_NUMBER_TO_WITHDRAW_MONEY);
	printf("ENTER AMOUNT OF MONEY TO WITHDRAW:\n");
	scanf("%d", &AMMOUNT_OF_WITHDRAW);

	S.AccountID = ACCOUNT_NUMBER_TO_WITHDRAW_MONEY;
	S.Ammount = AMMOUNT_OF_WITHDRAW;

	/*	Send request for withdrawing money by specifying
		ACCOUNT NUMBER from which money going to be withdrawn and
		AMMOUNT OF WITHDRAW for that ACCOUNT
		The request will go to SERVER and will return result in result_3
	*/
	result_3 = withdraw_money_from_an_account_1(&S, clnt);

	if(result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if(*result_3 >= 0){
		printf("AMMOUNT %d WITHDRAWN SUCCESSFULLY FROM ACCOUNT %d\n", AMMOUNT_OF_WITHDRAW, ACCOUNT_NUMBER_TO_WITHDRAW_MONEY);
	}

	if(*result_3 == -1){
		printf("INSUFICIENT BALANCE TO WITHDRAW MONEY...\n");
	}

	if(*result_3 == -2){
		printf("THIS ACCOUNT DOES NOT EXISTS...\n");
	}

	printf("------------------------------------------\n");
}

void InquiryAccount(){
	int ACCOUNT_NUMBER;

	printf("\n----- INQUIRY -----\n");
	printf("ENTER ACCOUNT NUMBER FOR INQUIRY:\n");
	scanf("%d", &ACCOUNT_NUMBER);

	//inquiry_1_arg = ACCOUNT_NUMBER;

	/*	Send request for balance inquiry for given ACCOUNT_NUMBER to SERVER
		SERVER will do the thing and return the result into result_4
	*/
	result_4 = inquiry_1(&ACCOUNT_NUMBER, clnt);

	if(result_4 == (int *) NULL){
		clnt_perror(clnt, "call failed");
	}

	if(*result_4 >= 0){
		printf("ACCOUNT NUMBER: %d\n", ACCOUNT_NUMBER);
		printf("AVAILABLE BALANCE: %d\n", *result_4);
	}

	else{
		printf("ACCOUNT DOES NOT EXISTS...\n");
	}
	printf("-------------------\n");
}

int
main (int argc, char *argv[])
{
	char *host;
	
	/* Argument should be ./BankATMSystem_client localhost */
	if (argc == 2){
		printf("\nSUCCESS: CONNECTED TO SERVER...\n");
	}
	else{ /* Otherwise throw an error message */
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	bankatmsystem_1 (host);
exit (0);
}
