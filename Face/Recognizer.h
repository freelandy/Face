#pragma once
#include "include/FaceDatabase.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaFaceRecognizer.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face
{
	public ref class Recognizer
	{
	public:
		Recognizer();
		Recognizer(String^ model_file_name);
		~Recognizer();

		float Verify(Bitmap^ face1, List<PointF>^ pts1, Bitmap^ face2, List<PointF>^ pts2);
		long Identify(Bitmap^ face, List<PointF>^ pts, float% similarity);
		long Register(Bitmap^ face, List<PointF>^ pts);
		void Clear();
		long GetMaxRegisterIndex();


	private:
		seeta::FaceDatabase* recognizer = nullptr;
	};
}
