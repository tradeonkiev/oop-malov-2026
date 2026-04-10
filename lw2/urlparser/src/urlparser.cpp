#include "urlparser.h"
#include <algorithm>
#include <regex>

UrlInfo::UrlInfo(const std::string& url)
	: m_originalUrl(url)
	, m_protocol(Protocol::HTTP)
	, m_port(0)
{
	Parse();
}

void UrlInfo::Parse()
{
	// TODO: вспомнить синтаксис регулярок
	std::regex urlRegex(

		R"(^([a-z]+)://([^/:]+)(?::(\d+))?(?:/(.*))?$)", std::regex::icase);

	std::smatch match;
	if (!std::regex_match(m_originalUrl, match, urlRegex))
		throw std::invalid_argument("Invalid URL format: " + m_originalUrl);

	m_protocol = ParseProtocol(match[1].str());

	m_host = match[2].str();
	if (m_host.empty())
		throw std::invalid_argument("Empty host in URL: " + m_originalUrl);

	if (match[3].matched)
		m_port = ParsePort(match[3].str());
	else
		m_port = GetDefaultPort(m_protocol);

	m_document = match[4].matched ? match[4].str() : "";
}

Protocol UrlInfo::ParseProtocol(const std::string& str)
{
	std::string lower = str;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

	if (lower == "http")
		return Protocol::HTTP;
	if (lower == "https")
		return Protocol::HTTPS;
	if (lower == "ftp")
		return Protocol::FTP;
	throw std::invalid_argument("Unknown protocol: " + str);
}

int UrlInfo::GetDefaultPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	}
	throw std::logic_error("Unhandled protocol");
}

int UrlInfo::ParsePort(const std::string& str)
{
	int port;
	try
	{
		port = std::stoi(str);
	}
	catch (...)
	{
		throw std::invalid_argument("Port is not a number: " + str);
	}

	if (port < 1 || port > 65535)
		throw std::out_of_range("Port out of range: " + str);

	return port;
}

Protocol UrlInfo::GetProtocol()
{
	return m_protocol;
}
std::string UrlInfo::GetHost()
{
	return m_host;
}
int UrlInfo::GetPort()
{
	return m_port;
}
std::string UrlInfo::GetDocument()
{
	return m_document;
}
std::string UrlInfo::GetOriginalUrl()
{
	return m_originalUrl;
}

void UrlInfo::Print(std::ostream& output) const
{
	output << m_originalUrl << "\n";
	output << "HOST: " << m_host << "\n";
	output << "PORT: " << m_port << "\n";
	output << "DOC: " << m_document << "\n";
}