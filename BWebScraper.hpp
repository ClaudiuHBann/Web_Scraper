#pragma once

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#include <iostream>
#include <string>

#include <future>

#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")

/**
 * Implementation of a bind status callback for URLDownloadTo(Cache)File
 *
 * @see [IBindStatusCallback](https://docs.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/ms775060(v=vs.85))
 */
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

/**
 * Implementation of a basic web scraper
 */
class BWebScraper {
public:
	BWebScraper();
	~BWebScraper();

	/**
	 * Downloads data from "url" and saves it to "file"
	 *	with basic and/or extended info when downloading
	 *
	 * @param[in] website's url
	 * @param[in] the file where the data will be downloaded
	 * @param[in] basic info about downloading
	 * @param[in] extended info about downloading
	 */
	static void URLToFile(const std::string& url, const std::string& file, const bool infoBasic = true, const bool infoExtended = false);

	/**
	 * Downloads data from "url" and saves it to "file"
	 *	with basic and/or extended info when downloading asynchronously
	 *
	 * @param[in] website's url
	 * @param[in] the file where the data will be downloaded
	 * @param[in] basic info about downloading
	 * @param[in] extended info about downloading
	 *
	 * @return the result of the async operation
	 */
	static std::future<void> URLToFileAsync(const std::string& url, const std::string& file, const bool infoBasic = true, const bool infoExtended = false);

	/**
	 * Downloads data from "url" and saves it to cache
	 *	with basic and/or extended info when downloading
	 *
	 * @param[in] website's url
	 * @param[out] the path of the cached file if "asRef" is true
	 * @param[in] basic info about downloading
	 * @param[in] extended info about downloading
	 * @param[in] if false the method returns the cached file path else it will assign the "file" variable to it
	 *
	 * @return the path of the cached file if "asRef" is false
	 */
	static std::string URLToFileCache(const std::string& url, std::string& file, const bool infoBasic = true, const bool infoExtended = false, const bool asRef = false);

	/**
	 * Downloads data from "url" and saves it to cache
	 *	with basic and/or extended info when downloading asynchronously
	 *
	 * @param[in] website's url
	 * @param[out] the path of the cached file if "asRef" is true
	 * @param[in] basic info about downloading
	 * @param[in] extended info about downloading
	 * @param[in] if false the method returns the result of the async operation (the path of the cached file)
	 *	else it will assign the "file" variable to the path of the cached file
	 *
	 * @return the result of the async operation (the path of the cached file) if "asRef" is false
	 */
	static std::future<std::string> URLToFileCacheAsync(const std::string& url, std::string& file, const bool infoBasic = true, const bool infoExtended = false, const bool asRef = false);
};