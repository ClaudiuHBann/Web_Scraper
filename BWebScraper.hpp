#pragma once

#include <iostream>
#include <string>

#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")

class DownloadProgress: public IBindStatusCallback {
public:
	DownloadProgress();
	~DownloadProgress();

	STDMETHOD(OnProgress)(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR wszStatusText);
	STDMETHOD(OnStartBinding)(DWORD dwReserved, IBinding __RPC_FAR* pib);
	STDMETHOD(GetPriority)(LONG __RPC_FAR* pnPriority);
	STDMETHOD(OnLowResource)(DWORD reserved);
	STDMETHOD(OnStopBinding)(HRESULT hresult, LPCWSTR szError);
	STDMETHOD(GetBindInfo)(DWORD __RPC_FAR* grfBINDF, BINDINFO __RPC_FAR* pbindinfo);
	STDMETHOD(OnDataAvailable)(DWORD grfBSCF, DWORD dwSize, FORMATETC __RPC_FAR* pformatetc, STGMEDIUM __RPC_FAR* pstgmed);
	STDMETHOD(OnObjectAvailable)(REFIID riid, IUnknown __RPC_FAR* punk);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	STDMETHOD(QueryInterface)(REFIID riid, void __RPC_FAR* __RPC_FAR* ppvObject);
};

class BWebScraper {
public:
	BWebScraper();
	~BWebScraper();

	static void URLToFile(const std::string& url, const std::string& file, const bool infoBasic = true, const bool infoExtended = false);
	static std::string URLToFileCache(const std::string& url, std::string& file, const bool infoBasic = true, const bool infoExtended = false, const bool asRef = false);
};