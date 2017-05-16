#version 430 core
layout (points) in;
layout (triangle_strip, max_vertices = 27) out;

out vec3 outColor;

in VS_GS_VERTEX{
	in vec4 position;
	in vec3 color;
	in mat4 mvp;
} gs_in[];

void main()
{
	outColor = gs_in[0].color;

//	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-2.0f, 0.0f, 0.0f, 0.0f);
//	EmitVertex();
//	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(2.0f, 0.0f, 0.0f, 0.0f);
//	EmitVertex();
//	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, 2.0f, 0.0f, 0.0f);
//	EmitVertex();

	
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(3.5f, -8.8f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(2.0f, -14.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(7.0f, -11.5f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(7.0f, -11.5f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(12.0f, -14.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(10.5f, -9.0f, 0.0f, 0.0f);
	EmitVertex();

	
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(10.5f, -9.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(14.0f, -5.5f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(9.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(9.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(7.0f, 0.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(5.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(5.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, -5.5f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(3.5f, -8.8f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(3.5f, -8.8f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(7.0f, -11.5f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(10.5f, -9.0f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(10.5f, -9.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(9.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(3.5f, -8.8f, 0.0f, 0.0f);
	EmitVertex();

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(3.5f, -8.8f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(5.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(9.0f, -5.0f, 0.0f, 0.0f);
	EmitVertex();

	EndPrimitive();
}