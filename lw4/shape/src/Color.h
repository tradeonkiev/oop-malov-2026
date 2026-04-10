
#include <cstdint>

class Color
{
public:
	Color(uint32_t color);
	uint32_t GetColor();

private:
	uint32_t m_color;
};
