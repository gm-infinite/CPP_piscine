
#include "strReplace.hpp"

void strreplace(std::string filename, std::string s1, std::string s2)
{
	std::string replaced;
	std::ifstream file(filename.c_str()); 
	int s1_length = s1.length();
	int s2_length = s2.length();

	if (filename == "" || s1_length < 1)
		return ;

	std::ostringstream buffer;
    buffer << file.rdbuf();
    replaced = buffer.str();
    file.close();

	if (replaced.length() > 0)
	{
		size_t found_pos = replaced.find(s1, 0);
		while (found_pos != std::string::npos)
		{
			replaced.erase(found_pos, s1_length);
			replaced.insert(found_pos, s2);
			found_pos = replaced.find(s1, found_pos + s2_length);
		}
	}
	
	std::ofstream file_replaced((filename + ".replace").c_str());
	if (file_replaced.is_open())
		file_replaced << replaced;
}
