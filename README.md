# ClickCounter

A lightweight [Geode](https://geode-sdk.org/) mod for **Geometry Dash 2.2081** that displays a real-time click counter in the top-left corner of the screen while you play a level.

---

## What it does

While playing any level, a small label appears in the top-left corner:

```
CC: 42
```

`CC` stands for **Click Counter**. The number updates instantly with every input you make.

- ✅ Counts every press (jump, secondary button, dual mode)
- ✅ Resets automatically on retry
- ✅ Disappears cleanly when you exit the level
- ✅ Works in normal mode and practice mode
- ✅ No configuration needed — just install and play

---

## Installation

1. Make sure you have [Geode](https://geode-sdk.org/) installed.
2. Download the latest `.geode` file from the [Releases](../../releases) page.
3. Drop it into your Geode mods folder:
   ```
   C:\Users\<you>\AppData\Local\GeometryDash\geode\mods\
   ```
4. Launch Geometry Dash — the mod loads automatically.

---

## Building from source

**Requirements:**
- [Geode SDK](https://docs.geode-sdk.org/getting-started/) installed and `GEODE_SDK` environment variable set
- CMake 3.21+
- Visual Studio 2022 (Windows) or Clang (macOS/Linux)

**Steps:**
```bash
git clone https://github.com/cdramirez25/clickcounter
cd clickcounter
cmake -B build
cmake --build build --config RelWithDebInfo
```

The `.geode` file will be placed in your mods folder automatically by the Geode build system.

---

## Project structure

```
ClickCounter/
├── src/
│   └── main.cpp       # All mod logic (hooks + label)
├── mod.json           # Mod metadata
├── CMakeLists.txt     # Build configuration
├── CHANGELOG.md       # Version history
└── README.md          # This file
```

---

## How it works

The mod hooks two classes from GD's internals:

- **`GJBaseGameLayer::handleButton`** — fires on every player input. Increments the counter only on button-down events to avoid counting releases as extra clicks.
- **`PlayLayer::init`** — creates the `CC: 0` label when a level starts and attaches it directly to the play layer at z-order 100 so it renders on top of everything.
- **`PlayLayer::resetLevel`** — resets the counter to 0 on each retry.
- **`PlayLayer::onQuit`** — cleans up the label reference when the level is exited.

---

## Contributing

Pull requests are welcome! If you find a bug or want to suggest a feature, open an [issue](../../issues).

Ideas for future versions:
- Option to show/hide the counter via a settings toggle
- Show clicks per attempt in the end screen
- Separate counters for Player 1 and Player 2 in dual mode
- Best/average clicks per attempt tracking

---

*Made with ❤️ using [Geode SDK](https://geode-sdk.org/)*
