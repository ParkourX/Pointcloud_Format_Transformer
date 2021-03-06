#include <boost/program_options.hpp>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/io.h>
#include <pcl/io/vtk_io.h>
 
#include <iostream>
#include <fstream>
 
using namespace pcl;
using namespace std;
 
// Brief: Do the batch bin2pcd transformation for kitti odometry datatset (http://www.cvlibs.net/datasets/kitti/)

int main(int argc, char **argv){
	
    // The file to read from.
	string infile = argv[1];
 
	// The file to output to.
	string outfile = argv[2];
    
    std::cout<<"Transform begin"<<std::endl;
    
	// Load point cloud
	fstream input(infile.c_str(), ios::in | ios::binary);
	if(!input.good()){
		cerr << "Could not read file: " << infile << endl;
		exit(EXIT_FAILURE);
	}
	input.seekg(0, ios::beg);
 
	pcl::PointCloud<PointXYZI>::Ptr pointCloud (new pcl::PointCloud<PointXYZI>);
 
	int i;
	for (i=0; input.good() && !input.eof(); i++) {
		PointXYZI point;
		input.read((char *) &point.x, 3*sizeof(float));
		input.read((char *) &point.intensity, sizeof(float));
        point.intensity*=255;
		pointCloud->push_back(point);
	}
	input.close();
 
	cout << "Read bin file from [" << infile << "]: "<< i << " points, writing to [" << outfile << "]"<< endl;
    
    if (pcl::io::savePCDFileBinary(outfile, *pointCloud) == -1) 
	{
		PCL_ERROR("Couldn't write file\n");
		return false;
	}

	std::cout<<"Transform done"<<std::endl;
}
