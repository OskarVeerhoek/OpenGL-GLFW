#version 150 core

layout (triangles) in;
layout (triangles, max_vertices = 3) out;

in VertexData
{
    vec4 color;
    vec3 normal;
}

void main()
{
    for(int i = 0; i < gl_in.length; i++)
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EmitPrimitive();
}
