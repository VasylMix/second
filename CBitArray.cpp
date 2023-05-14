#include "CBitArray.h"
#include "CMyException.h"


namespace CBA {
	

	CBitArray::CBitArray() { 
		pBitAray = new unsigned int[1];
	}
	CBitArray::CBitArray(unsigned int CountBit) : m_nCntBit{ CountBit }{	
		pBitAray =  new unsigned int[(m_nCntBit / SIZE_UI) + 1] {0};
	}
	CBitArray::CBitArray(const CBitArray& other) : CBitArray(other.m_nCntBit)
	{
		unsigned int SizeArrayInByte = ((m_nCntBit % SIZE_UI != 0) ? (m_nCntBit + SIZE_UI) / 8 : m_nCntBit / 8);
		std::memcpy(pBitAray, other.pBitAray, SizeArrayInByte);
	}
	CBitArray::CBitArray(CBitArray&& other) noexcept
	{
		std::swap(pBitAray, other.pBitAray);
		m_nCntBit = other.m_nCntBit;
		other.m_nCntBit = 0;
	}
	CBitArray::~CBitArray() noexcept {
		if (pBitAray) {
			delete[] pBitAray;
		}
	}

	CBitArray& CBitArray::operator=(const CBitArray& other) {
		if (this != &other) {
			if (m_nCntBit != other.m_nCntBit) {
				delete[] pBitAray;
				pBitAray = nullptr;
			}
			m_nCntBit = other.m_nCntBit;
			if (!pBitAray) {
				pBitAray = new unsigned int[(m_nCntBit / SIZE_UI) + 1] {0};
			}
			unsigned int SizeArrayInByte = ((m_nCntBit % SIZE_UI != 0) ? (m_nCntBit + SIZE_UI) / 8 : m_nCntBit / 8);
			std::memcpy(pBitAray, other.pBitAray, SizeArrayInByte);
		}
		return *this;
	}
	CBitArray& CBitArray::operator=(CBitArray&& other) noexcept {
		if (this != &other) {
			if (pBitAray)
				delete pBitAray;
			m_nCntBit = other.m_nCntBit;
			pBitAray = other.pBitAray;
			other.m_nCntBit = 0;
			other.pBitAray = nullptr;
		}
		return *this;
	}

	CBitArray CBitArray::operator&(const CBitArray& other) const {
		return Compare(other,
			[](unsigned int left, unsigned int right) {return left & right; },
			[](bool left, bool right) {return left && right; });
	}
	CBitArray CBitArray::operator|(const CBitArray& other) const {
		return Compare(other,
			[](unsigned int left, unsigned int right) {return left | right; },
			[](bool left, bool right) {return left || right; });
	}
	CBitArray CBitArray::operator^(const CBitArray& other) const {
		return Compare(other,
			[](unsigned int left, unsigned int right) {return left ^ right; },
			[](bool left, bool right) {return left != right; });
	}

	CBitArray& CBitArray::operator--() noexcept {
		unsigned int Mask{ 0x80000000 }, flag{ 0 };
		for (int i = m_nCntBit / SIZE_UI; i >= 0 && pBitAray; --i) {
			if (flag) {
				flag = pBitAray[i] & Mask;
				pBitAray[i] <<= 1;
				pBitAray[i] |= 1;
			}
			else {
				flag = pBitAray[i] & Mask;
				pBitAray[i] <<= 1;
			}
		}
		return *this;
	}
	CBitArray& CBitArray::operator++() noexcept {
		unsigned int Mask{ 1 }, flag{ 0 };
		for (size_t i = 0; i <= m_nCntBit / SIZE_UI && pBitAray; ++i)
		{
			if (i == m_nCntBit / SIZE_UI)
				SetBitByNubmer(false, m_nCntBit);
			if (flag)
			{
				flag = pBitAray[i] & Mask;
				pBitAray[i] >>= 1;
				pBitAray[i] |= 0x80000000;
			}
			else {
				flag = pBitAray[i] & Mask;
				pBitAray[i] >>= 1;
			}
		}
		return *this;
	}
	CBitArray CBitArray::operator++(int) {
		CBitArray temp(*this);
		++(*this);
		return temp;
	}
	CBitArray CBitArray::operator--(int) {
		CBitArray temp(*this);
		--(*this);
		return temp;
	}
	bool CBitArray::operator[](unsigned int nIndex) const {
		return GetBitByNubmer(nIndex);
	}

	std::istream& operator>>(std::istream& in, CBitArray& obj) {
		if (in.good()) {
			int bit = 0;
			for (unsigned int i = 1; i <= obj.m_nCntBit && obj.pBitAray && !in.eof(); ++i) {
				in >> bit;
				if (in.fail()) 
					throw CMyBadStream("Unable to read data, problems with input stream\n");
				else
					obj.SetBitByNubmer(bit ? 1 : 0, i);
			}
		} else
			throw CMyBadStream("Problems with intput stream\n");
		return in;
	}
	std::ostream& operator<<(std::ostream& out, const CBitArray& obj) {
		if (out.good()) {
			for (unsigned int i = 1; i <= obj.m_nCntBit; ++i) {
				out << obj[i];
				if (out.fail())
					throw CMyBadStream("Unable to write data, problems with output stream\n");
			}
		} else
			throw CMyBadStream("Problems with output stream\n");
		return out;
	}

	

	bool CBitArray::SetBitByNubmer(bool nValueBit, unsigned int nNumber) {
		if (--nNumber >= m_nCntBit || pBitAray == nullptr)
			throw CMyOutOfRange();
		unsigned int nIndex = nNumber / SIZE_UI, Mask{ 1 };
		Mask <<= (SIZE_UI - 1 - (nNumber % SIZE_UI));
		if (nValueBit)
			pBitAray[nIndex] |= Mask;
		else
			pBitAray[nIndex] &= (~Mask);
		return nValueBit;
	}
	bool CBitArray::GetBitByNubmer(unsigned int nIndex) const {
		if (--nIndex >= m_nCntBit || pBitAray == nullptr)
			throw CMyOutOfRange();
		unsigned int nPosition = nIndex / SIZE_UI, Mask{ 1 };
		return Mask & (pBitAray[nPosition] >> (SIZE_UI - 1 - (nIndex % SIZE_UI))) ? true : false;
	}
	unsigned int CBitArray::GetCntBitsWithValue(bool nValue) const noexcept {
		unsigned int Count1{ 0 }, Count0{ 0 };
		for (unsigned int i = 1; i <= m_nCntBit && pBitAray; ++i)
			if ((*this)[i])
				Count1++;
			else
				Count0++;
		return nValue ? Count1 : Count0;
	}


	CBitArray CBitArray::Compare(const CBitArray& other,
		unsigned int(*compare1)(unsigned int, unsigned int),
		bool(*compare2)(bool, bool)) const 
	{
		CBitArray Array(m_nCntBit);
		if (m_nCntBit == other.m_nCntBit && pBitAray && other.pBitAray) {
			for (unsigned int i = 0; i <= m_nCntBit / SIZE_UI; ++i)
				Array.pBitAray[i] = compare1(pBitAray[i], other.pBitAray[i]);
		} else {
			unsigned int Count{ m_nCntBit > other.m_nCntBit ? other.m_nCntBit : m_nCntBit };
			Array = CBitArray(Count);
			for (unsigned int i = 1; i <= Count; ++i)
				Array.SetBitByNubmer(compare2((*this)[i], other[i]), i);
		}
		return Array;
	}

}


