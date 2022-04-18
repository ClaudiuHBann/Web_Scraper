#include "BWebScraper.hpp"

DownloadProgress::DownloadProgress() {

}

DownloadProgress::~DownloadProgress() {

}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText) {
	std::cout << "OnProgess: Downloaded " << ulProgress << " of " << ulProgressMax << " byte(s). Status: ";
	if(wszStatusText) {
		std::wcout << wszStatusText;
	} else {
		std::cout << '-';
	}
	std::cout << " (" << ulStatusCode << ')' << std::endl;

	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnStartBinding(DWORD dwReserved, IBinding __RPC_FAR* pib) {
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::GetPriority(LONG __RPC_FAR* pnPriority) {
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnLowResource(DWORD reserved) {
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnStopBinding(HRESULT hresult, LPCWSTR szError) {
	std::cout << "OnStopBinding: Status: ";
	if(szError) {
		std::wcout << szError;
	} else {
		std::cout << '-';
	}
	std::cout << " (" << hresult << ')' << std::endl;

	return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::GetBindInfo(DWORD __RPC_FAR* grfBINDF, BINDINFO __RPC_FAR* pbindinfo) {
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR* pformatetc, STGMEDIUM __RPC_FAR* pstgmed) {
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnObjectAvailable(REFIID riid, IUnknown __RPC_FAR* punk) {
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG __stdcall) DownloadProgress::AddRef() {
	return 0;
}

STDMETHODIMP_(ULONG __stdcall) DownloadProgress::Release() {
	return 0;
}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::QueryInterface(REFIID riid, void __RPC_FAR* __RPC_FAR* ppvObject) {
	return E_NOTIMPL;
}

BWebScraper::BWebScraper() {

}

BWebScraper::~BWebScraper() {

}

void BWebScraper::URLToFile(const std::string& url, const std::string& file, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/) {
	HRESULT hResult;
	if(infoExtended) {
		DownloadProgress dp;
		hResult = URLDownloadToFile(nullptr, url.c_str(), file.c_str(), 0, (IBindStatusCallback*)&dp);
	} else {
		hResult = URLDownloadToFile(nullptr, url.c_str(), file.c_str(), 0, nullptr);
	}

	if(!infoBasic) {
		return;
	}

	switch(hResult) {
		case S_OK:
			std::cout << url << " has been downloaded to " << file << '.' << std::endl;
			break;
		case E_OUTOFMEMORY:
			std::cout << "Buffer length invalid, or insufficient memory!" << std::endl;
			break;
		case INET_E_DOWNLOAD_FAILURE:
			std::cout << url << " is invalid!" << std::endl;
			break;
		default:
			std::cout << "Other error: " << hResult << '.' << std::endl;
			break;
	}
}

std::string BWebScraper::URLToFileCache(const std::string& url, std::string& file, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/, const bool asRef/* = false*/) {
	std::string toReturn("");
	char buffer[MAX_PATH];

	HRESULT hResult;
	if(infoExtended) {
		DownloadProgress dp;
		hResult = URLDownloadToCacheFile(nullptr, url.c_str(), buffer, MAX_PATH, 0, (IBindStatusCallback*)&dp);
	} else {
		hResult = URLDownloadToCacheFile(nullptr, url.c_str(), buffer, MAX_PATH, 0, nullptr);
	}

	if(asRef) {
		file.assign(buffer);
	} else {
		toReturn.assign(buffer);
	}

	if(infoBasic) {
		switch(hResult) {
			case S_OK:
				std::cout << url << " has been downloaded to " << file << '.' << std::endl;
				break;
			case E_OUTOFMEMORY:
				std::cout << "Buffer length invalid, or insufficient memory!" << std::endl;
				break;
			case INET_E_DOWNLOAD_FAILURE:
				std::cout << url << " is invalid!" << std::endl;
				break;
			default:
				std::cout << "Other error: " << hResult << '.' << std::endl;
				break;
		}
	}

	return toReturn;
}

std::future<void> BWebScraper::URLToFileAsync(const std::string& url, const std::string& file, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/) {
	return std::async(std::launch::async, [url, file, infoBasic, infoExtended] {
		URLToFile(url, file, infoBasic, infoExtended);
	});
}

std::future<std::string> BWebScraper::URLToFileCacheAsync(const std::string& url, std::string& file, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/, const bool asRef/* = false*/) {
	return std::async(std::launch::async, [url, &file, infoBasic, infoExtended, asRef] {
		return URLToFileCache(url, file, infoBasic, infoExtended, asRef);
	});
}

std::vector<std::string> BWebScraper::URLToAttributeValues(const std::string& url, const std::string& attribute, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/) {
	std::vector<std::string> values;
	URLToAttributeValues(url, attribute, values, infoBasic, infoExtended);
	return values;
}

void BWebScraper::URLToAttributeValues(const std::string& url, const std::string& attribute, std::vector<std::string>& values, const bool infoBasic/* = true*/, const bool infoExtended/* = false*/) {
	std::string path;
	URLToFileCache(url, path, infoBasic, infoExtended, true);

	BStringParser bsp;
	std::string gifsAsString = BMiscellaneous::FileAsString(path);
	std::vector<size_t> gifsDataWebms = bsp.FindAllOccurrences(gifsAsString, attribute);
	for(size_t i = 0; i < gifsDataWebms.size(); i++) {
		values.push_back(bsp.AttributeValue(gifsAsString, attribute, gifsDataWebms[i]));
	}
}