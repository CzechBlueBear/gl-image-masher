#include <iostream>
#include <fstream>
#include <vector>
#include "FileUtils.hpp"

std::string loadFileAsString(const std::string &path) {
    std::fstream in(path, std::ios_base::in | std::ios_base::binary);
    if (in.bad()) {
    	return "";
    }

    // load the contents into buffer
    // FIXME: clumsy
    std::vector<char> buf;
    buf.reserve(1024);
    for (;;) {
        int c = in.get();
        if (c < 0) break;
        buf.push_back(static_cast<char>(c));
    }
    if (in.bad()) {
        throw "";
    }

    // add terminating zero to make a valid C-style string
    buf.push_back('\0');

    return std::string(buf.data());
}
