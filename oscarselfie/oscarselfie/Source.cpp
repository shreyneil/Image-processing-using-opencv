//SHREYASH SHARMA
//Branch:CSE
//6th Semester B.E.
//shreyneil@yahoo.co.in
//(Reg no.140905304)
//MIT MANIPAL
//sources
//http://docs.opencv.org/2.4/doc/tutorials/tutorials.html
//http://docs.opencv.org/2.4/modules/refman.html

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <iostream>
#include <stdio.h>
#include <windows.h>

using namespace std;
using namespace cv;

// Function Headers
void detectAndDisplay(Mat frame);

// Global variables
string face_cascade_name = "../haarcascade_frontalface_alt2.xml";
string eyes_cascade_name = "../haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

string window_name = "Capture - Face detection";

int main(void)
{
	//Load the cascade classifiers
	if (!face_cascade.load(face_cascade_name)){
		printf("--(!)Error loading\n");
		return (-1);
	}
	if( !eyes_cascade.load( eyes_cascade_name ) ){ 
		printf("--(!)Error loading\n"); 
		return -1; 
	}


	// Read the image file
	Mat frame = imread("../x64/Debug/oscarSelfie.jpg");
	
	// Apply the classifier to the frame
	if (!frame.empty()){
		detectAndDisplay(frame);
	}
	else{
		printf("File not found.");
	}

	waitKey(0);

	return 0;
}

/* *
*	Detect faces using harrcascade and guess Ellen's face for detecting eyes.
*	Draw circles on Ellen's eyes based on the eye's radius.
*	Marked the centroid of each eye by marking the center.
*	Displays the RGB values of the centroids.
*/
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;
	Mat crop;
	Mat res;
	Mat gray;
	string text;
	stringstream sstm;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	// Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 1, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));


	// Set Regions of Interest
	cv::Rect roi_b;
	cv::Rect roi_c;
	cv::Rect roi_d;

	size_t ic = 0; // ic is index of current element
	int ac = 0; // ac is area of current element

	size_t ib = 0; // ib is index of biggest element
	int ab = 0; // ab is area of biggest element

	for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

	{
		roi_c.x = faces[ic].x;
		roi_c.y = faces[ic].y;


		roi_c.width = (faces[ic].width);
		roi_c.height = (faces[ic].height);

		ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)
		

		roi_b.x = faces[ib].x;
		roi_b.y = faces[ib].y;

		roi_b.width = (faces[ib].width);
		roi_b.height = (faces[ib].height);

		ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

		if (ac > ab)
		{
			ib = ic;
			roi_b.x = faces[ib].x;
			roi_b.y = faces[ib].y;
			roi_b.width = (faces[ib].width);
			roi_b.height = (faces[ib].height);
		}



		Point pt1(faces[ic].x, faces[ic].y);	// Mark detected faces using rectangles
		Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
		rectangle(frame, pt1, pt2, Scalar(255, 0, 0), 2, 8, 0);




		Mat faceROI = frame_gray( faces[ic] );	//defining region of interest for eyes
		std::vector<Rect> eyes;

		//detect eyes of Ellen
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.156, 10, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );//1.156 for detecting ellen degenres' eyes



		bool eyeSide = true;
		for( size_t j = 0; j < eyes.size(); j++ )
		{
			// Centroid is being calculated by calculating their distance from the face
			int eye_y = faces[ic].y + eyes[j].y + eyes[j].height*0.5;
			int eye_x = faces[ic].x + eyes[j].x + eyes[j].width*0.5;

			//mark the eyes
			Point center( eye_x, eye_y);
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			//drawing circle for the eyeglasses
			circle( frame, center, radius, Scalar( 0, 255, 0 ), 1, 8, 0 );

			//marking the centroid of each eye
			circle(frame,center,1,Scalar(0,0,255),1,8,0);
			Point3_<uchar> *p = frame.ptr<Point3_<uchar>>(eye_y,eye_x);

			//displaying rgb values on the console
			if(eyeSide){
				cout<<"Left eye centroid : "<<endl;
			}else{
				cout<<"Right eye centroid : "<<endl;
			}
			eyeSide = !eyeSide;
			cout<<"R value is "<<(int)p->z<<endl;
			cout<<"G value is "<<(int)p->y<<endl;
			cout<<"B value is "<<(int)p->x<<endl;
		}




	}

	imshow("original", frame);

	if (!crop.empty())
	{
		imshow("detected", crop);
	}
	else
		destroyWindow("detected");

}