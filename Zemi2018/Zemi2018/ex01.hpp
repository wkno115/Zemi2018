#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

void GrayReadVideo()
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

		cv::Mat grayframe;
		cv::cvtColor(frame, grayframe, CV_BGR2GRAY);
		cv::imshow("Output", grayframe);

		cv::waitKey(33);	//�����̐��l��ω�������Ɓc�H
	}
}

void GrayCamera()
{
	cv::VideoCapture cap(0);	//�J�������͂̓ǂݍ���//0��windows�ɕW������

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
		cv::Mat grayframe;
		cv::cvtColor(frame, grayframe, CV_BGR2GRAY);

		cv::imshow("Output", grayframe);	//�摜�̕\��

		if (cv::waitKey(33) >= 0)	//33ms�ҋ@��A���͂������break
			break;
	}
}

void ExNegaPosi()
{
	cv::Mat image = cv::imread("sample_split.jpg");

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

//�摜���̂���̈�𒊏o
void ExtractROI()
{
	cv::Mat image = cv::imread("sample.jpg");
	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::Mat roi(image, cv::Rect(200, 150, 250, 150));	//�̈�̐؂蔲��

	image = ~image;
	roi = ~roi;

	cv::imshow("image", image);	//���摜�̕\��

	cv::waitKey();
}

//�`�����l���̕����E����
void BlueNegaImage()
{
	cv::Mat image = cv::imread("sample_split.jpg");

	if (image.empty())
	{
		cout << "�摜�t�@�C����ǂݍ��߂܂���ł����D" << endl;
		return;
	}

	cv::imshow("image", image);

	cv::Mat channels[3];
	cv::split(image, channels);	//image��3��Mat�I�u�W�F�N�g�ɕ���

	channels[0] = ~channels[0];

	cv::Mat negaImage;
	cv::merge(channels, 3, negaImage);	//�`�����l������ёւ����摜�𐶐�

	cv::imshow("BlueNegaImage", negaImage);

	cv::waitKey();
}

void main() {
	//GrayReadVideo(); //������O���[�X�P�[��������B
	//GrayCamera();	//�J�����̉摜���O���[�X�P�[�����B
	//ExNegaPosi();
	//ExtractROI();
	BlueNegaImage();
}