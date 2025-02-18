#include "pch.h"
#include "Recognizer.h"

namespace Face
{
	Recognizer::Recognizer()
	{
	}

	Recognizer::Recognizer(String^ model_file_name)
	{
		seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
		int id = 0;

		char* model = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(model_file_name);
		seeta::ModelSetting model_setting(model, device, id);
		this->recognizer = new seeta::FaceDatabase(model_setting);
	}

	Recognizer::~Recognizer()
	{
		if (this->recognizer != nullptr)
		{
			delete this->recognizer;
			this->recognizer = nullptr;
		}
	}

	float Recognizer::Verify(Bitmap^ face1, List<PointF>^ pts1, Bitmap^ face2, List<PointF>^ pts2)
	{
		SeetaImageData img1 = Utils::Bitmap2SeetaImageData(face1);
		SeetaImageData img2 = Utils::Bitmap2SeetaImageData(face2);
		
		SeetaPointF points1[5];
		SeetaPointF points2[5];

		for (int i = 0; i < 5; i++)
		{
			points1[i] = Utils::PointF2SeetaPointF(pts1[i]);
			points2[i] = Utils::PointF2SeetaPointF(pts2[i]);
		}

		float similarity = -1;
		similarity = this->recognizer->Compare(img1, points1, img2, points2);

		return similarity;
	}

	long Recognizer::Identify(Bitmap^ face, List<PointF>^ pts, float% similarity)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(face);
		SeetaPointF points[5];
		for (int i = 0; i < 5; i++)
		{
			points[i] = Utils::PointF2SeetaPointF(pts[i]);
		}

		float s = -1;
		int idx = -1;
		idx = this->recognizer->Query(img, points, &s);
		
		similarity = s;

		return idx;
	}


	long Recognizer::Register(Bitmap^ face, List<PointF>^ pts)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(face);
		SeetaPointF points[5];
		for (int i = 0; i < 5; i++)
		{
			points[i] = Utils::PointF2SeetaPointF(pts[i]);
		}

		int idx = -1;
		idx = this->recognizer->Register(img, points);

		return idx;
	}

	void Recognizer::Clear()
	{
		this->recognizer->Clear();
	}

	long Recognizer::GetMaxRegisterIndex()
	{
		return this->recognizer->Count();
	}
}