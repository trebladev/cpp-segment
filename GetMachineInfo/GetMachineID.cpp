//
// Created by xuan on 9/16/22.
//
#include "GetMachineID.h"


std::string GetMachineInfo::GetCPUId()
{
  std::string strCPUId;

  unsigned int level = 1;
  unsigned eax = 3 /* processor serial number */, ebx = 0, ecx = 0, edx = 0;
  __get_cpuid(level, &eax, &ebx, &ecx, &edx);

  // byte swap
  int first = ((eax >> 24) & 0xff) | ((eax << 8) & 0xff0000) | ((eax >> 8) & 0xff00) | ((eax << 24) & 0xff000000);
  int last = ((edx >> 24) & 0xff) | ((edx << 8) & 0xff0000) | ((edx >> 8) & 0xff00) | ((edx << 24) & 0xff000000);

  // tranfer to string
  std::stringstream ss;
  ss << std::hex << first;
  ss << std::hex << last;
  ss >> strCPUId;

  return strCPUId;
}


int GetMachineInfo::getEthNames(set<string> &ethName)
{
  FILE *fp = NULL;
  char *p = NULL;
  char linebuf[512];
  char devname[128];
  string tmp;

  fp = fopen("/proc/net/dev", "r");
  if(fp == NULL)
  {
    return -1;
  }

  memset(linebuf, 0x00, sizeof(linebuf));
  memset(devname, 0x00, sizeof(devname));

  while(fgets(linebuf, 511, fp) != NULL)
  {
    p = strstr(linebuf, ":");
    if(p == NULL)
    {
      memset(linebuf, 0x00, sizeof(linebuf));
      continue;
    }

    p[0] = 0x00;

    memset(devname, 0x00, sizeof(devname));

    strncpy(devname, linebuf, 127);

    tmp = string(devname);
    tmp.erase(0, tmp.find_first_not_of(" "));
    tmp.erase(tmp.find_last_not_of(" ")+1);

    if(strncmp(tmp.c_str(), "lo", 2) != 0 )
    {
      if(strncmp(tmp.c_str(), "eth", 3) == 0 || strncmp(tmp.c_str(), "ens", 3) == 0 || \
                strncmp(tmp.c_str(), "enp", 3) == 0 || strncmp(tmp.c_str(), "en", 2) == 0)
      {
        ethName.insert(tmp);
      }
    }

    memset(linebuf, 0x00, sizeof(linebuf));
  }

  fclose(fp);

  return 0;
}

int GetMachineInfo::getIPMACs(set<string> &ethName, map<string, pair<string, string>> &macs)
{
  set<string>::iterator it;
  struct ifreq ifr;
  struct sockaddr_in *sin;
  char ip_addr[30];
  char mac_addr[30];
  int sockfd = -1;
  int nRes = -1;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
  {
    return -1;
  }

  for(it=ethName.begin(); it!=ethName.end(); it++)
  {
    nRes = -1;

    memset(ip_addr, 0x00, sizeof(ip_addr));
    memset(mac_addr, 0x00, sizeof(mac_addr));

    memset(&ifr, 0x00, sizeof(ifr));

    strcpy(ifr.ifr_name, (*it).c_str());

    nRes = ioctl(sockfd, SIOCGIFADDR, &ifr);
    if(nRes < 0)
    {
      strcpy(ip_addr, "");
    }
    else
    {
      sin = (struct sockaddr_in *)&ifr.ifr_addr;
      strcpy(ip_addr, inet_ntoa(sin->sin_addr));
    }

    nRes = ioctl(sockfd, SIOCGIFHWADDR, &ifr);
    if(nRes < 0)
    {
      strcpy(mac_addr, "00:00:00:00:00:00");
    }
    else
    {
      sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x",
              (unsigned char)ifr.ifr_hwaddr.sa_data[0],
              (unsigned char)ifr.ifr_hwaddr.sa_data[1],
              (unsigned char)ifr.ifr_hwaddr.sa_data[2],
              (unsigned char)ifr.ifr_hwaddr.sa_data[3],
              (unsigned char)ifr.ifr_hwaddr.sa_data[4],
              (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
    }

    macs.insert(make_pair(string(mac_addr), make_pair(string(ifr.ifr_name), string(ip_addr))));
  }

  close(sockfd);

  return 0;
}
//int main()
//{
//  set<string> eth;
//  map<string, pair<string, string>> macs;
//  map<string, pair<string, string>>::iterator it;
//
//  getEthNames(eth);
//  getIPMACs(eth, macs);
//
//  //cout << eth.size() << endl;
//
//  for(it=macs.begin(); it!=macs.end(); it++)
//    //it=macs.begin();
//  {
//    cout << (*it).first << endl;
//    cout << (*it).second.first << endl;
//    cout << (*it).second.second << endl;
//  }

//  return 0;
//}