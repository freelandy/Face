#include "pch.h"
#include "Detector.h"
#include <fstream>
#include <iostream>

namespace Face
{
	Detector::Detector()
	{
		
	}

	Detector::Detector(String^ model_file_name)
	{
		seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
		int id = 0;		

		char* model = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(model_file_name);
		seeta::ModelSetting model_setting(model, device, id);
		this->detector = new seeta::FaceDetector(model_setting);
	}

	Detector::~Detector()
	{
		if (this->detector != nullptr)
		{
			delete this->detector;
			this->detector = nullptr;
		}
	}

	List<Rectangle>^ Detector::Detect(Bitmap^ bmp)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(bmp);

		//set face detector's min face size
		this->detector->set(seeta::FaceDetector::PROPERTY_MIN_FACE_SIZE, 20);

		SeetaFaceInfoArray face_array = this->detector->detect(img);

		std::vector<SeetaFaceInfo> faces = std::vector<SeetaFaceInfo>(face_array.data, face_array.data + face_array.size);
		List<Rectangle>^ face_list = gcnew List<Rectangle>();
		for (SeetaFaceInfo& face : faces)
		{
			Rectangle rect;
			rect.X = face.pos.x;
			rect.Y = face.pos.y;
			rect.Width = face.pos.width;
			rect.Height = face.pos.height;

			face_list->Add(rect);
		}	

		return face_list;
	}

	
}
