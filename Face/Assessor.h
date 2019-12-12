#pragma once
#include "include/QualityAssessor.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaQualityAssessor.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face
{
	public ref class Assessor
	{
	public:
		Assessor();
		~Assessor();

	public:
		float Evaluate(Bitmap^ bmp, Rectangle^ face, List<PointF>^ pts);


	private:
		seeta::QualityAssessor* assessor = nullptr;
	};
}
