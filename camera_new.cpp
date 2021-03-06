﻿#include "camera.h"
#include <string>
#include <math.h>
#include <robokit/core/time_server/rbk_time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>
#include <pcl/features/eigen.h>
#include <pcl/features/normal_3d.h>
#include <pcl/segmentation/region_growing.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include<pcl/visualization/cloud_viewer.h>
#include "message_pointcloud.pb.h"
#include "message_localization.pb.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>

#define SOURCE_PLUGIN "O3D3xxCamera.W32.pap"
#define SOURCE_PARAM "192.168.192.6:80:50010"	//摄像头IP地址
#define PROC_PLUGIN "O3D3xxProc.W32.ppp"
#define PROC_PARAM ""

namespace {
	const bool SEE_RESULT = true;
	const float minRange = -3.2;								//最近能看到的栈板距离 （m）
	const float maxRange = -1.2;								//最远能看到的栈板距离 （m）
	const int max_pallet_num = 20;							//栈板最多叠的层数
	const int maxExposureTime = 8000;						//最大的曝光时间 （μs）
	const int minExposureTime = 4000;
	const float smoothnessThreshold = 12.0f * M_PI / 180.0f;//区域增长的结束条件 （°）
	const float pallet_height = 0.15;						//每块栈板的高度
	const float cut_bottom = 0.0;							//每层栈板往下切掉的量
	const float cut_top = 0.09;								//每层栈板往上切掉的量
};


using namespace rbk::protocol;

RBK_INHERIT_SOURCE(IFMO3d303)
IFMO3d303::IFMO3d303() {
	//connect to the camera
	res = pmdOpen(&hnd, SOURCE_PLUGIN, SOURCE_PARAM, PROC_PLUGIN, PROC_PARAM);
	if (res != PMD_OK) {
		LogError("Could not connect");
	}
	setExposureTime(maxExposureTime);
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
	}

	res = pmdGetSourceDataDescription(hnd, &dd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get data description : " << err);
		pmdClose(hnd);
	}

	imgWidth = dd.img.numColumns;
	imgHeight = dd.img.numRows;
	amp.resize(imgWidth * imgHeight);
	flags.resize(imgWidth * imgHeight);
}

IFMO3d303::~IFMO3d303() {
	res = pmdClose(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not close the connection : " << err);
	}
}

bool IFMO3d303::setExposureTime(unsigned int exposure) {
	exposureTime = exposure;
	res = pmdSetIntegrationTime(hnd, 0, exposure);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not set the integration time : " << err);
		pmdClose(hnd);
		return false;
	}
	return true;
}

unsigned int IFMO3d303::getExposureTime() {
	unsigned int exposure = 0;
	res = pmdGetIntegrationTime(hnd, &exposure, 0);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not set the integration time : " << err);
		pmdClose(hnd);
		return -1;
	}
	return exposure;
}

bool IFMO3d303::getPointCloud(std::vector<float> &pointcloud) {
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}

	pointcloud.clear();
	pointcloud.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &pointcloud[0], pointcloud.size() * sizeof(float));

	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	return true;
}

bool IFMO3d303::getData(pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud) {
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}

	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	input_cloud->clear();
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	return true;
}

bool IFMO3d303::getDoubleData(pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud) {
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}

	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	input_cloud->clear();
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	///////////////////////////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	return true;
}

bool IFMO3d303::getTripleData(pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud) {
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}

	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	input_cloud->clear();
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	///////////////////////////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	///////////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetAmplitudes(hnd, &amp[0], amp.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get amplitude data : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	return true;
}

bool IFMO3d303::writeData() {
	pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	pcl::PCDWriter writer;
	time_t t = time(NULL);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S.pcd", localtime(&t));
	writer.write(std::string(tmp), *input_cloud, false);
	return true;
}

bool IFMO3d303::writeDoubleData() {
	pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	///////////////////////////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}

	pcl::PCDWriter writer;
	time_t t = time(NULL);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S.pcd", localtime(&t));
	writer.write(std::string(tmp), *input_cloud, false);
	return true;
}

