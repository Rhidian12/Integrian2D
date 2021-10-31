#pragma once
// ===========================
// Bart Uyttenhove, professor at DAE created this class
// I took it, with permission, and changed it to suit this engine
// ===========================
#include "../Math/TypeDefines.h"

#include <string> // std::string
#include <SDL_opengl.h> // GLUint
#include <SDL_ttf.h> // TTF_Font

struct SDL_Surface;
namespace Integrian2D
{
	class Texture final
	{
	public:
		explicit Texture(const std::string& imagePath);
		explicit Texture(const std::string& text, const std::string& fontPath, const int ptSize, const RGBColour& textColor);
		~Texture();

		/* Returns the Texture width */
		float GetWidth() const noexcept;

		/* Returns the Texture height */
		float GetHeight() const noexcept;

		/* Returns whether the creation of the Texture succeeded */
		bool IsCreationOk() const noexcept;

		/* Get the ID assigned to the Texture */
		unsigned int GetTextureID() const noexcept;

		Texture(const Texture& other) noexcept;
		Texture(Texture&& other) noexcept;
		Texture& operator=(const Texture& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

	private:
		//DATA MEMBERS
		GLuint m_Id;
		float m_Width;
		float m_Height;
		bool m_CreationOk;

		// FUNCTIONS
		void CreateFromImage(const std::string& path) noexcept;

		/* Function copies RGBColour by value because it calls MaxToOne */
		void CreateFromString(const std::string& text, TTF_Font* const pFont, RGBColour textColor) noexcept;
		void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const RGBColour& textColor) noexcept;
		void CreateFromSurface(SDL_Surface* const pSurface) noexcept;
		void DrawFilledRect(const Rectf& dstRect) const noexcept;
	};
}