#include "pch.h"
#include "Assessor.h"

namespace Face
{
	Assessor::Assessor()
	{
		this->assessor = new seeta::QualityAssessor();
	}

	Assessor::~Assessor()
	{
		if (this->assessor != nullptr)
		{
			delete this->assessor;
			this->assessor = nullptr;
		}
	}

	float Assessor::Evaluate(Bitmap^ bmp, Rectangle^ face, List<PointF>^ pts)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(bmp);
		SeetaRect rect = Utils::Rectangle2SeetaRect(face);
		SeetaPointF points[5];
		for (int i = 0; i < 5; i++)
		{
			points[i] = Utils::PointF2SeetaPointF(pts[i]);
		}

		return this->assessor->evaluate(img, rect, points);
	}
}