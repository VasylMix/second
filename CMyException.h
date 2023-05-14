#pragma once
#include <exception>

class CMyOutOfRange : public std::exception {
public:
	/*CMyOutOfRange() noexcept;
	explicit CMyOutOfRange(const char* msg) noexcept;*/
	 const char* what() const noexcept override ;
};

class CMyBadStream : public std::exception
{
public:
	CMyBadStream() noexcept;
	explicit CMyBadStream(const char* msg) noexcept;
	inline const char* what() const noexcept override;
};
