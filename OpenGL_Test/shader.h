#pragma once

const char* vertexShaderSource =
"#version 330 core \n\
		layout(location = 0) in vec3 aPos;\n\
		layout(location = 1) in vec2 aTexture;\n\
		out vec2 TextureCoord;\n\
		uniform mat4 model;\n\
		uniform mat4 view;\n\
		uniform mat4 project;\n\
		void main() \n\
		{ \n\
			//gl_Position = vec4(aPos, 1.0);\n\
			gl_Position = project * view * model * vec4(aPos, 1.0);\n\
			TextureCoord = aTexture;\n\
		}";

const char* fragShaderSource =
"#version 330 core\n\
		out vec4 FragColor;\n\
		in vec2 TextureCoord;\n\
		uniform sampler2D ourTexture;\n\
		void main()\n\
		{\n\
			FragColor = texture(ourTexture, TextureCoord) ;\n\
		}"; 