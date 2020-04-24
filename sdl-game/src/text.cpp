#include "text.h"
#include "window.h"
#include <iostream>

Text::Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color, int x, int y) : _x(x), _y(y)
{
	// Load the texture
	_text_texture = loadTexture(renderer, font_path, font_size, message_text, color);
	
	// Get texture width and height from font size and text length
	// Save this info to the text rectangle
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

// Renders text rectangle to screen every tick
void Text::draw(SDL_Renderer *renderer) const {
	// Update position
	_text_rect.x = _x;
	_text_rect.y = _y;

	// If texture exists, then copy texture to rectangle.
	if (_text_texture) {
		SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
	}
	
}

// Reload texture with new string value
void Text::reloadTexture(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color) {
	// Load the texture 
	_text_texture = loadTexture(renderer, font_path, font_size, message_text, color);
	
	// Get texture width and height from font size and text length
	// Save this info to the text rectangle
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

// Load the texture of the string
SDL_Texture* Text::loadTexture(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color) {
	// Create font from font path
	TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
	
	// Check that font was created successfully
	if (!font) {
		std::cerr << "Failed to load font.\n";
	}

	// Create surface from a string message, font, and color
	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	
	// Check that surface was created successfully
	if (!text_surface) {
		std::cerr << "Failed to create text surface.\n";
	}

	// Create texture from surface
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	
	// Check if texture was created successfully
	if (!text_texture) {
		std::cerr << "Failed to create text texture.\n";
	}
	
	// Free surface memory
	SDL_FreeSurface(text_surface);

	// Return the texture
	return text_texture;
}