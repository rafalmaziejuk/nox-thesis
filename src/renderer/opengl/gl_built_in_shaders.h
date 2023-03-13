#pragma once

#include <string_view>

namespace NOX {

    constexpr std::string_view fullscreenQuadVertexShaderSource = R"(
		#version 460 core

		layout (location = 0) in vec2 aPosition;
		layout (location = 1) in vec2 aTextureCoordinates;

		out vec2 textureCoordinates;

		void main() {
			gl_Position = vec4(aPosition, 0.0, 1.0); 
			textureCoordinates = aTextureCoordinates;
		}
	)";

    constexpr std::string_view fullscreenQuadFragmentShaderSource = R"(
		#version 460 core

		in vec2 textureCoordinates;
		out vec4 fragmentColor;

		layout (location = 0) uniform sampler2D fullscreenTexture;

		void main() { 
			fragmentColor = texture(fullscreenTexture, textureCoordinates);
		}
	)";

} // namespace NOX
