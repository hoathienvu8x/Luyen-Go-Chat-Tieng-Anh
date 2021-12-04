#ifndef _UTIL_H
#define _UTIL_H

#include <string>
#include <vector>

#define PATH_SEPARATOR "/"

bool file_exists(const std::string name);
unsigned int m_rand(int s, int e);
std::string& ltrim(std::string& str, const std::string& chars);
std::string& ltrim(std::string& str);
std::string& rtrim(std::string& str, const std::string& chars);
std::string& rtrim(std::string& str);
std::string& trim(std::string& str, const std::string& chars);
std::string& trim(std::string& str);
std::string load_text_file(std::string filepath);
std::string load_json_file(std::string filepath);
bool save_json_file(std::string filepath, std::string data);
bool save_text_file(std::string filepath, std::string data);
std::vector<std::string> split(std::string str, std::string delimiter);
std::string join(std::vector<std::string> array, std::string delimiter);
std::string join(std::vector<std::string> array);

#endif