# QStandardIconsViewer
Viewer for Qt Standard Icons according to Icon Naming Specification

## Overview
The Icon Theme Specification is in use in several desktops, including KDE and Gnome.

The latest version of the freedesktop icon specification and naming specification can be obtained here:
* http://standards.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html
* http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

## Fetch an Icon from theme in Qt:
To fetch an icon from the current icon theme:
```cpp
 QIcon undoicon = QIcon::fromTheme("edit-undo");
```
