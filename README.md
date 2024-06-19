# mac-swap-screens

TIL you can swap your screens on your mac with some simple C code.
I have two monitors at home and they seem to swap every time I connect them. I end up clicking in the settings to rearrange them. 

After searching for a commandline solution to this problem I found this on [Stack Overflow](https://stackoverflow.com/questions/53370613/change-macos-display-arrangement-through-command-line-applescript).

I converted answer above to this small snippet of C code. This will print your monitor details and if there is exactly two of them will swap their position. Saving you lots of pointing and clicking.

## Setup

```
make
mv mac-swap-screens ~/bin # Or where ever keep your local commands
```

## Usage

```
mac-swap-screens
```