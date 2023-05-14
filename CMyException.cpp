#include "CMyException.h"
//
//CMyOutOfRange::CMyOutOfRange() noexcept : std::exception("You are out of array range\n")  {}
//
//CMyOutOfRange::CMyOutOfRange(const char* msg) noexcept : std::exception(msg) {}

 const char* CMyOutOfRange::what() const noexcept {
	//return std::exception::what();
	return "wsjgg";
}

CMyBadStream::CMyBadStream() noexcept : std::exception("Error with stream\n") {}

CMyBadStream::CMyBadStream(const char* msg) noexcept : std::exception(msg) {}

inline const char* CMyBadStream::what() const noexcept {
	return std::exception::what();
}