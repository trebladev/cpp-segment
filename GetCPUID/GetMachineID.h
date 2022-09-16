//
// Created by xuan on 9/16/22.
//

#ifndef CPP_SEGMENT_GETCPUID_GETMACHINEID_H_
#define CPP_SEGMENT_GETCPUID_GETMACHINEID_H_

#include <cpuid.h>
#include <sstream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class GetMachineInfo{
 public:
  GetMachineInfo(){};
  ~GetMachineInfo(){};
  string GetCPUId();
  int getEthNames(set<string> &ethName);
  int getIPMACs(set<string> &ethName, map<string, pair<string, string>> &macs);

 private:
  string _CPUID;
  string _MACADDRESS;
};










#endif //CPP_SEGMENT_GETCPUID_GETMACHINEID_H_
