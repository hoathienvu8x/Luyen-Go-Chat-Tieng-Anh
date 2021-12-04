#include <sys/stat.h>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <limits.h>
#include <unistd.h>
#include <util.h>

unsigned int m_rand(int s, int e) {
    unsigned int v = rand() % (e - s + 1) + s;
    return v;
}
bool file_exists(const std::string name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}
std::string& ltrim(std::string& str, const std::string& chars) {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
std::string& ltrim(std::string& str) {
    return ltrim(str, "\t\n\v\f\r ");
}
std::string& rtrim(std::string& str, const std::string& chars) {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
std::string& rtrim(std::string& str) {
    return rtrim(str, "\t\n\v\f\r ");
}
std::string& trim(std::string& str, const std::string& chars) {
    return ltrim(rtrim(str, chars), chars);
}
std::string& trim(std::string& str) {
    return trim(str, "\t\n\v\f\r ");
}
std::string load_text_file(std::string filepath) {
    std::string data = "";
    try {
        std::ifstream is (filepath, std::ifstream::binary);
        if (is) {
            is.seekg (0, is.end);
            int length = is.tellg();
            is.seekg (0, is.beg);
            char * buffer = new char [length];
            is.read (buffer,length);
            if (is) {
                data = std::string(buffer, length);
            }
            is.close();
            delete[] buffer;
        }
    } catch (...) {}
    return data;
}
std::string load_json_file(std::string filepath) {
    std::string json = load_text_file(filepath);
    json = trim(json);
    if (json.empty()) return "";
    if (json.at(0) == '{' && json.at(json.length()-1) == '}') return json;
    if (json.at(0) == '[' && json.at(json.length()-1) == ']') return json;
    return "";
}
bool save_text_file(std::string filepath, std::string data) {
    bool saved = false;
    try {
        std::ofstream out(filepath);
        out << data;
        out.close();
        saved = true;
    } catch(...) {}
    return saved;
}
bool save_json_file(std::string filepath, std::string data) {
    data = trim(data);
    if (data.empty()) return false;
    if (data.at(0) == '{' && data.at(data.length()-1) == '}') {
        return save_text_file(filepath, data);
    }
    if (data.at(0) == '[' && data.at(data.length()-1) == ']') {
        return save_text_file(filepath, data);
    }
    return false;
}
std::vector<std::string> split(std::string str, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = str.find (delimiter, pos_start)) != std::string::npos) {
        token = str.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (str.substr (pos_start));
    return res;
}
std::string join(std::vector<std::string> array, std::string delim) {
    std::stringstream res;
    copy(array.begin(), array.end(), std::ostream_iterator<std::string>(res, delim.c_str()));
    std::string s = res.str();
    s = trim(s);
    return trim(s,delim);
}
std::string join(std::vector<std::string> array) {
    return join(array, ",");
}