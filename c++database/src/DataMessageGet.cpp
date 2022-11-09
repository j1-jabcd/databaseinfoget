/* DataBase GET
        2022 11.8
# */

#include <iostream>
#include <DataMessageGet.hpp> /* Proce ss library */

/* Help */
#define HELP(object) std::cout << "Usage: " << object << " [--pid | --name]\n --pid : <NAME> to <PID>\n--name : <PID> to <NAME>\n";
using namespace ns_DataTool;
int main(int argc, char** argv) {
        if(argc < 3) {
                HELP(argv[0])
                return 0;
        }
       std:: string strDataBaseName;
       int pid = 0;
        std::string strText(argv[1]);
         if(strText == "--name") {
                std::string pid_string(argv[2]);
                pid = atoi(pid_string.c_str());
                strDataBaseName = CDataBase::GetProcessName(pid);
                std::cout << "Name: " << strDataBaseName + "\n";
        } else
                HELP(argv[0]) ;
        if(strDataBaseName == "kingbase")
        {
                CkdDataBase clskbData;
                clskbData.DataInit(pid);
                clskbData.GetProcessInfo_out();
    
        }
        else if(strDataBaseName == "dmserver")
        {
                CdmDataBase clsDmData;
                clsDmData.DataInit(pid);
                clsDmData.GetProcessInfo_out();

        }
        else 
        {
                std::cout << "error pid" << std::endl;
        }
        return 0;
}