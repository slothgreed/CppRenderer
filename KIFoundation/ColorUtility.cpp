
namespace KI
{
namespace Foundation
{
std::vector<vec3> ColorUtility::m_pseudoColor(0);
ColorUtility::ColorUtility()
{
}

ColorUtility::~ColorUtility()
{
}

vec3 ColorUtility::IndexToColor(int index)
{
	vec3 color;
	color.r = (float)((index & 0x000000FF) >> 0) / 255.0f;
	color.g = (float)((index & 0x0000FF00) >> 8) / 255.0f;
	color.b = (float)((index & 0x00FF0000) >> 16) / 255.0f;
	return color;
}

void ColorUtility::InitializePseudoColor()
{
    m_pseudoColor.resize(256);
    float scale = 4;
    for (int i = 0; i < 256; i++)
    {
        if (i <= 63)
        {
            m_pseudoColor[i].x = 0 / 255.0f;
            m_pseudoColor[i].y = scale * i / 255.0f;
            m_pseudoColor[i].z = 255 / 255.0f;
            continue;
        }
        if (i <= 127)
        {
            m_pseudoColor[i].x = 0 / 255.0f;
            m_pseudoColor[i].y = 255 / 255.0f;
            m_pseudoColor[i].z = (255 - (scale * (i - 64))) / 255.0f;
            continue;
        }
        if (i <= 191)
        {
            m_pseudoColor[i].x = (scale * (i - 127)) / 255.0f;
            m_pseudoColor[i].y = 255 / 255.0f;
            m_pseudoColor[i].z = 0 / 255.0f;
            continue;
        }
        if (i <= 255)
        {
            m_pseudoColor[i].x = 255 / 255.0f;
            m_pseudoColor[i].y = (255 - (scale * (i - 192))) / 255.0f;
            m_pseudoColor[i].z = 0 / 255.0f;
            continue;
        }
    }
}

vec3 ColorUtility::GetPseudoColor(float value, float min, float max)
{
    if (m_pseudoColor.size() == 0) {
        InitializePseudoColor();
    }

    if (max < value)
    {
        return m_pseudoColor[255];
    }
    if (min > value)
    {
        return m_pseudoColor[0];
    }
    float length = max - min;
    float scale = 255 * (value - min) / length;
    return m_pseudoColor[(int)scale];
}
}
}
