#pragma once
#include <iostream>


namespace CBA {
	class CBitArray {
	public:
		CBitArray();
		explicit CBitArray(unsigned int CountBit);
		CBitArray(const CBitArray& other);
		CBitArray(CBitArray&& other) noexcept;
		~CBitArray() noexcept;

	private:
		unsigned int* pBitAray{ nullptr }, m_nCntBit{ 32 },
			SIZE_UI = sizeof(unsigned int) * 8;
	public:
		CBitArray& operator=(const CBitArray& other);
		CBitArray& operator=(CBitArray&& other) noexcept;
		CBitArray operator&(const CBitArray& other) const;
		CBitArray operator|(const CBitArray& other) const;
		CBitArray operator^(const CBitArray& other) const;
		CBitArray& operator--() noexcept;
		CBitArray& operator++() noexcept;
		CBitArray operator--(int);
		CBitArray operator++(int);
		bool operator[](unsigned int nIndex) const;
		friend std::istream& operator>>(std::istream& in, CBitArray& obj);
		friend std::ostream& operator<<(std::ostream& out, const CBitArray& obj);

		bool SetBitByNubmer(bool nValueBit, unsigned int nNumber) ;
		bool GetBitByNubmer(unsigned int nIndex) const;
		unsigned int GetCntBitsWithValue(bool bValue) const noexcept;
	private:
		CBitArray Compare(const CBitArray& other, unsigned int (*fun1)(unsigned int, unsigned int), bool (*fun2)(bool, bool)) const;
	};
}


