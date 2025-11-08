#pragma once

#include <cstdint>

namespace PixelPad::Core
{
	struct Color
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;
		uint8_t A;

		constexpr Color() noexcept : R(0), G(0), B(0), A(255) { }

		constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) noexcept
			: R(red), G(green), B(blue), A(alpha) { }

		constexpr uint32_t ToRGBA() const noexcept
		{
			return (static_cast<uint32_t>(A) << 24) |
				(static_cast<uint32_t>(R) << 16) |
				(static_cast<uint32_t>(G) << 8) |
				static_cast<uint32_t>(B);
		}

		constexpr bool operator==(const Color& other) const noexcept = default;
	};
}