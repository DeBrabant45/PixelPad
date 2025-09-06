#include "Graphics/UIButton.hpp"
#include "Renderers/IRenderer.hpp"

namespace PixelPad::Infrastructure
{
	PixelPad::Infrastructure::UIButton::UIButton(int x, int y, int w, int h, std::shared_ptr<PixelPad::Application::ITexture> texture) :
		m_transform{ x, y, w, h },
		m_texture(texture),
		m_callback(nullptr)
	{

	}

	void UIButton::Render(PixelPad::Application::IRenderer& renderer)
	{
		//if (!m_texture)
		//{
		//	m_texture = renderer.CreateTexture(m_texturePath);
		//	if (!m_texture)
		//	{
		//		std::cerr << "Failed to load PencilTool texture: " << m_texturePath << "\n";
		//		return;
		//	}
		//}
		if (!m_texture)
			return;

		renderer.DrawTexture(
			m_texture.get(),
			m_transform.x,
			m_transform.y,
			m_transform.width,
			m_transform.height
		);
	}

	void UIButton::OnClick(const std::function<void()>& callback)
	{
		m_callback = callback;
	}

	void UIButton::HandleClick(int clickX, int clickY)
	{
		if (clickX >= m_transform.x && clickX <= m_transform.x + m_transform.width &&
			clickY >= m_transform.y && clickY <= m_transform.y + m_transform.height)
		{
			if (m_callback) 
				m_callback();
		}
	}

	PixelPad::Application::Transform UIButton::GetTransform() const
	{
		return m_transform;
	}
}