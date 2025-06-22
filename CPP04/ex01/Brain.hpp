
#ifndef BRAIN_HPP
#define BRAIN_HPP
#include <string>
#include <iostream>

class Brain {

public:
	Brain(void);
	~Brain(void);
	Brain(const Brain& other);
	Brain& operator=(const Brain& other);

	const std::string& getIdea(int i) const;
	void setIdea(int i, const std::string& idea);

private:
	std::string ideas[100];
};

#endif /* BRAIN_HPP */