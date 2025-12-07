#pragma once

#include "Graphics/IRenderable.hpp"

#include <cstdint>
#include <string>

namespace PixelPad::Application
{
	struct ClickResult
	{
		std::uint32_t ButtonId;
	};

	class IUIButton : public IRenderable
	{
	public:
		virtual ~IUIButton() = default;
		virtual void OnClick(int clickX, int clickY) = 0;
		virtual std::uint32_t GetId() const = 0;
		virtual void SetActive(bool active) = 0;
		virtual bool IsActive() const = 0;
	};
}