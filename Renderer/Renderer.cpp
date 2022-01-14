#include "Renderer.h"
#include "../Texture/Texture.h"
#include "../Utils/Utils.h"
#include "../EventQueue/EventQueue.h"

#include <SDL_opengl.h>
#include <SDL_video.h>

namespace Integrian2D
{
	inline uint8_t operator"" _u(unsigned long long x) // adding _8 behind any integer (IN THIS FILE) will make it a uint8_t
	{
		ASSERT((x <= 255) && (x >= 0), "_u suffix was used for a value outside the uint8_t range [0, 255]");
		return static_cast<uint8_t>(x);
	}
}

namespace Integrian2D
{
	Renderer* Renderer::GetInstance() noexcept
	{
		ASSERT(m_pInstance != nullptr, "Renderer::GetInstance() > m_pInstance was never created! Was the Window created properly?");
		return m_pInstance;
	}

	void Renderer::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	Renderer::Renderer(SDL_Window* const pWindow)
		: m_IsNewFrame{}
		, m_ClearColour{ 192_u,192_u,192_u }
		, m_TexturesToRender{}
		, m_pWindow{ pWindow }
	{}

	void Renderer::CreateRenderer(SDL_Window* const pWindow) noexcept
	{
		ASSERT(!m_pInstance, "Renderer::CreateRenderer() > This function is called by the Core, do not manually call this function!");

		m_pInstance = new Renderer{ pWindow };
	}

