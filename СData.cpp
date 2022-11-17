#include <iostream>
#include <string>
#include <iomanip>
#include "cData.h"

CDataChain::~CDataChain(void) {}

void CDataSimple::Generate(int nDepth, int nMaxLength) {
	int i = 0;
	std::string generateStr = "";
	while (size(generateStr) < nMaxLength) {
		if (i > nDepth)
			break;

		generateStr += std::to_string(i);
		i++;
	}
	m_sChain = generateStr + "\n";
}

size_t CDataSimple::GetLength(const char *sSubStr) {
	return size(m_sChain);
}

const char *CDataSimple::GetFullString() {
	return m_sChain.c_str();
}

void CDataSimple::SetM_sChain(std::string str) {
	m_sChain = str;
}

int CDataSimple::Find(const char *sSubStr, int nPos) {
	bool f = false;
	std::string sSubStr1 = sSubStr;
	int resultId = -1;
	for (int i = nPos; i < size(m_sChain); i++) {
		if (m_sChain[i] == sSubStr1[0]) {
			if (size(sSubStr1) <= size(m_sChain) - i) {
				int count = 0;
				int id = i;
				resultId = i;

				for (int j = 0; j < size(sSubStr1); j++) {
					if (m_sChain[id] == sSubStr1[j]) {
						count++;
						id++;
					}
				}

				if (count == size(sSubStr1)) {
					f = true;
					break;
				}
			}
		}
	}

	if (f)
		return resultId;
	else
		return -1;
}

void CDataPi::Generate(int nDepth, int nLength) {
	double Pi = 4 * atan(1);

	std::ofstream file("data.txt");
	file << std::setprecision(nLength) << Pi;
	file.close();

	std::string str;
	std::ifstream inputFile("data.txt");
	inputFile >> str;
	inputFile.close();

	for (int i = 0; i < size(str); i++) {
		if (str[i] == '.')
			continue;

		m_sChain += str[i];
	}
}

size_t CDataPi::GetLength(const char *sSubStr) {
	return size(m_sChain);
}

int CDataPi::Find(const char *sSubStr, int nPos) {
	bool f = false;
	std::string sSubStr1 = sSubStr;
	int resultId = -1;
	for (int i = nPos; i < size(m_sChain); i++) {
		if (m_sChain[i] == sSubStr1[0]) {
			if (size(sSubStr1) <= size(m_sChain) - i) {
				int count = 0;
				int id = i;
				resultId = i;

				for (int j = 0; j < size(sSubStr1); j++) {
					if (m_sChain[id] == sSubStr1[j]) {
						count++;
						id++;
					}
				}

				if (count == size(sSubStr1)) {
					f = true;
					break;
				}
			}
		}
	}

	if (f)
		return resultId;
	else
		return -1;
}

const char *CDataPi::GetFullString() {
	return m_sChain.c_str();
}

void CDataPi::SetM_sChain(std::string str) {
	m_sChain = str;
}

std::string CDataPi::GetString() {
	return m_sChain;
}