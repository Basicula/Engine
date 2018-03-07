#include "testfuncs.h"

namespace Engine
{
	namespace Graph
	{
		float square(float x)
		{
			return x * x;
		}

		std::vector<Math::Vector2> lineInterpolation(const std::vector<Math::Vector2> &dots)
		{
			std::vector<Math::Vector2> result;

			for (int i = 0; i < dots.size(); i++)
			{
				result.push_back(dots[i]);
			}
			std::sort(result.begin(), result.end());

			while (result.size() < 1000)
			{
				int n = result.size();
				for (int i = 1; i < n; i++)
				{
					double x, y;
					x = (result[i].x + result[i - 1].x) / 2;
					y = result[i - 1].y + (x - result[i - 1].x) / (result[i].x - result[i - 1].x)*(result[i].y - result[i - 1].y);
					result.push_back(Math::Vector2(x, y));
				}
				std::sort(result.begin(), result.end());
			}

			return result;
		}

		std::vector<Math::Vector2> cubeInterpolation(const std::vector<Math::Vector2> &dots)
		{
			int n = dots.size();
			std::vector<std::vector<float>> matrix(n, std::vector<float>(n + 1));
			//fill matrix
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					matrix[i][j] = pow(dots[i].x, n - j - 1);
				}
				matrix[i][n] = dots[i].y;
			}

			for (int i = 0; i < n; i++)
			{
				float mainElem = matrix[i][i];
				for (int j = 0; j <= n; j++)
				{
					matrix[i][j] /= mainElem;
				}
				for (int j = 0; j < n; j++)
				{
					if (i == j) continue;
					float m = matrix[j][i];
					for (int k = 0; k <= n; k++)
					{
						matrix[j][k] -= matrix[i][k] * m;
					}
				}
			}
			//print
			/*for (int i = 0; i < n; i++)
			{
				for (int j = 0; j <= n; j++)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
			std::vector<Math::Vector2> result;
			for (int i = 0; i < n; i++)
			{
				result.push_back(dots[i]);
			}
			sort(result.begin(), result.end());
			for (int i = 1; i < n; i++)
			{
				if (dots[i - 1].dist(dots[i]) < 1) continue;
				for (float x = result[i - 1].x + 0.1f; x < result[i].x; x += 0.1f)
				{
					float y = 0;
					for (int j = 0; j < n; j++)
					{
						y += matrix[j][n] * pow(x, n - 1 - j);
					}
					result.push_back(Math::Vector2(x, y));
				}
			}
			sort(result.begin(), result.end());
			for (int i = 0; i < n; i++)
			{
				std::cout << matrix[i][n] << "*x^" << n - 1 - i << ((i == n - 1) ? " = 0\n" : " + ");
			}
			return result;
		}

		/*std::vector<Math::Vector2> nInterpolation(const std::vector<Math::Vector2> &dots)
		{
			std::vector<Math::Vector2> result;
			for (int i = 0; i < dots.size(); i++)
			{
				result.push_back(dots[i]);
			}
			sort(result.begin(), result.end());
			for (float x = result[0].x + 0.1; x < result[dots.size() - 1].x; x += 0.1)
			{
				for (int i = 0; i < dots.size(); i++)
				{

				}
			}
		}*/
	}


}