#include "curlpp_downloader.hpp" // Current header

namespace se {

CurlppDownloader::CurlppDownloader()
: m_requester()
{}

std::ostringstream CurlppDownloader::downloadPage(const std::string& a_url)
{
    curlpp::Cleanup myCleanup;
    std::ostringstream os;

    try	{
	    m_requester.setOpt(curlpp::options::Url(a_url));
    	os << m_requester;
    }
    catch(curlpp::RuntimeError &e) {
		throw;
	}
	catch(curlpp::LogicError &e) {
		throw;
	}

    return os;
}

} // namespace se
