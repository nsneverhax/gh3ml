### Note: this readme is still a wip and probably will be for a while! Feel free to join the discord and ask as I am very active there.

[Latest Release](https://github.com/nsneverhax/nylon/releases)
### Sections
[How To Install](#how-to-install)\
[How do I Make a Mod?](#how-do-i-make-a-mod)

### Need Additional Help?
[Neverhax Server](https://discord.gg/h4KY26nyya)

## How To Install
1) Get the latest release [here](https://github.com/nsneverhax/nylon/releases).
2) Locate your Guitar Hero III exe directory (this is typically located at `%ProgramFiles(x86)%/Aspyr/Guitar Hero III/`
3) Drag the contents of the release folder into your Guitar Hero III exe directory.

## How do I Make a Mod
For right now, the GUI is still being worked on, until then follow these steps:

1) Copy the test mod folder located in your nylon mods folder.
2) Name the copied folder whatever you'd like
3) Open your new mod folder, and find ``modinfo.json`` and open it in you're text editor of choice.
4) The "name" variable here, refers to the unique identifier to your mod. I would recommend something like.. ``vultumast.mymod``
5) Place the pak you wish to load into the "pak" folder, which is in the same directory as ``modinfo.json`` (create it if it's not)
6) Rename the pak file to be ``<yourmodname>.pak.xen`` ex: ``vultumast.mymod.pak.xen``