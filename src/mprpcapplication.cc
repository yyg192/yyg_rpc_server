#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp()
{
    std::cout<<"format: command -i <configfile>" << std::endl;
}

void MprpcApplication::Init(int argc, char **argv)
{ //provider -i config.conf
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while((c = getopt(argc, argv, "i:")) != -1) //如果我们的agrv参数里面有i的话就说明我们指定了配置文件了。
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?': //这个问号代表我们不希望出现的其他参数 这里可以打印一下允许的参数
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':': //出现了-i 但是没有给出文件
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件了 rpcserver_ip=  rpcserver_port   zookeeper_ip=  zookepper_port=
    m_config.LoadConfigFile(config_file.c_str());

    // std::cout << "rpcserverip:" << m_config.Load("rpcserverip") << std::endl;
    // std::cout << "rpcserverport:" << m_config.Load("rpcserverport") << std::endl;
    // std::cout << "zookeeperip:" << m_config.Load("zookeeperip") << std::endl;
    // std::cout << "zookeeperport:" << m_config.Load("zookeeperport") << std::endl;
}

MprpcApplication& MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig& MprpcApplication::GetConfig()
{
    return m_config;
}