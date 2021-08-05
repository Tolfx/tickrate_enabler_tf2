# Tickrate Enabler

![Downloads](https://img.shields.io/github/downloads/zer0k-z/truestrike/total?style=flat-square) ![Last commit](https://img.shields.io/github/last-commit/zer0k-z/truestrike?style=flat-square) ![Open issues](https://img.shields.io/github/issues/zer0k-z/truestrike?style=flat-square) ![Closed issues](https://img.shields.io/github/issues-closed/zer0k-z/truestrike?style=flat-square) ![Size](https://img.shields.io/github/repo-size/zer0k-z/truestrike?style=flat-square)

In CS:GO, tick intervals are quantized to the nearest N / 512 fraction. 

The only possible tickrates are: 128.0, 102.4, 85.33, 73.14, 64.0, 56.89, 51.2, 46.55, 42.67, 39.38, 36.57, 34.13, 32.0, 30.12, 28.44, 26.95, 25.60, 24.38, 23.27, 22.26, 21.33, 20.48.

The CS:GO port of Tickrate Enabler gets rid of this limitation.

## How to use:
1. Get the latest release for your OS at: `https://github.com/zer0k-z/TickrateEnablerCSGO/releases`

2. Extract the archive to your server folder

3. Add `-tickrate <number>` to your launch parameters

## Linux Build Instructions:

1. Clone `https://github.com/alliedmodders/hl2sdk` to the branch 'csgo' and set HL2SDK in the Makefile to the root of the git repo.

2. Clone and build `https://github.com/alliedmodders/metamod-source`, then set MMSDK in the Makefile accordingly.

3. Run `make`

## Windows Build Instructions:

*Note*: Use Visual Studio 2013, later versions don't seem to be working.

1. Clone `https://github.com/alliedmodders/hl2sdk/tree/csgo` and set HL2SDKCSGO environment variable to the root of the git repo.

2. Clone and build `https://github.com/alliedmodders/metamod-source` with the `Release - CSGO` configuration, then set MMSDK (in your environment variables) accordingly.

3. Open and build the solution

4. You'll find 'tickrate_enabler.dll' in the `tickrate_enabler\Release` folder