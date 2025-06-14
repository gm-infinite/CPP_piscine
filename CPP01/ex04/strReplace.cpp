
#include "strReplace.hpp"

static std::string readfile(std::string filename)
{
    std::ifstream file(filename, std::ios::binary); 

    if (!file.is_open())                              
        return "";

    file.seekg(0, std::ios::end);                   
    std::streampos fileSize = file.tellg();         
    file.seekg(0, std::ios::beg);                   

    std::string fileData(fileSize, '\0');            
    file.read(&fileData[0], fileSize);               

    return fileData;                                  
}

void strreplace(std::string filename, std::string s1, std::string s2)
{
	std::string replaced;
	int s1_length = s1.length();
	int s2_length = s2.length();

	if (filename == "" || s1_length < 1)
		return ;
	replaced = readfile(filename);
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
