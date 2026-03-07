
#ifndef DATA_HPP
#define DATA_HPP

class Data {

public:
	Data(void);
	~Data(void);
	Data(int data_int);
	Data(const Data& other);
	Data& operator=(const Data& other);

	int getdata_int(void) const;
	void setdata_int(const int data_int);

private:
	int data_int;
};

#endif /* DATA_HPP */