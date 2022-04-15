#include "BWebScraper.hpp"

DownloadProgress::DownloadProgress() {

}

DownloadProgress::~DownloadProgress() {

}

STDMETHODIMP_(HRESULT __stdcall) DownloadProgress::OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText) {
	std::cout << "Downloaded " << ulProgress << " of " << ulProgressMax << " byte(s). Status Code = " << ulStatusCode << std::endl;
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
	return E_NOTIMPL;
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
		hResult = URLDownloadToFile(nullptr, std::wstring(url.begin(), url.end()).c_str(), std::wstring(file.begin(), file.end()).c_str(), 0, (IBindStatusCallback*)&dp);
	} else {
		hResult = URLDownloadToFile(nullptr, std::wstring(url.begin(), url.end()).c_str(), std::wstring(file.begin(), file.end()).c_str(), 0, nullptr);
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
