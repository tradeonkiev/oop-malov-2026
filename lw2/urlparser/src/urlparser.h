#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

class UrlInfo
{
public:
	UrlInfo(const std::string& url);

	Protocol GetProtocol();
	std::string GetHost();
	int GetPort();
	std::string GetDocument();
	std::string GetOriginalUrl();

	void Print(std::ostream& output) const;

private:
	std::string m_originalUrl;
	Protocol m_protocol;
	std::string m_host;
	int m_port;
	std::string m_document;

	static Protocol ParseProtocol(const std::string& str);
	static int ParsePort(const std::string& str);
	static int GetDefaultPort(Protocol protocol);
	void Parse();
};