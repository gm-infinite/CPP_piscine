/* ************************** */
/*                                                                            */
/*   PhoneBook.cpp                                    ██╗  ██╗██████╗ ██╗   ██╗   */
/*                                                ██║ ██╔╝██╔══██╗╚██╗ ██╔╝   */
/*   By: kuzyilma <kuzeyilma@gmail.com>           █████╔╝ ██████╔╝ ╚████╔╝    */
/*                                                ██╔═██╗ ██╔══██╗  ╚██╔╝     */
/*   Created: 2025/06/16 19:14:28 by kuzyilma     ██║  ██╗██████╔╝   ██║      */
/*                                                ╚═╝  ╚═╝╚═════╝    ╚═╝      */
/*                                                                            */
/* ************************** */



#include <iostream>
#include <string>
#include <iomanip>
#include "PhoneBook.hpp"

void add_function(PhoneBook *phonebook)
{
	Contacts new_contact;
	static int contact_amounth = 0;

	std::cout << "Please enter the first name of the new contact:" << std::endl;
	std::getline(std::cin, new_contact.first_name);

	std::cout << "Please enter the last name of the new contact:" << std::endl;
	std::getline(std::cin, new_contact.last_name);

	std::cout << "Please enter the nickname of the new contact:" << std::endl;
	std::getline(std::cin, new_contact.nickname);

	std::cout << "Please enter the phone number of new the contact:" << std::endl;
	std::getline(std::cin, new_contact.phone_number);

	std::cout << "Please enter the darkest secret of the new contact:" << std::endl;
	std::getline(std::cin, new_contact.dark_secret);

	phonebook->all_contects[contact_amounth%8].first_name = new_contact.first_name; 
	phonebook->all_contects[contact_amounth%8].last_name = new_contact.last_name; 
	phonebook->all_contects[contact_amounth%8].nickname = new_contact.nickname; 
	phonebook->all_contects[contact_amounth%8].phone_number = new_contact.phone_number; 
	phonebook->all_contects[contact_amounth%8].dark_secret = new_contact.dark_secret;

	contact_amounth++;
}

void check_size_print(std::string string)
{
	if (string.size() > 10)
		std::cout << string.substr(0,9) << '.' << '|';
	else
		std::cout << std::setw(10) << string << '|';
}

void print_search_table(int index, Contacts contact)
{
	std::cout << '|' << std::setw(10) << index << '|';
	check_size_print(contact.first_name);
	check_size_print(contact.last_name);
	check_size_print(contact.nickname);
	std::cout << std::endl;

}

void search_function(PhoneBook phonebook)
{
	std::string index = "9";

	Contacts contact;
	
	while (!(index.size() < 2 && (index.at(0) >= '0' && index.at(0) <= '7')))
	{
		for (int i = 0; i < 8; i++)
		print_search_table(i, phonebook.all_contects[i]);
		std::cout << "which indexes information do you want to see?" << std::endl;
		std::getline(std::cin, index);
		if (!(index.size() < 2 && (index.at(0) >= '0' && index.at(0) <= '7')))
		{
			std::cout << "[\e[0;31mERROR\e[0m] Please enter an index between 0 and 7 without any other characters after it:" << std::endl;
			index.assign("9");
		}
	}

	std::cout << std::endl;
	std::cout << "first name:     " << phonebook.all_contects[index.at(0) - '0'].first_name << std::endl;
	std::cout << "last name:      " << phonebook.all_contects[index.at(0) - '0'].last_name << std::endl;
	std::cout << "nickname:       " << phonebook.all_contects[index.at(0) - '0'].nickname << std::endl;
	std::cout << "phonenumber:    " << phonebook.all_contects[index.at(0) - '0'].phone_number << std::endl;
	std::cout << "darkest secret: " << phonebook.all_contects[index.at(0) - '0'].dark_secret << std::endl;
	std::cout << std::endl;
}

int main (void)
{
	PhoneBook phone_book;
	std::string comand;

	while (1)
	{
		std::cout << "ADD, SEARCH or EXIT?" << std::endl;
		std::getline(std::cin, comand);
		if (comand == "EXIT")
			break ;
		else if (comand == "ADD")
			add_function(&phone_book);
		else if (comand == "SEARCH")
			search_function(phone_book);
	}
}