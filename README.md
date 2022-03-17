# Poison Strike 🚁
<p align="center">
  <img alt="Version" src="https://img.shields.io/github/v/tag/kyuuzou/poison-strike?label=version" />
  <a href="https://github.com/kyuuzou/poison-strike/issues" target="_blank">
     <img alt="GitHub issues" src ="https://img.shields.io/github/issues-raw/kyuuzou/poison-strike" />
  </a>

  <a href="https://github.com/kyuuzou/poison-strike/pulls" target="_blank">
   <img alt="GitHub pull requests" src ="https://img.shields.io/github/issues-pr-raw/kyuuzou/poison-strike" />
  </a>
  
  <img alt="GitHub last commit" src ="https://img.shields.io/github/last-commit/kyuuzou/poison-strike" />
</p>
<p align="center">
  <a href="https://www.codacy.com/gh/kyuuzou/poison-strike/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=kyuuzou/poison-strike&amp;utm_campaign=Badge_Grade" target="_blank"><img src="https://app.codacy.com/project/badge/Grade/d2c5f4c88f2a46218ccf465d528fb76b"/></a>
  <a href="https://github.com/kyuuzou/poison-strike/blob/master/LICENSE" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-blue.svg" />
  </a>

</p>

## Description
A spiritual successor to Miniclip's Ores, made in C++ with SDL 2.0.

## Gameplay Video

[![Gameplay Video](https://github.com/kyuuzou/poison-strike/blob/master/thumbnail.png)](https://www.youtube.com/watch?v=J1tMeTlPNzU "Gameplay Video")

*Disclaimer: the background and the boat textures are copyrighted placeholders, not included on this repository.*

## Why it Exists

In March of 2016, I was challenged by <a href="https://www.miniclip.com/" target="_blank">Miniclip</a> to implement a clone of their classic game Ores. After a few days, Poison Strike came into being.

I had quite a bit of fun tackling this project, here are some technical details about it:
- It is fully integrated with <a href="https://www.mapeditor.org/" target="_blank">Tiled Map Editor</a>'s TMX files. Each screen of the game corresponds to an xml file completely editable on Tiled, including every game object, from the background to the UI.
- It is also integrated with <a href="https://www.codeandweb.com/texturepacker" target="_blank">TexturePacker</a>, a tool for compiling textures into an atlas. The atlas' accompanying xml is parsed by the game, and each texture is mapped to the game object parsed from Tiled, via two custom properties (defined on tiled) called AtlasID and TextureID, associated with each game object.
- Some of the textures had an incorrect sRGB profile, and SDL didn't like that, so I created an [msdos batch file](https://github.com/kyuuzou/poison-strike/blob/master/SDLSandbox/SDLSandbox/Tools/PNGCrush/run.bat) which removes the invalid profile from the textures, via <a href="https://pmt.sourceforge.io/pngcrush/" target="_blank">PNGCrush</a>.
- Some of the design patterns on this project: a <a href="https://refactoring.guru/design-patterns/state" target="_blank">State Machine</a> for navigating the game, an <a href="https://refactoring.guru/design-patterns/factory-method" target="_blank">Object Factory</a> for creating the game objects, a <a href="https://gameprogrammingpatterns.com/service-locator.html" target="_blank">Service Locator</a> for low coupling, a <a href="https://refactoring.guru/design-patterns/command" target="_blank">Command Pattern</a> for mapping actions to the UI.
- Most of the sounds were generated on <a href="https://www.bfxr.net/" target="_blank">Bfxr</a> (this part was fun).
- I edited the sprite placeholders on <a href="https://www.gimp.org/" target="_blank">Gimp</a> (this part was even more fun, and I spent more time doing this than I'd want to admit).
- Finally, the game has an unintended easter egg, which I left in because I ended up liking it: since the titles for each screen are made out of boxes, the player can wreak havoc on the title by clicking (and consequently destroying) the boxes.
- For managing the parallel builds on different operating systems, I used a simple <a href="https://www.dropbox.com/" target="_blank">Dropbox</a> folder, to synchronize the Visual Studio and Xcode projects in real time, between my PC and Macbook.
- Finally, on the Windows version, "Visual C++ Redistributable for Visual Studio x86" is statically linked, so the user does not need to have the libraries previously installed.


## Dependencies

- C++14-compatible compiler
- [SDL 2.0](https://www.libsdl.org/download-2.0.php)
- [SDL_image 2.0](https://www.libsdl.org/projects/SDL_image/)
- [SDL_mixer 2.0](https://www.libsdl.org/projects/SDL_mixer/)

## Folder Structure

```
.
├── SDLSandbox    # Main project, for Visual Studio 2015 on Windows
├── OSX           # Secondary project, for Xcode on OSX. Links to the source and assets of the main project.
├── LICENSE
└── README.md
```

## Version History

* 0.1.0
    * Initial Release (version submitted to Miniclip)


## Contacting the Author

* Email: newita@gmail.com
* Github: [@kyuuzou](https://github.com/kyuuzou)
* LinkedIn: [@nelson-rodrigues-ba4ab263](https://linkedin.com/in/nelson-rodrigues-ba4ab263)
* Portfolio: http://kyuandcaffeine.com

## License

Copyright © 2016 [Nelson Rodrigues](https://github.com/kyuuzou).<br />
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

## Acknowledgments
[@Farious](https://github.com/Farious) took on this challenge as well! Check it out: [Farious' GemBreaker](https://github.com/Farious/GemBreaker)
  