# Unreal Engine Stealth Game Tutorial

Based on the course[Unreal Engine 4 Mastery: Create Multiplayer Games with C++](https://www.udemy.com/course/unrealengine-cpp/) by Tom Looman, forked from https://github.com/tomlooman/SimpleFPSTemplate.


# Usage

Download release, start it on Win64.

Start game exe, have fun. Rules:

- **Move around** with WASD/Space. **Avoid guards.** If they see anybodyin the team, mission is failed. Try to **grab the objective and escort it to the extraction zone**.
- Shoot with the mouse to launch bombs distract the guards. 

## Change resolution

- Open console with `F12`
- Issue commands similar to the following examples, where the letter following the resolution is a **fullscreen** or **windowed** mode: `r.SetRes 600x400f`, `r.SetRes 600x400w`.


## Multiplayer mode

- Open console with `F12`
- Server: `open FirstPersonExampleMap?listen`
- Client: `open <SERVER-IP>:7777` or `open <SERVER-IP>`


# License

This project is licensed under the Unreal Engine 4 EULA.