bool IFMO3d303::writeTripleData() {
	pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//start to sample
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	std::vector<float> xyz3Dcoordinate;
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	///////////////////////////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	//////////////////////
	res = pmdUpdate(hnd);
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 256);
		LogError("Could not updateData : " << err);
		pmdClose(hnd);
		return false;
	}
	res = pmdGetFlags(hnd, &flags[0], flags.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get flag data : " << err);
		pmdClose(hnd);
		return false;
	}
	xyz3Dcoordinate.clear();
	xyz3Dcoordinate.resize(imgHeight * imgWidth * 3);
	res = pmdGet3DCoordinates(hnd, &xyz3Dcoordinate[0], xyz3Dcoordinate.size() * sizeof(float));
	if (res != PMD_OK) {
		pmdGetLastError(hnd, err, 128);
		LogError("Could not get xyz data : " << err);
		pmdClose(hnd);
		return false;
	}
	for (int i = 0; i < flags.size(); i++) {
		if (!(flags[i] & 1)) { // first bit is set to 1,if pixel is invalid
			input_cloud->push_back(pcl::PointXYZ(xyz3Dcoordinate[i * 3 + 0],
				xyz3Dcoordinate[i * 3 + 1],
				xyz3Dcoordinate[i * 3 + 2]));
		}
	}
	pcl::PCDWriter writer;
	time_t t = time(NULL);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S.pcd", localtime(&t));
	writer.write(std::string(tmp), *input_cloud, false);
	return true;
}

