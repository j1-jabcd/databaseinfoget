/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef PROCESS_PLUS_PLUS_HPP
#define PROCESS_PLUS_PLUS_HPP

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <bits/stdc++.h> 
#include <list>
#include <cstring>
#include <cstdlib>

#define IN
#define OUT
#define INOUT   


namespace ns_DataTool{
        /********************************/
        /* desc:         获取对应命令行执行结果
             param:      strCmd 命令行
        */
        /********************************/
        void GetCmdResult(IN const  std::string &strCmd)
        {
                FILE* fp = nullptr;
                if((fp=popen(strCmd.c_str(),"r")) == nullptr)
                {
                std::cout<<"error"<<std::endl;
                return;
                }
                char cDmstr[256];
                 while(fgets(cDmstr,sizeof(cDmstr),fp))
                        std::cout<<cDmstr<<std::endl;
                pclose(fp);
        }
        /********************************/
        /* desc:         在指定文件路径中找到对应字符串所在行
             param:      strFile 文件路径     str 对应字符串     
        */
        /********************************/
        std::string FindStringWithReturn(IN std::string  strFile,IN std::string str) {
                std::string strLine;
                std::ifstream ifReadfile(strFile.c_str());
                if(ifReadfile.is_open()) {
                        while (std::getline(ifReadfile, strLine)) {
                                if(strstr(strLine.c_str(), str.c_str()))
                                        return strLine + "\n";
                                }
                                return "null";
                                ifReadfile.close();
                        } 
                                else {
                                        return "Unable to open file"; /* Unable to open file */
                                }
                        return "null"; /* Not found. */
} 
        /********************************/
        /* desc:         在指定文件路径中删除对应字符串
             param:      strMainString 文件路径     str 对应字符串     
        */
        /********************************/

        std::string EraseAllSubString(INOUT std::string & strMainString, IN const std::string & strErase) {
                size_t pos = std::string::npos;
                        while((pos = strMainString.find(strErase)) != std::string::npos) {
                                strMainString.erase(pos, strErase.length());
                        }       
                                        return strMainString;
        }

        //数据库基类
        class CDataBase
        {
                public:
                        void DataInit(IN int iPid){
                                m_iPid = iPid;
                        }              
                          /********************************/
                        /*desc:         通过进程pid获取进程名
                          param:        m_iPid 进程名    
                        */
                        /********************************/
                         static std::string GetProcessName( IN int m_iPid) {
                                std::string strPath("/proc/");
                                strPath.append(std::to_string(m_iPid));
                                strPath.append("/status");
                                strPath = FindStringWithReturn(strPath, "Name:");
                                if(strPath != "null") {
                                        strPath.erase(0,6);
                                        int iR = strPath.find('\r\n');
                                        strPath.replace(iR,1,"");
                                        return strPath;
                                 }
                                return "null";
                        }
                        /********************************/
                        /*      desc:      由进程pid获取进程数据目录/端口/配置文件目录/安装目录信息/IP信息/输出信息
                        */
                        /********************************/
                        virtual std::string GetProcessData(){};
                        virtual std::string GetProcessPort(){};
                        virtual std::string GetProcessInit(){};
                        virtual std::string GetHomePath(){};
                        virtual std::string GetIP(){};
                        virtual std::string GetProcessInfo_out(){};
                        ~CDataBase(){};
                public:
                        int m_iPid;
        };

