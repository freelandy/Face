using Face;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            Bitmap bmp1 = (Bitmap)Bitmap.FromFile("1.png");
            Face.Aligner aligner = new Aligner("models\\pd_2_00_pts5.dat");
            Face.Detector detector = new Detector("models\\fd_2_00.dat");
            Face.Recognizer recognizer = new Recognizer("models\\fr_2_10.dat");
            Face.Assessor assessor = new Assessor();

            Stopwatch sw = new Stopwatch();
            sw.Start();

            List<Rectangle> faces1 = detector.Detect(bmp1);
            List<Rectangle> faces2 = detector.Detect(bmp1);
            sw.Stop();

            long detect = sw.ElapsedMilliseconds;

            sw.Restart();
            List<PointF> pt1 = aligner.Align(bmp1, faces1[0]);
            List<PointF> pt2 = aligner.Align(bmp1, faces2[1]);
            sw.Stop();

            long align = sw.ElapsedMilliseconds;

            sw.Restart();
            double s = recognizer.Verify(bmp1, pt1, bmp1, pt2);
            sw.Stop();

            long recognize = sw.ElapsedMilliseconds;

            for (int i = 0; i < faces1.Count; i++)
            {
                Console.WriteLine(faces1[i].X + "\t" + faces1[i].Y + "\t" + faces1[i].Width + "\t" + faces1[i].Height);
            }

            double score = assessor.Evaluate(bmp1, faces1[0], pt1);

            Console.WriteLine(s);
            Console.WriteLine(score);
            Console.WriteLine("detect:" + detect);
            Console.WriteLine("align:" + align);
            Console.WriteLine("recognize:" + recognize);

            Console.ReadKey();
        }
    }
}
