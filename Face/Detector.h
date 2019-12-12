#pragma once
#include "include/FaceDetector.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaFaceDetector.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face
{
	public ref class Detector
	{
	public:
		Detector();
		Detector(String^ model_file_name);
		~Detector();

		List<Rectangle>^ Detect(Bitmap^ bmp);

	private:
		seeta::FaceDetector* detector = nullptr;
	};
}
