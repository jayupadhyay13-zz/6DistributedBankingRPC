struct STRUCTURE{
	int AccountID;
	int Ammount;
};

program BankATMSystem{
	version VERSION1{
		int CREATE_AN_ACCOUNT(int create) = 1;
		int ADD_MONEY_TO_AN_ACCOUNT(STRUCTURE add) = 2;
		int WITHDRAW_MONEY_FROM_AN_ACCOUNT(STRUCTURE deposit) = 3;
		int INQUIRY(int inquiry) = 4;
	} = 1;
} = 0x3EEEEEEE;