void IFMO3d303::getResult(std::vector<float> &result)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	getTripleData(input_cloud);
	//根据摄像头外参坐标转换
	//Current Robot Position;
	//Message_Localization msgLoc;
	//getSubscriberData(msgLoc);
	//Eigen::Matrix4f locMatrix = Eigen::Matrix4f::Identity();
	//locMatrix(0, 0) = cos(msgLoc.angle());
	//locMatrix(0, 1) = -sin(msgLoc.angle());
	//locMatrix(1, 0) = sin(msgLoc.angle());
	//locMatrix(1, 1) = cos(msgLoc.angle());
	//locMatrix(0, 3) = msgLoc.x();
	//locMatrix(1, 3) = msgLoc.y();

	Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
	Eigen::Matrix3f rotationMatrix = Eigen::AngleAxisf(_yawAngle*M_PI / 180.0 - M_PI / 2.0, Eigen::Vector3f::UnitZ()).toRotationMatrix()
		*Eigen::AngleAxisf(_rollAngle*M_PI / 180.0, Eigen::Vector3f::UnitX()).toRotationMatrix();
	transform.block(0, 0, 3, 3) = rotationMatrix;
	//float theta_z = -5 * M_PI / 180.0f;
	//transform.rotate(Eigen::AngleAxisf(theta_z, Eigen::Vector3f::UnitZ()));
	transform(0, 3) = _x;
	transform(1, 3) = _y;
	transform(2, 3) = _height;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tsf(new pcl::PointCloud<pcl::PointXYZ>());
	pcl::transformPointCloud(*input_cloud, *cloud_tsf, /*locMatrix**/transform);

	writeTripleData();
	result.clear();
	rbk::protocol::Message_AllPointCloud msgCloud;
	msgCloud.mutable_header()->set_data_nsec(boost::chrono::duration_cast<boost::chrono::nanoseconds>(boost::chrono::system_clock::now().time_since_epoch()).count());
	msgCloud.mutable_header()->set_frame_id("/O3D303");
	for (int pallet_num = 0; pallet_num < max_pallet_num; pallet_num++)
	{
		//直通滤波器切割点云
		pcl::PassThrough<pcl::PointXYZ> pass;
		pass.setInputCloud(cloud_tsf);            //设置输入点云
		pass.setFilterFieldName("z");         //设置过滤时所需要点云类型的Z字段
		pass.setFilterLimits(cut_bottom + pallet_num * pallet_height, cut_top + pallet_num * pallet_height);

		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered2(new pcl::PointCloud<pcl::PointXYZ>);
		pass.filter(*cloud_filtered2);            //执行滤波，保存过滤结果在cloud_filtered

		if (cloud_filtered2->size() < 10)
		{
			break;
		}


		pcl::PassThrough<pcl::PointXYZ> pass2;
		pass2.setInputCloud(cloud_filtered2);            //设置输入点云
		pass2.setFilterFieldName("x");         //设置过滤时所需要点云类型的Z字段
		pass2.setFilterLimits(minRange, maxRange);        //设置在过滤字段的范围	
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
		pass2.filter(*cloud_filtered);            //执行滤波，保存过滤结果在cloud_filtered          //执行滤波，保存过滤结果在cloud_filtered

		//统计滤波器去噪声
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
		pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;   //创建滤波器对象
		sor.setInputCloud(cloud_filtered);                           //设置待滤波的点云
		sor.setMeanK(20);                               //设置在进行统计时考虑查询点临近点数
		sor.setStddevMulThresh(0.5);                    //设置判断是否为离群点的阀值
		sor.filter(*cloud);                    //存储

		//法向量估计
		pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
		ne.setInputCloud(cloud);
		pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());
		ne.setSearchMethod(tree);
		pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
		ne.setKSearch(20);
		ne.compute(*normals);
		//pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
		//pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);

		////采用RANSAC分割地面
		//pcl::SACSegmentationFromNormals<pcl::PointXYZ, pcl::Normal> seg;
		//pcl::ModelCoefficients::Ptr coefficients_plane(new pcl::ModelCoefficients);
		//pcl::PointIndices::Ptr inliers_plane(new pcl::PointIndices);
		//pcl::ExtractIndices<pcl::PointXYZ> extract;
		//seg.setOptimizeCoefficients(true);     //设置对估计的模型系数需要进行优化
		//seg.setModelType(pcl::SACMODEL_NORMAL_PLANE); //设置分割模型
		//seg.setNormalDistanceWeight(0.1);      //设置表面法线权重系数
		//seg.setMethodType(pcl::SAC_RANSAC);    //设置采用RANSAC作为算法的参数估计方法
		//seg.setMaxIterations(100);             //设置迭代的最大次数
		//seg.setDistanceThreshold(0.1);         //设置内点到模型的距离允许最大值
		//seg.setInputCloud(cloud);
		//seg.setInputNormals(normals);
		//seg.segment(*inliers_plane, *coefficients_plane);
		//extract.setInputCloud(cloud);
		//extract.setIndices(inliers_plane);
		//extract.setNegative(true);            //保留平面以外的区域
		//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_ransac(new pcl::PointCloud<pcl::PointXYZ>());
		//extract.filter(*cloud_ransac);

		////法向量重新估计
		//pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne_2;
		//ne_2.setInputCloud(cloud_ransac);
		//pcl::search::KdTree<pcl::PointXYZ>::Ptr tree_2(new pcl::search::KdTree<pcl::PointXYZ>());
		//ne_2.setSearchMethod(tree_2);
		//pcl::PointCloud<pcl::Normal>::Ptr normals_2(new pcl::PointCloud<pcl::Normal>);
		//ne_2.setKSearch(20);
		//ne_2.compute(*normals_2);
		//pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals_2(new pcl::PointCloud<pcl::PointNormal>);
		//pcl::concatenateFields(*cloud_ransac, *normals_2, *cloud_with_normals_2);

		//区域增长算法找到三个端面
		pcl::RegionGrowing<pcl::PointXYZ, pcl::Normal> reg;
		reg.setMinClusterSize(50);
		reg.setMaxClusterSize(300);
		reg.setSearchMethod(tree);
		reg.setNumberOfNeighbours(20);
		reg.setSmoothModeFlag(true);
		reg.setCurvatureTestFlag(true);
		//reg.setResidualTestFlag(true);
		reg.setInputCloud(cloud);
		reg.setInputNormals(normals);
		reg.setSmoothnessThreshold(smoothnessThreshold);  //判断法向量夹角
		reg.setCurvatureThreshold(0.1);                    //判断曲率
		//reg.setResidualThreshold(0.05);                    //判断投影
		std::vector <pcl::PointIndices> clusters;
		reg.extract(clusters);
		LogInfo("Number of clusters is equal to " << clusters.size());



		pcl::PointCloud<pcl::Normal>::Ptr pallet_avg_normal_tmp(new pcl::PointCloud<pcl::Normal>);//每个面的法向量
		pcl::PointCloud<pcl::PointXYZ>::Ptr center_tmp(new pcl::PointCloud<pcl::PointXYZ>());     //每个面的中心坐标
		if (clusters.size() < 2) {
			LogWarn("No enough clusters !");
			break;
		}
		else
		{
			//可视化
			if (SEE_RESULT)
			{
				boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Normals"));
				viewer->setBackgroundColor(0, 0, 0);
				pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();
				viewer->addPointCloud<pcl::PointXYZRGB>(colored_cloud, "color");
				viewer->addCoordinateSystem();//红色是X轴，绿色是Y轴，蓝色是Z
				while (!viewer->wasStopped()) {
					viewer->spinOnce(100);
					boost::this_thread::sleep(boost::posix_time::microseconds(100000));
				}
			}
			
			for (int num = 0; num < clusters.size(); num++) {
				pcl::PointCloud<pcl::PointXYZ>::Ptr pallet(new pcl::PointCloud<pcl::PointXYZ>);
				pallet->clear();
				pcl::PointCloud<pcl::Normal>::Ptr normals_4(new pcl::PointCloud<pcl::Normal>);
				normals_4->clear();
				for (int i = 0; i < clusters[num].indices.size(); i++) {
					pallet->push_back(cloud->points[clusters[num].indices[i]]);
					normals_4->push_back(normals->points[clusters[num].indices[i]]);
				}

				int pallet_normal_size = (int)pallet->size();
				float pallet_normal[3] = { 0 };
				float center_point[3] = { 0 };
				for (int i = 0; i < pallet_normal_size; i++) {
					pallet_normal[0] += normals_4->points[i].normal[0];
					pallet_normal[1] += normals_4->points[i].normal[1];
					pallet_normal[2] += normals_4->points[i].normal[2];
					center_point[0] += pallet->points[i].x;
					center_point[1] += pallet->points[i].y;
					center_point[2] += pallet->points[i].z;
				}
				pallet_normal[0] /= pallet_normal_size;
				pallet_normal[1] /= pallet_normal_size; // /= pallet_normal_size;//消除栈板前端面法向量中垂直地面的分量
				pallet_normal[2] /= pallet_normal_size;
				center_point[0] /= pallet_normal_size;
				center_point[1] /= pallet_normal_size;
				center_point[2] /= pallet_normal_size;
				//法向量归一化
				float pallet_normal_norm = sqrt(pallet_normal[0] * pallet_normal[0] + pallet_normal[1] * pallet_normal[1] + pallet_normal[2] * pallet_normal[2]);
				pallet_normal[0] /= pallet_normal_norm;
				pallet_normal[1] /= pallet_normal_norm;
				pallet_normal[2] /= pallet_normal_norm;
				pallet_avg_normal_tmp->push_back(pcl::Normal(pallet_normal[0], pallet_normal[1], pallet_normal[2]));
				center_tmp->push_back(pcl::PointXYZ(center_point[0], center_point[1], center_point[2]));
			}

			pcl::PointCloud<pcl::Normal>::Ptr pallet_avg_normal(new pcl::PointCloud<pcl::Normal>);//三个面的法向量
			pcl::PointCloud<pcl::PointXYZ>::Ptr center(new pcl::PointCloud<pcl::PointXYZ>());     //三个面的中心坐标
			for (int i = 0; i < clusters.size();i++) {
				if (fabs(pallet_avg_normal_tmp->points[i].normal_z) < 0.5 && fabs(pallet_avg_normal_tmp->points[i].normal_y) < 0.5) {//根据法向量去除一些平面
					center->push_back(center_tmp->points[i]);
					pallet_avg_normal->push_back(pallet_avg_normal_tmp->points[i]);
				}
			}

			float pallet_normal_final[3] = { 0 };   //最终认为的栈板前表面法向量
			float pallet_center_final[3] = { 0 };   //最终认为的栈板前表面中点
			float total_normal_size = 0;            //所有栈板前表面点的个数
			int total_size = (int)pallet_avg_normal->size();//聚类数量
			LogInfo("Number of surface: " << total_size);
			for (int i = 0; i < total_size; i++) {
				//LogError( pallet_avg_normal->points[i] );
				pallet_normal_final[0] += pallet_avg_normal->points[i].normal_x * clusters[i].indices.size();
				pallet_normal_final[1] += pallet_avg_normal->points[i].normal_y * clusters[i].indices.size();
				pallet_normal_final[2] += pallet_avg_normal->points[i].normal_z * clusters[i].indices.size();
				pallet_center_final[0] += center->points[i].x;
				pallet_center_final[1] += center->points[i].y;
				pallet_center_final[2] += center->points[i].z;
				total_normal_size += clusters[i].indices.size();
			}
			pallet_normal_final[0] /= total_normal_size;  //取加权平均
			pallet_normal_final[1] /= total_normal_size;
			pallet_normal_final[2] /= total_normal_size;
			pallet_center_final[0] /= total_size;
			pallet_center_final[1] /= total_size;
			pallet_center_final[2] /= total_size;
			//转换到栈板底面的高度
			pallet_center_final[2] = pallet_center_final[2]- (cut_top - cut_bottom)/2 - cut_bottom;
			//转换为四元数, y方向为0，认为只绕y轴转过一定角度
			float theta = atan2(pallet_normal_final[1], pallet_normal_final[0]);
			Eigen::AngleAxisd rotation_vector(theta, Eigen::Vector3d(0, 0, 1));
			Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);

			result.push_back(pallet_center_final[0]);
			result.push_back(pallet_center_final[1]);
			result.push_back(pallet_center_final[2]);
			result.push_back(theta);
			LogInfo("x,y :"<<pallet_center_final[0] << ", "<<pallet_center_final[1]);
			LogInfo("height"<<pallet_center_final[2]);
			//result.push_back(q.y());
			//result.push_back(q.z());
			//result.push_back(q.w());
			rbk::protocol::Message_3DPointCloud *pointcloud = msgCloud.add_pointcloud();

			//LogInfo("size = "<<input_cloud.size());

			for (int i = 0; i < cloud->size(); i++) {
				//pointcloud.add_point();
				rbk::protocol::Message_O3D3o3Point* p = pointcloud->add_point();
				p->set_x((*cloud)[i].x);
				p->set_y((*cloud)[i].y);
				p->set_z((*cloud)[i].z);

			}
		}
	}
	publishTopic(msgCloud);

}
////////////////////////////////////////
void IFMO3d303::loadFromConfigFile()
{
	loadParam(_rollAngle, "Roll", -101.5, -180.0, 180.0, rbk::ParamGroup::Ungrouped, "相机安装: Roll", false);
	loadParam(_pitchAngle, "Pitch", 0.0, -180.0, 180.0, rbk::ParamGroup::Ungrouped, "相机安装: Pitch", false);
	loadParam(_yawAngle, "Yaw", 0.0, -180.0, 180.0, rbk::ParamGroup::Ungrouped, "相机安装: Yaw", false);
	loadParam(_x, "X", 0.0, 0.0, 1.0, rbk::ParamGroup::Ungrouped, "相机位置: X", false);
	loadParam(_y, "Y", 0.0, 0.0, 1.0, rbk::ParamGroup::Ungrouped, "相机安装: Y", false);
	loadParam(_height, "Height", 1.02, 0.0, 2.0, rbk::ParamGroup::Ungrouped, "相机安装: Z", false);
}

