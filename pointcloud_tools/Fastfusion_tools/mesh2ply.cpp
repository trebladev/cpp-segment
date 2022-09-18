//
// Created by xuan on 9/18/22.
//
#include "iostream"
#include "fstream"
#include <pcl/point_cloud.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <string>

using namespace std;

int main(int argc,char **argv) {

  //read .obj file
  ifstream fin;
  fin.open(argv[1],ios::in);
  string str;

  //variable of pointcloud's attribute
  float num_x,num_y,num_z,num_r,num_g,num_b;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointXYZRGB point;
  while(fin>>str)
  {
    if(str[0] == 118)  //判断是否是点的数据 118是v的ASCII
    {

      fin>>num_x>>num_y>>num_z>>num_r>>num_g>>num_b;
      point.x = num_x;
      point.y = num_y;
      point.z = num_z;
      point.r = (int)(num_r*255); // r in fastfusion's mesh file is 0-1
      point.g = (int)(num_g*255);
      point.b = (int)(num_b*255);

      cloud->points.push_back(point);
    }
  }
  fin.close();
  pcl::io::savePLYFile(argv[2],*cloud); // output ply file

  return 0;
}