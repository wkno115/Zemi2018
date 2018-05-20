#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;

void saveCameraImage() {
	cv::VideoCapture cap(0);	//カメラ入力の読み込み//0はwindowsに標準装備

	if (cap.isOpened() == false)	//カメラ入力の読み込みに失敗したら終了
	{
		cout << "カメラ入力を読み込めませんでした．" << endl;
		return;
	}

	cv::Mat frame;	//入力画像

	while (true)
	{
		cap >> frame;	//カメラからの画像を取得

		if (frame.empty())	//画像が正しく読み込めたのかを確認
		{
			cout << "カメラ入力のために待機" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//画像の表示

		switch (cv::waitKey(33))
		{
		case 's':
			cv::imwrite("Output.jpg", frame);
			break;
		case 'e':
		case 'q':
			return ;
		default:
			break;
		}
	}	
}

void ClickBlurChange() {
	int xblursize = 1;	//平滑化のカーネルサイズ
	int yblursize = 1;
	cv::Mat image = cv::imread("lena.jpg");
	cv::Mat blurimage;

	while (true) {
		cv::blur(image, blurimage, cv::Size(xblursize, yblursize));
		cv::imshow("Blur", blurimage);

		int key=cv::waitKey(33);

		switch (key)
		{
		case 'w':
			yblursize++;
			break;
		case 's':
			yblursize--;
			break;
		case 'd':
			xblursize++;
			break;
		case 'a':
			xblursize--;
			break;
		case 'e':
		case 'q':
			return;
		default:
			break;
		}

		//入力があった場合はカーネルサイズを表示
		if(key!=-1){
			cout << "カーネルサイズ(" << xblursize << "," << yblursize << ")"<<endl;
		}

		if (xblursize == 0) {
			xblursize = 1;
		}
		if (yblursize == 0) {
			yblursize = 1;
		}
	}
}

void xGradation() {
	cv::Mat image(cv::Size(256, 256), CV_8UC1);

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			image.ptr(y,x)[0]=x;
		}
	}
	cv::imshow("Gradation", image);
	cv::waitKey();
}

void Gradation() {
	cv::Mat image(cv::Size(256, 256), CV_8UC1);

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			image.ptr(y, x)[0] = x/2+y/2;	//両者を割ってからじゃないとオーバーフロー
		}
	}
	cv::imshow("Gradation", image);
	cv::waitKey();
}

void Lines() {
	cv::Mat image[3];
	int a[]{5,10,50};
	for (int count = 0; count < sizeof a; count++) {
		image[count].create(cv::Size(256, 256), CV_8UC1);
		for (int y = 0; y < image[count].rows; y++) {
			for (int x = 0; x < image[count].cols; x++) {
				if(x%a[count]==0){
					image[count].ptr(y, x)[0] = 0;	//両者を割ってからじゃないとオーバーフロー
				}
				else {
					image[count].ptr(y, x)[0] = 255;
				}
			}
		}
		
	}
	cv::imshow("1", image[0]);	
	cv::waitKey();
}

int main() {
	//saveCameraImage();
	//ClickBlurChange();
	//xGradation();
	//Gradation();
	Lines();
}