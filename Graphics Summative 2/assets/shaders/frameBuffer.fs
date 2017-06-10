#version 430 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D texFramebuffer;
uniform bool Greyscale;
uniform bool Motionblur;

const float blurSizeH = 1.0 / 300.0;
const float blurSizeV = 1.0 / 200.0;
 
void main()
{
	color = texture(texFramebuffer, TexCoords);

	if (Motionblur)
	{
		vec4 sum = vec4(0.0);

		for (int x = -4; x <= 4; x++)
			for (int y = -4; y <= 4; y++)
				sum += texture(
					texFramebuffer, vec2(TexCoords.x + x * blurSizeH, TexCoords.y + y * blurSizeV)) / 81.0;
		color = sum;
	}

	if (Greyscale)
	{
		float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
		color = vec4(average, average, average, 1.0);
	}
}

