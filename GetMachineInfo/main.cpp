//
// Created by xuan on 9/16/22.
//
#include "GetMachineID.h"
#include <stdio.h>
#include "iostream"
int main(int argc, char **argv)
{
  GetMachineInfo MachineInfo;
  std::string cpuid;
  cpuid = MachineInfo.GetCPUId();
  printf("cpuid:%s\n",cpuid.c_str());

  set<string> eth;
  map<string, pair<string, string>> macs;
  map<string, pair<string, string>>::iterator it;

  MachineInfo.getEthNames(eth);
  MachineInfo.getIPMACs(eth, macs);
  for(it=macs.begin(); it!=macs.end(); it++)
  {
    cout << (*it).second.first<<"'s mac address:"<<(*it).first << endl;
  }
}
