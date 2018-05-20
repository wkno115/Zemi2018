#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

//�摜�t�@�C���̕\��
void readImage()
{
	cv::Mat image = cv::imread("sample.jpg");	//�摜�̓ǂݍ���

	if (image.empty())	//�摜���������ǂݍ��߂��̂����m�F
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;	
	}
	/*
	cv::Mat outimage;
	cv::cvtColor(image, outimage,CV_BGR2GRAY);
	*/
	cv::imshow("Output", image);	//�摜�̕\��

	cv::waitKey();	//���͂�����܂őҋ@
}

//����t�@�C���̕\��
void readVideo()
{
	cv::VideoCapture cap("sora.avi");	//����t�@�C���̓ǂݍ���

	if (cap.isOpened() == false)	//����t�@�C���𐳂����ǂݍ��߂���
	{
		cout << "����t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//���悩��̉摜���擾

		if (frame.data == NULL)	//���悩��̉摜��S�ēǂݍ��񂾂�I��
			break;

		cv::imshow("Output", frame);

		cv::waitKey(33);	//�����̐��l��ω�������Ɓc�H
	}
}

//�J�������͂̕\��
void readCamera()
{
	cv::VideoCapture cap(1);	//�J�������͂̓ǂݍ���//0��windows�ɕW������

	if (cap.isOpened() == false)	//�J�������͂̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�J�������͂�ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	while (true)
	{
		cv::Mat frame;
		cap >> frame;	//�J��������̉摜���擾

		if (frame.empty())	//�摜���������ǂݍ��߂��̂����m�F
		{
			cout << "�J�������͂̂��߂ɑҋ@" << endl;
			continue;
		}

		cv::imshow("Output", frame);	//�摜�̕\��

		if (cv::waitKey(33) >= 0)	//33ms�ҋ@��A���͂������break
			break;
	}
}

//�摜�t�@�C���̕\��(�v���O�������s���Ƀt�@�C�������w��)
void readImage_cin()
{
	cout << "�摜�t�@�C��������͂��Ă��������D" << endl;
	cout << "��Fhoge.jpg" << endl;

	string name;
	cin >> name;	//�R���\�[���ւ̓��͂�name�ɑ��

	cv::Mat image;
	image = cv::imread(name);	//�摜�̓ǂݍ���

	if (image.empty())	//�摜�̓ǂݍ��݂Ɏ��s������I��
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow(name, image);	//image�Ɋi�[���ꂽ�摜��\������

	cv::waitKey();
}

//�F��Ԃ̕ϊ�
void convertColorSpace()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);	//���摜�̕\��

	//BGR��Gray
	cv::Mat grayimage;
	cv::cvtColor(image, grayimage, CV_BGR2GRAY);
	cv::imshow("grayimage", grayimage);

	//BGR��HSV
	cv::Mat hsvimage;
	cv::cvtColor(image, hsvimage, CV_BGR2HSV);
	cv::imshow("hsvimage", hsvimage);

	cv::waitKey();
}

//�摜���̂���̈�𒊏o
void extractROI()
{
	cv::Mat image = cv::imread("sample.jpg");
	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::Mat roi(image, cv::Rect(200, 150, 250, 150));	//�̈�̐؂蔲��
	cv::Mat roicopy = roi.clone();
	line(roicopy, cv::Point(10, 10), cv::Point(240, 140), cv::Scalar(0, 250, 0), 3);
	cv::imshow("ROI", ~roi);	//ROI�̕\��
	cv::imshow("ROICOPY", roicopy);	//ROI�̕\��

	cv::imshow("image", image);	//���摜�̕\��

	cv::waitKey();
}

//�l�K�|�W���]
void negaPosi()
{
	cv::Mat image = cv::imread("sampleMono.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	image = ~image;	//�l�K�|�W���]

	cv::imshow("invert", image);	//�l�K�|�W���]�摜�̕\��

	cv::waitKey();
}

//�`�����l���̕���
void splitColorImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];	//3���̉摜���i�[����z��
	cv::split(image, channels);	//1����3�`�����l���摜��3����1�`�����l���摜�ɕ���
	cv::imshow("Blue", channels[0]);
	cv::imshow("Green", channels[1]);
	cv::imshow("Red", channels[2]);

	cv::waitKey();
}

//�`�����l���̕����E����
void splitAndMergeColorImage()
{
	cv::Mat image = cv::imread("sample.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];
	cv::split(image, channels);	//image��3��Mat�I�u�W�F�N�g�ɕ���

	cv::Mat mergeChannels[3];	//�`�����l�����ёւ��p��Mat�z��
	mergeChannels[0] = channels[2];	//Blue��Red��
	mergeChannels[1] = channels[1];	//Green�͂��̂܂�
	mergeChannels[2] = channels[0];	//Red��Blue��

	cv::Mat mergeImage;
	cv::merge(mergeChannels, 3, mergeImage);	//�`�����l������ёւ����摜�𐶐�

	cv::imshow("mergeImage", mergeImage);

	cv::waitKey();
}


int main1(int argc, char** argv)
{
	//readImage();
	//readVideo();
	//readCamera();
	//readImage_cin();
	//convertColorSpace();
	//extractROI();
	//negaPosi();
	splitColorImage();
	//splitAndMergeColorImage();

	

	return 0;
}