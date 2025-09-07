

#include "Account.hpp"
#include <iostream>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

	int		Account::getNbAccounts( void )
	{
		return _nbAccounts;
	}
	
	int		Account::getTotalAmount( void )
	{
		return _totalAmount;
	}

	int		Account::getNbDeposits( void )
	{
		return _totalNbDeposits;
	}
	
	int		Account::getNbWithdrawals( void )
	{
		return _totalNbWithdrawals;
	}

	void		Account::displayAccountsInfos( void )
	{
		_displayTimestamp();
		std::cout << "accounts:"    << _nbAccounts      	<< ';'
        		  << "total:"       << _totalAmount     	<< ';'
        		  << "deposits:"    << _totalNbDeposits 	<< ';'
        		  << "withdrawals:" << _totalNbWithdrawals 
				  << std::endl;
	}

	Account::Account( int initial_deposit )
	{
		static int AccountIndex = 0;
		this->_accountIndex = AccountIndex;
		this->_amount = initial_deposit;
		this->_nbDeposits = 0;
		this->_nbWithdrawals = 0;
		_totalAmount += initial_deposit;
		_nbAccounts++;
		AccountIndex++;
		_displayTimestamp();
		std::cout << "index:" 	<< this->_accountIndex 	<< ';'
				  << "amount:"	<< this->_amount 		<< ';'
				  << "created"
				  << std::endl;
	}
	
	Account::~Account( void )
	{
		_nbAccounts--;
		_totalAmount -= this->_amount;
		_totalNbDeposits -= this->_nbDeposits;
		_totalNbWithdrawals -= this->_nbWithdrawals;
		_displayTimestamp();
		std::cout << "index:"  << this->_accountIndex 	<< ';'
				  << "amount:" << this->_amount 		<< ';'
				  << "closed"
				  << std::endl;
	}

	void	Account::makeDeposit( int deposit )
	{
		_totalNbDeposits++;
		this->_nbDeposits++;
		this->_amount += deposit;
		_totalAmount += deposit;
		_displayTimestamp();
		std::cout << "index:"		<< this->_accountIndex 		<< ';'
				  << "p_amount:"	<< this->_amount - deposit	<< ';'
				  << "deposit:"		<< deposit					<< ';'
				  << "amount:"		<< this->_amount 			<< ';'
				  << "nb_deposits:"	<< this->_nbDeposits
				  << std::endl;
	}
	
	bool	Account::makeWithdrawal( int withdrawal )
	{
		_displayTimestamp();
		std::cout << "index:"		<< this->_accountIndex 		<< ';'
				  << "p_amount:"	<< this->_amount	<< ';';
		if (withdrawal <= this->_amount)
		{
			_nbWithdrawals++;
			this->_amount -= withdrawal;
			_totalAmount  -= withdrawal;
			_totalNbWithdrawals++;
			std::cout << "withdrawal:" 		<< withdrawal 			<< ';'
					  << "amount:"			<< this->_amount 		<< ';'
					  << "nb_withdrawals:"	<< this->_nbWithdrawals	
					  << std::endl;
		}
		else
		{
			std::cout 	<< "withdrawal:refused"
						<< std::endl;
			return false;
		}
		return true;
	}
	
	int	Account::checkAmount( void ) const
	{
		return this->_amount;
	}

	void	Account::displayStatus( void ) const
	{
		_displayTimestamp();
		std::cout << "index:"		<< this->_accountIndex 	<< ';'
				  << "amount:"		<< this->_amount 		<< ';'
				  << "deposits:"	<< this->_nbDeposits	<< ';'
				  << "withdrawals:"	<< this->_nbWithdrawals	
				  << std::endl;
	}

	void	Account::_displayTimestamp( void )
	{
		 time_t now = time(0);                
    	struct tm* localTime = localtime(&now);  

    	char buffer[19];  
    	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ", localTime);
		std::cout << buffer;
	}