	void Renderer::StartRenderLoop() noexcept
	{
		glClearColor(static_cast<float>(m_ClearColour.r) / 255.f, static_cast<float>(m_ClearColour.g) / 255.f, static_cast<float>(m_ClearColour.b) / 255.f,
			static_cast<float>(m_ClearColour.a));
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); // This is for when a camera gets added
	}

	void Renderer::Render() noexcept
	{
		ASSERT(m_IsNewFrame, "Renderer::Render() > This function was called twice this frame, don't call this function manually!");

		RenderAllTextures();

		EndRenderLoop();

		m_IsNewFrame = false;
	}

	void Renderer::SetNewFrame() noexcept
	{
		m_IsNewFrame = true;

		StartRenderLoop();
	}

	void Renderer::RenderRectangle(const Rectf& rect, const RGBColour& colour) noexcept
	{
		OpenGLRectangle rectangle{};
		rectangle.colour = colour;
		SetLeftBottom(rectangle.shapeSpecificData.rectangle, rect.xy);
		SetWidth(rectangle.shapeSpecificData.rectangle, rect.width);
		SetHeight(rectangle.shapeSpecificData.rectangle, rect.height);

		m_RectanglesToRender.push_back(rectangle);
	}

	void Renderer::RenderRectangle(const PRectf& rect, const RGBColour& colour) noexcept
	{
		OpenGLRectangle rectangle{};
		rectangle.colour = colour;
		rectangle.shapeSpecificData.rectangle = rect;

		m_RectanglesToRender.push_back(rectangle);
	}

	void Renderer::RenderFilledRectangle(const Rectf& rect, const RGBColour& colour) noexcept
	{
		OpenGLRectangle rectangle{};
		rectangle.colour = colour;
		rectangle.isFilled = true;
		SetLeftBottom(rectangle.shapeSpecificData.rectangle, rect.xy);
		SetWidth(rectangle.shapeSpecificData.rectangle, rect.width);
		SetHeight(rectangle.shapeSpecificData.rectangle, rect.height);

		m_RectanglesToRender.push_back(rectangle);
	}

	void Renderer::RenderFilledRectangle(const PRectf& rect, const RGBColour& colour) noexcept
	{
		OpenGLRectangle rectangle{};
		rectangle.colour = colour;
		rectangle.isFilled = true;
		rectangle.shapeSpecificData.rectangle = rect;

		m_RectanglesToRender.push_back(rectangle);
	}

	void Renderer::RenderTriangle(const PTrianglef& _triangle, const RGBColour& colour) noexcept
	{
		OpenGLTriangle triangle{};
		triangle.colour = colour;
		triangle.shapeSpecificData.triangle = _triangle;

		m_TrianglesToRender.push_back(triangle);
	}

	void Renderer::RenderTriangle(const Trianglef& _triangle, const RGBColour& colour) noexcept
	{
		OpenGLTriangle triangle{};
		triangle.colour = colour;
		SetCenter(triangle.shapeSpecificData.triangle,
			Point2f{ (_triangle.leftPoint + _triangle.rightPoint + Vector2f{_triangle.topPoint}) / 3.f });
		SetWidth(triangle.shapeSpecificData.triangle, GetWidth(_triangle));
		SetHeight(triangle.shapeSpecificData.triangle, GetHeight(_triangle));

		m_TrianglesToRender.push_back(triangle);
	}

	void Renderer::RenderFilledTriangle(const PTrianglef& _triangle, const RGBColour& colour) noexcept
	{
		OpenGLTriangle triangle{};
		triangle.colour = colour;
		triangle.isFilled = true;
		triangle.shapeSpecificData.triangle = _triangle;

		m_TrianglesToRender.push_back(triangle);
	}

	void Renderer::RenderFilledTriangle(const Trianglef& _triangle, const RGBColour& colour) noexcept
	{
		OpenGLTriangle triangle{};
		triangle.colour = colour;
		triangle.isFilled = true;
		SetCenter(triangle.shapeSpecificData.triangle,
			Point2f{ (_triangle.leftPoint + _triangle.rightPoint + Vector2f{_triangle.topPoint}) / 3.f });
		SetWidth(triangle.shapeSpecificData.triangle, GetWidth(_triangle));
		SetHeight(triangle.shapeSpecificData.triangle, GetHeight(_triangle));

		m_TrianglesToRender.push_back(triangle);
	}

	void Renderer::RenderLine(const PLinef& edge, const float lineWidth, const RGBColour& colour) noexcept
	{
		OpenGLLine line{};
		line.colour = colour;
		line.shapeSpecificData.line = edge;
		line.shapeSpecificData.lineWidth = lineWidth;

		m_LinesToRender.push_back(line);
	}

	void Renderer::RenderLine(const Point2f& start, const Point2f& end, const float lineWidth, const RGBColour& colour) noexcept
	{
		OpenGLLine line{};
		line.colour = colour;
		line.shapeSpecificData.line = PLinef{ start, end };
		line.shapeSpecificData.lineWidth = lineWidth;

		m_LinesToRender.push_back(line);
	}

	void Renderer::RenderCircle(const Circlef& _circle, const RGBColour& colour) noexcept
	{
		OpenGLCircle circle{};
		circle.colour = colour;
		circle.shapeSpecificData.circle = _circle;

		m_CirclesToRender.push_back(circle);
	}

	void Renderer::RenderFilledCircle(const Circlef& _circle, const RGBColour& colour) noexcept
	{
		OpenGLCircle circle{};
		circle.colour = colour;
		circle.isFilled = true;
		circle.shapeSpecificData.circle = _circle;

		m_CirclesToRender.push_back(circle);
	}

	void Renderer::RenderPolygon(const std::vector<Point2f>& points, const RGBColour& colour) noexcept
	{
		OpenGLPolygon polygon{};
		polygon.colour = colour;
		polygon.shapeSpecificData.points = points;

		m_PolygonsToRender.push_back(polygon);
	}

	void Renderer::RenderFilledPolygon(const std::vector<Point2f>& points, const RGBColour& colour) noexcept
	{
		OpenGLPolygon polygon{};
		polygon.colour = colour;
		polygon.isFilled = true;
		polygon.shapeSpecificData.points = points;

		m_PolygonsToRender.push_back(polygon);
	}

	void Renderer::RenderAllTextures() noexcept
	{
		for (const TextureInformation& textureInformation : m_TexturesToRender)
		{
			// Determine texture coordinates using srcRect and default destination width and height
			float textLeft{};
			float textRight{ 1.f };
			float textTop{};
			float textBottom{ 1.f };

			const float textureWidth{ textureInformation.pTexture->GetWidth() };
			const float textureHeight{ textureInformation.pTexture->GetHeight() };

			float defaultDestWidth{ textureWidth };
			float defaultDestHeight{ textureHeight };

			if (!Utils::AreEqual(textureInformation.sourceRect.width, 0.f) && !Utils::AreEqual(textureInformation.sourceRect.height, 0.f)) // srcRect specified
			{
				// Convert to the range [0.0, 1.0]
				textLeft = textureInformation.sourceRect.x / textureWidth;
				textRight = (textureInformation.sourceRect.x + textureInformation.sourceRect.width) / textureWidth;
				textTop = (textureInformation.sourceRect.y - textureInformation.sourceRect.height) / textureHeight;
				textBottom = textureInformation.sourceRect.y / textureHeight;

				defaultDestWidth = textureInformation.sourceRect.width;
				defaultDestHeight = textureInformation.sourceRect.height;
			}

			// Determine vertex coordinates
			const Point2f& leftBottom{ GetLeftBottom(textureInformation.destRect) };
			const Point2f& leftTop{ GetLeftTop(textureInformation.destRect) };
			const Point2f& rightTop{ GetRightTop(textureInformation.destRect) };
			const Point2f& rightBottom{ GetRightBottom(textureInformation.destRect) };

			// Tell opengl which texture we will use
			glBindTexture(GL_TEXTURE_2D, textureInformation.pTexture->GetTextureID());
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Draw
			glEnable(GL_TEXTURE_2D);
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(textLeft, textBottom);
					glVertex2f(leftBottom.x, leftBottom.y);

					glTexCoord2f(textLeft, textTop);
					glVertex2f(leftTop.x, leftTop.y);

					glTexCoord2f(textRight, textTop);
					glVertex2f(rightTop.x, rightTop.y);

					glTexCoord2f(textRight, textBottom);
					glVertex2f(rightBottom.x, rightBottom.y);
				}
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}

		for (const OpenGLRectangle& shape : m_RectanglesToRender)
			InternalRenderRectangle(shape.shapeSpecificData.rectangle, shape.colour, shape.isFilled);

		for (const OpenGLTriangle& shape : m_TrianglesToRender)
			InternalRenderTriangle(shape.shapeSpecificData.triangle, shape.colour, shape.isFilled);

		for (const OpenGLLine& shape : m_LinesToRender)
			InternalRenderLine(shape.shapeSpecificData.line, shape.shapeSpecificData.lineWidth, shape.colour);

		for (const OpenGLCircle& shape : m_CirclesToRender)
			InternalRenderCircle(shape.shapeSpecificData.circle, shape.colour, shape.isFilled);

		for (const OpenGLPolygon& shape : m_PolygonsToRender)
			InternalRenderPolygon(shape.shapeSpecificData.points, shape.colour, shape.isFilled);

		m_RectanglesToRender.clear();
		m_TrianglesToRender.clear();
		m_LinesToRender.clear();
		m_CirclesToRender.clear();
		m_PolygonsToRender.clear();
	}

	void Renderer::EndRenderLoop() noexcept
	{
		glPopMatrix(); // This is for when a camera gets added

		// == Swap back- and frontbuffer ==
		SDL_GL_SwapWindow(m_pWindow);

		m_TexturesToRender.clear();
	}

	void Renderer::InternalRenderRectangle(const PRectf& rect, const RGBColour& colour, const bool isFilled) noexcept
	{
		glColor3ub(colour.r.v, colour.g.v, colour.b.v);

		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);
		{
			glVertex2f(GetLeftBottom(rect).x, GetLeftBottom(rect).y);
			glVertex2f(GetLeftTop(rect).x, GetLeftTop(rect).y);
			glVertex2f(GetRightTop(rect).x, GetRightTop(rect).y);
			glVertex2f(GetRightBottom(rect).x, GetRightBottom(rect).y);
		}
		glEnd();
	}

	void Renderer::InternalRenderTriangle(const PTrianglef& triangle, const RGBColour& colour, const bool isFilled) noexcept
	{
		glColor3ub(colour.r.v, colour.g.v, colour.b.v);

		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);
		{
			for (const Point2f& p : triangle)
				glVertex2f(p.x, p.y);
		}
		glEnd();
	}

	void Renderer::InternalRenderLine(const PLinef& edge, const float lineWidth, const RGBColour& colour) noexcept
	{
		glColor3ub(colour.r.v, colour.g.v, colour.b.v);
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(edge.begin.x, edge.begin.y);
			glVertex2f(edge.end.x, edge.end.y);
		}
		glEnd();
	}

	void Renderer::InternalRenderCircle(const Circlef& circle, const RGBColour& colour, const bool isFilled) noexcept
	{
		glColor3ub(colour.r.v, colour.g.v, colour.b.v);

		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINES);
		{
			for (float i{}; i < 360.f; ++i)
				glVertex2f(circle.position.x + circle.radius * cosf(i), circle.position.y + circle.radius * sinf(i));
		}
		glEnd();
	}

	void Renderer::InternalRenderPolygon(const std::vector<Point2f>& points, const RGBColour& colour, const bool isFilled) noexcept
	{
		glColor3ub(colour.r.v, colour.g.v, colour.b.v);

		if (isFilled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINES);
		{
			for (const Point2f& p : points)
				glVertex2f(p.x, p.y);
		}
		glEnd();
	}

	void Renderer::RenderTexture(Texture* const pTexture, const PRectf& destRect, const Rectf& sourceRect) noexcept
	{
		m_TexturesToRender.push_back(TextureInformation{ pTexture, destRect, sourceRect });
	}
}