
#include "Data.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
Data::Data(void) : data_int(0)
{ }

Data::Data(int data_int) : data_int(data_int)
{ }

Data::Data(const Data& other):  data_int(other.getdata_int())
{ }

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

Data::~Data(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

Data& Data::operator=(const Data& other)
{
	if (this != &other)
		this->setdata_int(other.getdata_int());
	return *this;
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

int Data::getdata_int(void) const {
	return this->data_int;
}

void Data::setdata_int(const int data_int) {
	this->data_int = data_int;
}
