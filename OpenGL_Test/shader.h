#pragma once

const char* vertexShaderSource =
"#version 330 core \n\
		layout(location = 0) in vec3 aPos;\n\
		layout(location = 1) in vec3 aPosColor;\n\
		layout(location = 2) in vec2 aTexture;\n\
		//out vec4 vertexColor;\n\
		out vec3 posColor;\n\
		out vec2 TextureCoord;\n\
		void main() \n\
		{ \n\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
			//vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n\
			posColor = aPosColor;\n\
			TextureCoord = aTexture;\n\
		}";

const char* fragShaderSource =
"#version 330 core\n\
		out vec4 FragColor;\n\
		//in vec4 vertexColor;\n\
		in vec3 posColor;\n\
		in vec2 TextureCoord;\n\
		uniform sampler2D ourTexture;\n\
		void main()\n\
		{\n\
			//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
			//FragColor = vertexColor;\n\
			//FragColor = vec4(posColor, 1.0f);\n\
			FragColor = texture(ourTexture, TextureCoord) * vec4(posColor, 1.0f);\n\
		}"; 