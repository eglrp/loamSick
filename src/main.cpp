
#include <scanRegistration.hpp>
#include <laserOdometry.hpp>
#include <laserMapping.hpp>
#include <transformMaintenance.hpp>


#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/point_operators.h>
#include <pcl/common/io.h>
#include <pcl/search/organized.h>
#include <pcl/search/octree.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/filters/voxel_grid.h>
#include<pcl/visualization/cloud_viewer.h>



using namespace pcl;
using namespace std;


 void getFiles(string path, vector<string>& files){
            
            struct dirent *ptr;    
            DIR *dir;
            dir=opendir(path.c_str());
            int i = 0;
            while((ptr=readdir(dir))!=NULL)
            {
                string p;
            //跳过'.'和'..'两个目录
                if(ptr->d_name[0] == '.'){
                    
                    continue;}
                printf("%s is ready...\n",ptr->d_name);
                // sprintf(files[i],"./one/%s",ptr->d_name);
                files.push_back(p.assign(path).append("/").append(ptr->d_name));

             
          
            }
            closedir(dir);





    }



int main(int argc, char* args[]){
	
	

	
	std::ofstream outfile;
//	std::ofstream outfile2;
//	std::ofstream outfile3;
	int i;
	char filename[50] = {0};
	string p;

	outfile.open (p.assign(args[1]).append("/../pose.txt").c_str());
//	outfile2.open (p.assign(args[1]).append("/../pose_bef.txt").c_str());
//	outfile3.open (p.assign(args[1]).append("/../mapLog.txt").c_str());
	int num_id=0;
 	
    pcl::visualization::CloudViewer viewer ("mapping viewer");  
 


    scanRegistration scanner;
	laserOdometry odometrier;
	laserMapping mapper;
	transformMainTenance mainer;

		scanRegistrationBack scanValueBack;
        laserOdometryBack odometryValueBack;
		laserMappingBack mappingBackValue;
		maintenanceBack maintenanceValueBack;

	

	ifstream infile(args[2]);
	string temp;
	while (getline(infile,temp)){
		
		pcl::PointCloud<pcl::PointXYZI> points;
        
		pcl::io::loadPCDFile(p.assign(args[1]).append("/").append(temp.c_str()).c_str(),points);


        // pcl::io::savePCDFileASCII ("/home/xiesc/test.pcd", points);
        int j  = points.size();
		cout << "Read KTTI point cloud with " << j << " belong to " <<temp <<endl;
        


        scanValueBack = scanner.laserCloudHandler(points);
		odometryValueBack = odometrier.laserOdometryHandler(scanValueBack);
		// if (i%5==0 || i<10){
		// 	mappingBackValue = mapper.laserMappingHandler(odometryValueBack);
		// 	outfile3<<mappingBackValue.transformAftMapped[0]<<" "<<mappingBackValue.transformAftMapped[1]<<" "<<mappingBackValue.transformAftMapped[2]<<" "<<mappingBackValue.transformAftMapped[3]<<" "<<mappingBackValue.transformAftMapped[4]<<" "<<mappingBackValue.transformAftMapped[5]<<endl;

		// }
		mappingBackValue = mapper.laserMappingHandler(odometryValueBack);
		
		// maintenanceValueBack = mainer.transformRecorder(odometryValueBack,mappingBackValue);






        // std::stringstream filename;
        // filename << "/home/xiesc/testpcd_map/"<<num_id<<".pcd";
        
        // pcl::io::savePCDFileASCII (filename.str(), *mappingBackValue.laserCloudSurround);

		// if (num_id>0){
		// std::stringstream filename2;
        // filename2 << "/home/xiesc/testpcd_second_frame/"<<num_id<<".pcd";
        
        // pcl::io::savePCDFileASCII (filename2.str(), *mappingBackValue.laserCloudFullRes);
		// }

     	num_id++;
		 viewer.showCloud(mappingBackValue.laserCloudSurround);  
		char poseTime[20];
		strncpy(poseTime,temp.c_str(),20);
		outfile<<poseTime<<" "<<mappingBackValue.transformAftMapped[0]<<" "<<mappingBackValue.transformAftMapped[1]<<" "<<mappingBackValue.transformAftMapped[2]<<" "<<mappingBackValue.transformAftMapped[3]<<" "<<mappingBackValue.transformAftMapped[4]<<" "<<mappingBackValue.transformAftMapped[5]<<endl;
//		outfile2<<odometryValueBack.transformSum[0]<<" "<<odometryValueBack.transformSum[1]<<" "<<odometryValueBack.transformSum[2]<<" "<<odometryValueBack.transformSum[3]<<" "<<odometryValueBack.transformSum[4]<<" "<<odometryValueBack.transformSum[5]<<endl;
//      outfile3<<maintenanceValueBack.transformMapped[0]<<" "<<maintenanceValueBack.transformMapped[1]<<" "<<maintenanceValueBack.transformMapped[2]<<" "<<maintenanceValueBack.transformMapped[3]<<" "<<maintenanceValueBack.transformMapped[4]<<" "<<maintenanceValueBack.transformMapped[5]<<endl;
    
		// // Save DoN features
		// writer.write<PointXYZI> (outfile, *points, false);
		
	}

//  	while (!viewer.wasStopped ())  
//   {  
//   }  




    
    
    return 0;


}
