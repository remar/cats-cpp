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

      \brief Creates a window with the given dimension.

      @param width Width of the window in pixels

      @param height Height of the window in pixels
   */
  void Init(int width, int height, float multiplier = 1.0f);

  /** \fn void Redraw(float delta)

      \brief Redraws the screen, call once each frame.

      @param delta Seconds since last frame
   */
  void Redraw(float delta);

  /** \fn void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue)

      \brief Sets color that is used when clearing the screen before redrawing.

      @param red Red component
      @param green Green component
      @param blue Blue component
   */
  void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);

  /* TODO: documentation */
  void SetFullscreen(bool on);

  /* TODO: documentation */
  void ShowPointer(bool on);

  /* TODO: documentation */
  void SetWindowTitle(std::string title);

  /** \fn void LoadSprite(std::string filename)

      \brief Loads a sprite from the provided JSON file.

      A sprite is specified in a JSON object, containing the key
      "animations". "animations" points to an object containing the
      animations, with the keys used as animation names. The name of
      the JSON file determines the sprites name, e.g. the filename
      "hero.json" means that the sprite will be called "hero".

      Each animation is specified as an object, containing the keys
      "image", "origin", "looping" and "frames". "image" contains an object
      describing the image path and frame dimensions. "origin", which is
      optional, contains the center of each frame as a list of offsets.  If
      "origin" is missing, it will default to [0, 0] (upper left corner).
      "looping" indicates whether this animation should loop or not.
      "frames" contains a list of lists, where each such list points out an
      index into the image and a duration in milliseconds. A frame index of
      -1 indicates that the sprite will be hidden during the frames
      duration.

      The images path is relative to the sprite definitions path, so a
      path of just "goomba.png" means that the image will be found as
      a neighbour to the sprite definition.

      Example sprite definition:
      <pre>
      {
          "animations": {
              "animation 1": {
                  "image": {
                      "path":"path/to/animation.png",
                      "width":32,
                      "height":32
                  },
                  "origin": [16, 16],
                  "looping": true,
                  "frames": [
                      [0, 100], [1, 150], [2, 100], [1, 150]
                  ]
              },
              "animation 2": {
                  "image": {
                      "path":"path/to/animation.png",
                      "width":32,
                      "height":32
                  },
                  "looping": true,
                  "frames": [
                      [0, 100], [1, 150], [2, 100], [1, 150]
                  ]
              }
          }
      }
      </pre>

      @param filename Relative path to JSON sprite definition file
   */
  void LoadSprite(std::string filename);

  /** \fn int CreateSpriteInstance(std::string spritename)

      \brief Creates a sprite instance of a loaded sprite definition.

      @param name Name of the sprite definition, same as the filename
      but without the .json suffix

      @return ID used to indicate this sprite instance
   */
  int CreateSpriteInstance(std::string spritename);

  /** \fn void RemoveSpriteInstance(int spriteId)

      \brief Removes the provided sprite instance.

      @param id ID of a sprite instance
   */
  void RemoveSpriteInstance(int spriteId);

  /** \fn void ShowSprite(int spriteId, bool show)

      \brief Shows or hides a sprite instance.

      @param id ID of a sprite instance

      @param show Indicates whether this sprite instance should be
      visible or not
   */
  void ShowSprite(int spriteId, bool show);

  /** \fn void SetSpritePosition(int spriteId, int x, int y)

      \brief Sets a sprite instances position in screen coordinates.

      @param id ID of a sprite instance

      @param x x component of the position

      @param y y component of the position

   */
  void SetSpritePosition(int spriteId, int x, int y);

  /* TODO: documentation */
  void MoveSprite(int spriteId, int deltaX, int deltaY);

  /** \fn void SetAnimation(int spriteId, std::string animation)

      \brief Sets the sprite instances animation.

      The animation will start from the beginning.

      @param id ID of a sprite instance

      @param animation Name of an animation

   */
  void SetAnimation(int spriteId, std::string animation);

  /* TODO: documentation */
  void PauseAnimation(int spriteId, bool on);

  /* TODO: documentation */
  void PauseAnimations(bool on);

  /** \fn void SetupTileLayer(int width, int height, int tileWidth, int tileHeight)

      \brief Setup a tile background.

      The background will contain width*height tiles. Each
      individual tiles height and width is also specified.

      @param width Width of the tilemap

      @param height Height of the tilemap

      @param tileWidth Width of a tile

      @param tileHeight Height of a tile
   */
  void SetupTileLayer(int width, int height, int tileWidth, int tileHeight);

  /** \fn void LoadTileset(std::string filename)

      \brief Loads in the provided tileset.

      A tileset is specified in a JSON object, containing the key
      "image". "image" contains an object describing the image path
      and tile dimensions. The name of the JSON file determines the
      tilesets name, e.g. the filename "blocks.json" means that the
      tileset will be called "blocks".

      The images path is relative to the tileset definitions path, so a path
      of just "blocks.png" means that the image will be found as a neighbour
      to the tileset definition.

      <pre>
      {
          "image": {
              "path":"path/to/blocks.png",
              "width":16,
              "height":16,
          }
      }
      </pre>

      @param file Relative path to the tileset definition file
   */
  void LoadTileset(std::string filename);

  /** \fn void SetTile(int x, int y, std::string tileset, int tileX, int tileY)

      \brief Sets the tile at position x, y to the tile found in the provided
      tileset at location tileX, tileY.

      @param x x position in the tilemap where the tile will be set

      @param y y position in the tilemap where the tile will be set

      @param tileset Name of the tileset to use

      @param tileX x offset into the tileset

      @param tileY y offset into the tileset
   */
  void SetTile(int x, int y, std::string tileset, int tileX, int tileY);

  /** \fn void SetScroll(int x, int y)

      \brief Sets the scroll of the tile layer.

      @param x x offset of the tile layer

      @param y y offset of the tile layer

   */
  void SetScroll(int x, int y);

  /* TODO: documentation */
  void LoadFont(std::string fontfile);

  /* TODO: documentation */
  int CreateText(std::string font, std::string text);

  /* TODO: documentation */
  void SetTextPosition(int textId, int x, int y);

  /* TODO: documentation */
  void ShowText(int textId, bool show);

  /* TODO: documentation */
  void RemoveText(int textId);
}

#endif
