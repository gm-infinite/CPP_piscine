/* ************************************************************************************** */
/*                                                █████   ████ ███████████  █████ █████   */
/*   Contacts.cpp                                 ░░███   ███░ ░░███░░░░░███░░███ ░░███   */
/*                                                 ░███  ███    ░███    ░███ ░░███ ███    */
/*   By: kuzyilma <kuzyilma@student.42istanbul.com ░███████     ░██████████   ░░█████     */
/*                                                 ░███░░███    ░███░░░░░███   ░░███      */
/*   Created: 2025/06/02 by kuzyilma               ░███ ░░███   ░███    ░███    ░███      */
/*                                                 █████ ░░████ ███████████     █████     */
/*                                                 ░░░░░   ░░░░ ░░░░░░░░░░░     ░░░░░     */
/* ************************************************************************************** */

#pragma once
#ifndef CONTACTS_HPP
#define CONTACTS_HPP

#include <string>

class Contacts {
public:

	std::string first_name;
    std::string last_name;
    std::string nickname;
	std::string phone_number;
	std::string dark_secret;

};

#endif
