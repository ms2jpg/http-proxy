#include <iostream>
#include "HTTP.h"


void HTTP::addHeader(const std::string& header, const std::string& value) {
    auto *h = new Header(header, value);
    this->headers.push_back(h);
}

unsigned long HTTP::contentLength() {
    Header* h = this->getHeader("Content-Length");
    if (h != nullptr) {
        try {
            long contentLength = std::stol(h->value);
            return contentLength < 0 ? 0 : contentLength;
        } catch (std::invalid_argument &err) {
            return 0;
        } catch (std::out_of_range &err) {
            return 0;
        }
    }
    return 0;
}

Header* HTTP::getHeader(std::string headerName) {
    headerName = HTTP::tolower(headerName);
    for (Header *h : this->headers) {
        if (HTTP::tolower(h->header) == headerName) {
            return h;
        }
    }
    return nullptr;
}

std::string HTTP::tolower(std::string in) {
    std::locale loc;
    for(auto &elem : in) {
        elem = std::tolower(elem, loc);
    }
    return in;
}

std::string HTTP::trim(std::string& str)
{
    str.erase(str.find_last_not_of(' ')+1);         //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    return str;
}

HTTP::~HTTP() {
    for (auto header : this->headers) {
        delete header;
    }
}

void HTTP::removeHeader(const std::string& header) {
    for (auto it = this->headers.begin(); it != headers.end();) {
        if (HTTP::tolower(header) == HTTP::tolower((*it)->header)) {
            this->headers.erase(it);
        } else {
            it++;
        }
    }
}
