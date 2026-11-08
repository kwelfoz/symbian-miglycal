# Miglycal Symbian

Native Symbian S60 5th Edition prototype for the Nokia 5230.

## Phase 1 target

A small, offline proof of concept that:

- launches as a native Symbian application;
- scans the memory card's `E:\\Music\\` folder for MP3 and AAC files;
- displays the discovered tracks in a simple list;
- starts playback when a track is selected.

This is deliberately not an Android port. It is a separate Symbian C++ application.

## Hardware target

- Nokia 5230
- Symbian OS 9.4
- S60 5th Edition
- 360 × 640 touchscreen
- Removable memory card normally mounted as drive `E:`

## Build environment

This project targets the legacy **S60 5th Edition SDK** with the Symbian C++ toolchain (for example, Carbide.c++ 2.0 / the matching SDK).

Open the SDK command prompt, change into the `group` directory, and run:

```bat
cd group
bldmake bldfiles
abld build gcce urel
```

The exact compiler target depends on the SDK/toolchain installed. Some legacy SDK installations use `armi` instead of `gcce`.

Package the resulting executable with the supplied `Miglycal.pkg` using the SDK's `makesis` tool:

```bat
makesis Miglycal.pkg
```

## Install and test

1. Create the folder `E:\\Music\\` on the Nokia's memory card.
2. Copy a few ordinary MP3 files into it for the first test.
3. Install `Miglycal.sis`.
4. Launch Miglycal and select a listed track.

The prototype currently scans only the memory card's `Music` folder. It does not scan internal storage, recurse through subfolders, read tags, show artwork, or build artist/album pages yet.

## Current limitations

- MP3/AAC discovery is implemented by file extension.
- Playback is delegated to Symbian's native audio player API. Actual codec/container support depends on the device firmware and installed codecs; AAC variants must be tested on the 5230.
- The first pass is intentionally small. No network access, analytics, Android dependencies, or background services are included.
- This repository has not yet been built with the original Nokia-era SDK or tested on physical hardware. A successful compile and on-device playback test are still required before calling Phase 1 complete.

## Project layout

- `inc/` — application and UI declarations
- `src/` — application, UI, and audio implementation
- `group/` — Symbian build and SIS package files
- `resources/` — application resources

## Next steps after the first device test

1. Verify MP3 playback on the actual Nokia 5230.
2. Verify AAC playback with representative files.
3. Add configurable SD-card folder selection and optional subfolder scanning.
4. Build the local library, artist splitting, artist pages, and album pages.
5. Add the five fixed accent-colour presets and refine the touch UI.