        //人大金昌数据库类
        class CkdDataBase:public CDataBase
        {
                public:
                        std::string GetProcessData()
                        {
                                std::string strPath("/proc/");
                                strPath.append(std::to_string(m_iPid));
                                strPath.append("/cwd/kingbase.pid");
                                strPath = FindStringWithReturn(strPath, "data");
                                if(strPath != "null") {
                                        m_strData = strPath;
                                return m_strData;
                         }
                                return "null";
                        }
                        std::string GetIP()
                        {
                                std::string strPath(m_strData);
                                strPath.append("SupTools/suptools.ini");
                              //  std::cout<<strPath<<std::endl;
                                m_strIp = FindStringWithReturn(strPath, "HOST");
                                std::cout<<m_strIp;
                                m_strIp = FindStringWithReturn(strPath, "IP_LIST=");
                                std::cout<<m_strIp;
                                return m_strIp;
                        }
                        std::string GetProcessPort(){
                                std::string strPath("/proc/");
                                strPath.append(std::to_string(m_iPid));
                                strPath.append("/cwd/kingbase.conf");
                                std::cout << "INI:" << strPath << std::endl;
                                strPath = FindStringWithReturn(strPath, "port");
                                if(strPath != "null") {
                                        m_strPort = EraseAllSubString(strPath,"# (change requires restart)");
                                std::cout << m_strPort;
                                return m_strPort;
                        }
                                return "null";
                        }
                        std::string GetProcessInfo_out(){
                                std::cout<<"Verion:";
                                m_strData = GetProcessData();
                                GetCmdResult( m_strData.erase(20,23) + "Server/bin/ksql  -V");
                                std::cout << "DATA:" << m_strData<<std::endl;
                                GetProcessPort();
                                std::cout << "LOG:" << m_strData << "sys_log" << std::endl;
                                GetIP();
                                return "success";
                        }
                ~CkdDataBase(){};
                private:
                        std::string m_strPort , m_strData , m_strIp;
        };

        //达梦数据库类
        class CdmDataBase:public CDataBase
        {
                public:
                        std::string GetProcessInit( )
                        {
                                std::string strPath("/proc/");
                                int iFlag = 0;
                                strPath.append(std::to_string(m_iPid));
                                strPath.append("/cmdline");
                                strPath = FindStringWithReturn(strPath, "dm");
                                if(strPath != "null") {
                                         for(auto & i : strPath)
                                        {
                                                 if('.' == i)
                                                 {
                                                         m_strIni += ".ini";
                                                         return m_strIni;;
                                                 }
                                                if(iFlag) m_strIni += i;
                                                if('=' == i) iFlag = 1;
                                        }
                                         return m_strIni;
                                 }
                                        return "null";
                        }
                        std::string GetHomePath()
                        {
                                std::string strPath("/proc/");
                                int iFlag = 0;
                                strPath.append(std::to_string(m_iPid));
                                strPath.append("/cwd/DmInstanceMonitorService");
                                strPath = FindStringWithReturn(strPath, "DM_HOME");
                                if(strPath != "null") {
                                        for(auto& s : strPath)
                                        {
                                                if(iFlag && s != '"')m_strHome+=s;
                                                if( '"' == s)
                                                        ++iFlag;
                                                if(2 == iFlag)break;
                                        }
 
                                         return m_strHome;
                                 }
                                        return "null";
                        }
                       std::string GetIP()
                        {
                                std::cout<<"IP: 127.0.0.1"<<std::endl;
                                return "success";
                        }
                        std::string GetProcessInfo_out( )
                        {
                                std::string strIniway = " ";
                                GetHomePath();
                                std::cout<<"Verion:";
                                GetCmdResult(m_strHome+"/tool/./version.sh");
                                GetProcessInit();
                                for(auto& in : m_strIni )
                                {
                                        strIniway += in;
                                        if('.' == in)
                                {
                                        strIniway += "ini";
                                        break;
                                }
                                }
                                m_strPort = EraseAllSubString(FindStringWithReturn(m_strIni,"DCRS_PORT_NUM").erase(0,2).erase(16,17),"#Port number on which the database dcrs will listen");
                                int iR = m_strPort.find('\r\n');
                                m_strPort.replace(iR,1,"");
                                std::cout << m_strPort << std::endl;
                                std::cout << "DM_HOME:" << m_strHome << std::endl;
                                std::cout << "LOG:" << m_strHome + "/log" << std::endl;
                                m_strIni = strIniway;
                                std::cout << "INI：" << m_strIni << std::endl;
                                std::cout << "Plugins：" << m_strHome + "/tool/plugins" << std::endl;
                                GetIP();
                                return "success";
                        }
                        ~CdmDataBase(){};
                private:
                                std::string m_strData , m_strIni, m_strPort , m_strHome;
        };


}

#endif /* PROCESS_PLUS_PLUS_HPP */