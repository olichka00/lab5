#include <iostream>
#include <fstream>
#include <string>
#include "cWork.h"

CWorkspace::CWorkspace(CDataChain &data): m_refChain(data) {}
//~CWorkspace(void) {}
//Ініціалізує повну послідовність цифр
void CWorkspace::Init(int nDepth, int nLength) {
	if (nDepth != -1)
		m_refChain.Generate(nDepth, nLength);
	else {
		CDataPi pi;
		pi.Generate(-1, nLength);
		m_refChain.SetM_sChain(pi.GetString());
	}

}

	//Повертає стрічку із повною послідовністю цифр.
const char *CWorkspace::GetChainString() {
	return m_refChain.GetFullString();
}

bool CWorkspace::Save(std::string &sFilePath) {
	if (sFilePath == "")
		return false;

	std::string save = GetChainString();
	std::ofstream saveFile(sFilePath, std::fstream::app);

	saveFile << m_refChain.GetLength(save.c_str()) << std::endl;
	saveFile << GetChainString() << std::endl;

	saveFile << m_aLinks.size() << std::endl;
	for (int i = 0; i < m_aLinks.size(); i++) {
		m_aLinks[i]->Save(saveFile);
	}
		
	saveFile.close();

	return true;
}

bool CWorkspace::Load(std::string &sFilePath) {
	std::ifstream loadFile(sFilePath);
		
	if (!loadFile.is_open())
		return false;
		
	std::string str, resultStr;
	int i = 0, fCheck = -1;
	while (std::getline(loadFile, str)) {
		if (i == 0) {
			i++;
			continue;
		}

		if (str == "") {
			// i + 1 - рядок із кількістю links
			fCheck = i + 1;
		}

		if (i == fCheck) {
			int end = stoi(str);
			for (int j = 0; j < end; j++) {
				AddLink(-1, -1, new CLink(m_refChain));
				m_aLinks[m_aLinks.size() - 1]->Load(loadFile);
			}

			break;
		}


		m_refChain.SetM_sChain(m_refChain.GetFullString() + str);
		i++;
	}

	loadFile.close();

	return true;
}

int CWorkspace::Find(const char *sSubStr, int nPos) {
	return m_refChain.Find(sSubStr, nPos);
}

bool CWorkspace::AddLink(int nStartPos, int nLength, CLink* pLink) {
	pLink->SetM_nPos(nStartPos);
	pLink->SetM_nSize(nLength);

	m_aLinks.push_back(pLink);
	return true;
}

bool CWorkspace::RemoveLink(int nPosInList) {
	if (nPosInList < 0 || nPosInList >= m_aLinks.size()) {
		std::cout << "Error no such element with this id in list";
		return false;
	}

	m_aLinks.erase(m_aLinks.begin() + nPosInList);
	return true;
}

bool CWorkspace::GetAllLinks(LinksArray &aLinks) {
	for (int i = 0; i < m_aLinks.size(); i++) {
		aLinks.push_back(m_aLinks[i]);
	}

	return true;
}

void CWorkspace::ShowAll() {
	for (int i = 0; i < m_aLinks.size(); i++) {
		std::cout << "Pos: " << m_aLinks[i]->GetM_nPos();
		std::cout << " Size: " << m_aLinks[i]->GetM_nSize() << std::endl;
	}
}

	//Добавляє новий лінк типу URL для першого входження підстрічки sSubStr
bool CWorkspace::AddURL(const char *sSubStr, const char *sURL) {
	if (m_refChain.Find(sSubStr) == -1)
		return false;

	CLinkURL *url = new CLinkURL(m_refChain);
	int positionStart = m_refChain.Find(sSubStr);
	std::string charToStr = sSubStr;

	url->AddUrl(sURL);
	url->SetM_nPos(positionStart);
	url->SetM_nSize(m_refChain.GetLength(charToStr.c_str()));

	m_aLinks.push_back(url);
	return true;
}

//Добавляє новий лінк типу Person для першого входження підстрічки sSubStr
bool CWorkspace::AddPerson(const char *sSubStr, int nGroup, const char *sName) {
	if (m_refChain.Find(sSubStr) == -1)
		return false;

	CLinkPerson *person = new CLinkPerson(m_refChain);
	std::string str = sSubStr;
	int position = m_refChain.Find(sSubStr);
	person->SetGroup(nGroup);
	person->SetName(sName);
	person->SetM_nSize(m_refChain.GetLength(str.c_str()));
	person->SetM_nPos(position);

	m_aLinks.push_back(person);
	return true;
}

bool CWorkspace::TestPosition(int nPos, LinksArray &aNearestLinks) {
	if (nPos < 0 || nPos > m_aLinks.size() - 1)
		return false;

	for (int i = 0; i < m_aLinks.size(); i++) {
		if (m_aLinks[i]->GetM_nPos() == nPos) {
			aNearestLinks.push_back(m_aLinks[i]);
		}
	}
	return true;
}

bool CWorkspace::TestInterval(int nStartPos, int nEndPos, LinksArray &aNearestLinks) {
	std::string chain = GetChainString();

	if (nStartPos < 0 || nStartPos > nEndPos || nEndPos > size(chain) - 1)
		return false;

	for (int i = 0; i < m_aLinks.size(); i++) {
		if (m_aLinks[i]->GetM_nPos() >= nStartPos && m_aLinks[i]->GetM_nPos() <= nEndPos)
			aNearestLinks.push_back(m_aLinks[i]);
	}

	return true;
}
