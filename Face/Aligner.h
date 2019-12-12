#pragma once
#include "include/FaceLandmarker.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaFaceLandmarker.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face
{
	public ref class Aligner
	{
	public:
		Aligner();
		Aligner(String^ model_file_name);
		~Aligner();

		List<PointF>^ Align(Bitmap^ bmp, Rectangle^ face);

	private:
		seeta::FaceLandmarker* aligner = nullptr;
	};
}

