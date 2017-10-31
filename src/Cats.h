// -*- mode: c++ -*-

/**
   \mainpage Cats++ API Documentation

   \section intro Introduction

   Cats++ is the C++ implementation of Cats. It is an abstraction for
   making 2D games with tiled backgrounds and animated sprites.

   The specification is found at https://github.com/remar/cats-doc
 */

#ifndef CATS_H
#define CATS_H

#include <string>

/** \namespace Cats

    Namespace that contains the Cats++ API.
 */
namespace Cats {
  /** \fn void Init(int width, int height)

      Creates a window with the given dimension.

      @param width Width of the window in pixels

      @param height Height of the window in pixels
   */
  void Init(int width, int height);

  /** \fn void Redraw(float delta)

      Redraws the screen, call once each frame.

      @param delta Seconds since last frame
   */
  void Redraw(float delta);

  /** \fn void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)

      Set color that is used when clearing the screen before redrawing.

      @param red Red component
      @param green Green component
      @param blue Blue component
   */
  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);
  void LoadSprite(std::string filename);
  int CreateSpriteInstance(std::string spritename);
  void RemoveSpriteInstance(int spriteId);
  void ShowSprite(int spriteId, bool show);
  void SetSpritePosition(int spriteId, int x, int y);
  void SetAnimation(int spriteId, std::string animation);
  void SetupTileLayer(int width, int height, int tileWidth, int tileHeight);
  void LoadTileset(std::string filename);
  void SetTile(int x, int y, std::string tileset, int tileX, int tileY);
  void SetScroll(int x, int y);
}

#endif
