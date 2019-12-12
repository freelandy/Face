#include "pch.h"
#include "Aligner.h"

namespace Face
{
	Aligner::Aligner()
	{
	}

	Aligner::Aligner(String^ model_file_name)
	{
		seeta::ModelSetting::Device device = seeta::ModelSetting::CPU;
		int id = 0;

		char* model = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(model_file_name);
		seeta::ModelSetting model_setting(model, device, id);
		this->aligner = new seeta::FaceLandmarker(model_setting);
	}
	Aligner::~Aligner()
	{
		if (this->aligner != nullptr)
		{
			delete this->aligner;
			this->aligner = nullptr;
		}
	}

	List<PointF>^ Aligner::Align(Bitmap^ bmp, Rectangle^ face)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(bmp);
		SeetaRect rect = Utils::Rectangle2SeetaRect(face);

		std::vector<SeetaPointF> points(this->aligner->number());
		this->aligner->mark(img, rect, points.data());
		//points = std::move(points);

		List<PointF>^ pts = gcnew List<PointF>();
		for (int i = 0; i < points.size(); i++)
		{
			PointF pt;
			pt.X = points[i].x;
			pt.Y = points[i].y;

			pts->Add(pt);
		}

		return pts;
	}

}
