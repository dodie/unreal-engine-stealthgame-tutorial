# Unreal Engine Stealth Game Tutorial

Based on the course[Unreal Engine 4 Mastery: Create Multiplayer Games with C++](https://www.udemy.com/course/unrealengine-cpp/) by Tom Looman, forked from https://github.com/tomlooman/SimpleFPSTemplate.

By default, the game works in single player mode, and can be used in multiplayer mode.

![Game](https://raw.githubusercontent.com/dodie/unreal-engine-stealthgame-tutorial/dodi/game.jpg "Game")


# Usage

Download the [release](https://github.com/dodie/unreal-engine-stealthgame-tutorial/releases/), extraxt, start it on Win64.

Rules:

- **Move around** with WASD/Space. **Avoid guards.** If they see anybodyin the team, mission is failed. Try to **grab the objective and escort it to the extraction zone**.
- Shoot with the mouse to launch bombs distract the guards. 

## Change resolution

- Open console with `F12`
- Issue commands similar to the following examples, where the letter following the resolution is a **fullscreen** or **windowed** mode: `r.SetRes 600x400f`, `r.SetRes 600x400w`.


## Multiplayer mode

- Open console with `F12`
- Start Server: `open FirstPersonExampleMap?listen`
- Join with Client: `open <SERVER-IP>:7777` or `open <SERVER-IP>`


# Development

- Requires Unreal Engine 4.18.*


# License

This project is licensed under the Unreal Engine 4 EULA.
