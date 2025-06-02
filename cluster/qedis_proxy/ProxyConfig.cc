#include <vector>
#include <iostream>

#include "ProxyConfig.h"
#include "ConfigParser.h"

namespace qedis
{

static void EraseQuotes(std::string& str)
{
    // convert "hello" to hello
    if (str.size() < 2)
        return;

    if (str[0] == '"' && str[str.size() - 1] == '"')
    {
        str.pop_back();
        str.erase(str.begin());
    }
}

const std::string ProxyConfig::kProxyPrefixPath = "/proxy/qedis_proxy_";
const std::string ProxyConfig::kQedisSetsPath = "/servers";

ProxyConfig g_config;

ProxyConfig::ProxyConfig() :
    bindAddr("127.0.0.1:6379"),
    logDir("log_proxy"),
    clusters({"127.0.0.1:2181"})
{
}

bool LoadProxyConfig(const char* cfgFile, ProxyConfig& cfg)
{
    ConfigParser parser;
    if (!parser.Load(cfgFile))
        return false;
    
    cfg.bindAddr = parser.GetData<std::string>("bind", cfg.bindAddr);
    cfg.logDir = parser.GetData<std::string>("logdir", cfg.logDir);

    return true;
}

} // end namespace qedis

