#include <fstream>
#include <vector>
#include <string>
#include "cLink.h"

CLink::CLink(CDataChain &refChain): m_refChain(refChain) {
	m_nPos = -1;
	m_nSize = -1;
}
	
CLink::~CLink(void) {}

//Пробує прив"язати об"єкт до підстрічки у послідовності
//bool Attach(const char *sSubStr);
	
//Форматований вивід на консоль
//virtual void Output(std::ostream &os);

//Зберігає об"єкт у вихідному потоці
bool CLink::Save(std::ostream &so) {
	so << m_nPos << " " << m_nSize << std::endl;
	return true;
}

CLinkURL::~CLinkURL(void) {}

//Зчитує об"єкт із вхідного потоку
bool CLink::Load(std::istream &is) {
	std::string str;
	std::getline(is, str);
	if (str == "")
		std::cout << "Error load";
	else {
		std::string strNum;
		int j = 0;
		while (str[j] != ' ') {
			strNum += str[j];
			j++;
		}
		m_nPos = std::stoi(strNum);
		strNum = "";
		for (++j; j < size(str); j++) {
			strNum += str[j];
		}
		m_nSize = std::stoi(strNum);
		return true;
	}

	return false;
}

void CLink::SetM_nPos(int nPos) {
	m_nPos = nPos;
}

void CLink::SetM_nSize(int nSize) {
	m_nSize = nSize;
}

int CLink::GetM_nPos() {
	return m_nPos;
}

int CLink::GetM_nSize() {
	return m_nSize;
}

typedef std::vector<CLink *> LinksArray;

CLinkURL::CLinkURL(CDataChain &refChain): CLink(refChain) {}

void CLinkURL::AddUrl(const char *sSubStr) {
	m_sURL = sSubStr;
}

CLinkPerson::CLinkPerson(CDataChain &refChain): CLink(refChain) {
	m_nGroupCode = -1;
}
CLinkPerson::~CLinkPerson(void) {}
void CLinkPerson::SetGroup(int group) {
	m_nGroupCode = group;
}

void CLinkPerson::SetName(std::string name) {
	m_sName = name;
}