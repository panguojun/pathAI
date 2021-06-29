
// *****************************************************************
// PATH AI
// *****************************************************************
namespace PATHAI
{
	static const int SIZEX = IMAGESCALE;
	static const int SIZEY = IMAGESCALE;

	CDymPng png;
	inline uint getcolor(int x, int y)
	{
		if (png.Width() > 0)
		{
			x = clampi(x, 0, png.Width() - 1);
			y = clampi(y, 0, png.Height() - 1);
			y = png.Height() - 1 - y; // 上下颠倒

			unsigned int cor = png.gifGetPixel(x, y);
			return GetRValue(cor);
		}
		return 0;
	}

	static byte hismap[SIZEX][SIZEY] = { 0 };
	static byte aimap[SIZEX][SIZEY] = { 0 };
	point_t target;
	int hismapid = 1;
	void _gooddog()
	{
		for(int i = 0; i < SIZEX; i ++)
		for(int j = 0; j < SIZEY; j ++)
		{
			if(aimap[i][j] > 0)
				aimap[i][j] -= (hismapid == hismap[i][j]) ? 0 : 1;
		}
	}
	bool walk(int x, int y, int depth = 0)
	{
		if (depth > 1000)
			return false;

		if (x < 1 || x >= SIZEX - 1 || y < 1 || y >= SIZEY - 1)
		{
			return false;
		}

		if (x == target.x && y == target.y)
		{
			_gooddog();

			PRINT("goal!");
			return true;
		}

		if (rand() % 10 > aimap[x][y]) return false;

		if (hismap[x][y] == hismapid) return false; hismap[x][y] = hismapid;

		//if (0 == getcolor(x, y)) // border
		//{
		//	return;
		//}
		
		if (walk(x + 1, y, depth + 1)) return true;
		if (walk(x - 1, y, depth + 1)) return true;
		if (walk(x, y + 1, depth + 1)) return true;
		if (walk(x, y - 1, depth + 1)) return true;
	}
	void test()
	{
		memset(hismap, 0, sizeof(hismap));
		memset(aimap, 10, sizeof(aimap));

		target = point_t(546, 10);
		hismapid++;
		walk(1, 1);
	}
}
