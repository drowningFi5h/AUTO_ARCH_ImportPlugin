# ModVehicleLoader Plugin

**Version:** 1.0  
**Engine Version:** Unreal Engine **5.6.1**  
**Modules:** Runtime (`ModVehicleLoader`), Editor (`ModVehicleLoaderEditor`)

---

## Overview

This plugin lets the game support **car mods as external `.pak` files**.  
Players (or we, during development) can drop `.pak` files into a folder, and the game automatically:

- detects them
- mounts them
- and exposes their Vehicle Blueprints to Blueprints/UI

It works in **both the Unreal Editor** and the **packaged game**.

The plugin is divided into two main systems:

| System | Purpose |
|--------|---------|
| **Runtime Loader** | Auto-detects, mounts, and loads external `.pak` cars at runtime. |
| **Editor Tool** | Helps import FBXs → assign materials → cook → generate `.pak` files for runtime use. |

---

## Directory Structure: strict folder hierarchy

The plugin depends on **correct folder names and locations**.  
If the hierarchy is wrong, mods will not load.

### Development (Inside Unreal Editor)

Place test `.pak` files here:

```

[ProjectRoot]/
└── CarImports/              <-- create manually
├── my_custom_car.pak
└── another_car.pak

```

The subsystem scans this folder while running **Play-In-Editor (PIE)**.

### Packaged / Released Game

Players should drop `.pak` mods next to the `.exe`:

```

[GameName]/
├── Binaries/
│   └── Win64/
│       └── GameName.exe
└── CAR_IMPORTS/             <-- scanned relative to the .exe
└── user_mod.pak

```

`CarImports` and `CAR_IMPORTS` are **not interchangeable**.  
Editor → `CarImports`  
Shipping build → `CAR_IMPORTS`

---

## C++ Architecture

### Runtime Module — `ModVehicleLoader`
Runs in **Editor + packaged build**.

- Class: `UModLoaderSubsystem`
- Inherits: `UGameInstanceSubsystem`
- Initialized automatically with the GameInstance

Core functions:

| Function | Description |
|----------|-------------|
| `LoadMods()` | Scans directory → mounts `.pak` files → synchronous Asset Registry rescan |
| `GetLoadedVehicleClasses()` | Returns `UClass*` array of loaded cars (filter: `BP_Car_` prefix) |
| `MountPakFile(Path)` | Uses `FPakPlatformFile` to mount external content |

### Editor Module — `ModVehicleLoaderEditor`
Runs **only inside Unreal Editor**.  
Provides tools for preparing modded vehicles (FBX → cooked → `.pak`).

---

## Blueprint Usage

No C++ required to use the loader.

1. Right-click in Blueprint → **Get Mod Loader Subsystem**
2. Call **Load Mods** (usually on `Event BeginPlay`)
3. Call **Get Loaded Vehicle Classes**  
   → use the returned array to populate a **Vehicle Select / Garage / UI list**

---

## Troubleshooting Guide (All that I know of)

| Log Output | Meaning | Fix |
|-----------|---------|-----|
| `Mod Directory not found` | Required folder not found | Create `CarImports` (Editor) or `CAR_IMPORTS` (Packaged Build) |
| `Failed to initialize PakPlatformFile` | Pak system did not initialize | Ensure `PakFile` module is in `Build.cs` (already done in plugin) |
| `Failed to Mount: [Path]` | File exists but can’t be mounted | `.pak` may be corrupted, 0 bytes, or encrypted differently |
| `Found Vehicle: BP_Car_Name` | Success | Vehicle is loaded and spawn-ready |

---