void IFMO3d303::setSubscriberCallBack() {
	setServiceCallBack<std::vector<float>()>("RecogniseTray", &IFMO3d303::RecogniseTray, this);
	createPublisher<rbk::protocol::Message_AllPointCloud>();
}

//死循环
void IFMO3d303::run() {
	//do something
	while (true)
	{
		SLEEP(1000);
		RecogniseTray();
		//getParameter();
	}
}
//服务
std::vector<float> IFMO3d303::RecogniseTray()
{
	std::vector<float> result;
	// 获取数据 dx dy dz & 四元数(x, y, z, w) 
	getResult(result);
	return result;
}
std::vector<float> IFMO3d303::getParameter() 
{
	std::vector<float> res;
	pcl::PointCloud<pcl::PointXYZ>::Ptr ptrPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
	const double threshold = 0.01;
	getDoubleData(ptrPointCloud);

	pcl::PassThrough<pcl::PointXYZ> pass2;
	pass2.setInputCloud(ptrPointCloud);            //设置输入点云
	pass2.setFilterFieldName("z");         //设置过滤时所需要点云类型的Z字段
	pass2.setFilterLimits(1.2, 2.0);        //设置在过滤字段的范围	
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
	pass2.filter(*cloud_filtered);

	pcl::SACSegmentation<pcl::PointXYZ> seg;
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>());

	seg.setOptimizeCoefficients(true);
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	seg.setMaxIterations(300);
	seg.setDistanceThreshold(0.015);

	seg.setInputCloud(cloud_filtered);
	seg.segment(*inliers, *coefficients);

	//Visualization
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Normals"));
	viewer->setBackgroundColor(0, 0, 0);
	//pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();
	viewer->addPointCloud<pcl::PointXYZ>(cloud_filtered, "color");
	viewer->addCoordinateSystem();//红色是X轴，绿色是Y轴，蓝色是Z
	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	if (inliers->indices.size() == 0)
	{
		LogWarn("Could not estimate a planar model for the given dataset.");
	}
	//The angle between the fitting plane with plane xy
	else 
	{
		double angle = std::acos(-coefficients->values[2]);
		if (angle > M_PI / 2.0)
			angle = M_PI - angle;
		double allHeight = 0;
		for (int i = 0; i < inliers->indices.size(); i++)
		{
			allHeight = allHeight + cloud_filtered->points[inliers->indices[i]].y*sin(angle) + cloud_filtered->points[inliers->indices[i]].z*cos(angle);
		}
		double height, Roll;
		height = allHeight / (inliers->indices.size() + 1);
		Roll = -M_PI + angle;
		//LogInfo("height = " << height << "  Roll = " << Roll*180/M_PI);
		res.push_back(height);
		res.push_back(Roll*180/M_PI);
	}
	return res;
}