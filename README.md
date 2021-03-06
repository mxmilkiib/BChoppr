# B.Choppr
An audio stream chopping LV2 plugin.

Description: B.Choppr cuts the audio input stream into a repeated sequence of up to 16 chops.
Each chop can be leveled up or down (gating). B.Choppr is the successor of B.Slizr.

![screenshot](https://raw.githubusercontent.com/sjaehn/BChoppr/master/doc/screenshot.png "Screenshot from B.Choppr")

## Installation

a) Install the bchoppr package for your system
* [Arch user repository](https://aur.archlinux.org/packages/bchoppr-git) by Milk Brewster
* [Debian](https://kx.studio/Repositories:Plugins) by falkTX
* Check https://repology.org/project/bchoppr/versions for other systems

b) Build your own binaries in the following three steps.

Step 1: [Download the latest published version](https://github.com/sjaehn/BChoppr/releases) of B.Choppr. Or clone or
[download the master](https://github.com/sjaehn/BChoppr/archive/master.zip) of this repository.

Step 2: Install pkg-config and the development packages for x11, cairo, and lv2 if not done yet. On
Debian-based systems you may run:
```
sudo apt-get install pkg-config libx11-dev libcairo2-dev lv2-dev
```

Step 3: Building and installing into the default lv2 directory (/usr/lib/lv2/) is easy. Simply call:

```
make
sudo make install
```

from the directory where you downloaded the repository files. For installation into an
alternative directory (e.g., /usr/local/lib/lv2), change the variable `PREFIX` while installing:

```
sudo make install PREFIX=/usr/local
```


## Running

After the installation Ardour, Carla, and any other LV2 host should automatically detect B.Choppr.

If jalv is installed, you can also call it

```
jalv.gtk https://www.jahnichen.de/plugins/lv2/BChoppr
```

to run it (pseudo) stand-alone and connect it to the JACK system.

Note: **Jack transport is required to get information about beat / position**

## Usage

The plugin slices a stereo input stream, amplifies or silences the individual slices and send the whole
sequence to the output. Although this affects only the audio signal, it needs a playback running
(Jack transport).

In addition to the global controllers, the interface is divided into three parts: step controls,
monitor and step shape.

### Global
* **Bypass** : Bypass B.Choppr
* **Dry/wet** : Dry / wet mixing

### Step controls
* **Step markers** : Defines the size of each step. Drag markers to relocate. Right click to switch between automatic and manual placement
* **Step level control** : Sound level for each individual step
* **Sequences per bar** : Number of sequences in one bar (1..8)
* **Steps swing** : Sets all automatic markers to a swing pattern (1:3..3:1)
* **Auto markers** : Sets all markers to automatic placement
* **Number of steps** : Number of steps in one sequence (1..16)

### Monitor
* **On/Off switch** : Switches monitor and monitor <-> plugin communication on/off. Reduces CPU load.
* **Monitor** : Visualization (l + r signal) the input / output signal for a whole sequence. Use mouse wheel or drag to zoom in or out.

### Step shape
* **Blend** : Select between linear (for trapezoid shapes) and sinusoidal blend between the steps
* **Attack** : Time (fraction of the respective step length) to increase the level at the begin of each step
* **Decay** : Time (fraction of the respective step length) to decrease the level at the end of each step
* **Monitor** : Visualization of a single step

## What's new
* Set all markers to "auto" at once
* Steps swing option
* Plugin description and video tutorial linked

## Links
* Tutorial video: https://youtu.be/PuzoxiAs-h8
