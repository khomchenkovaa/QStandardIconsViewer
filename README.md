# QStandardIconsViewer
Viewer for Qt Standard Icons according to Icon Naming Specification and QStyle's standard pixmaps

## Overview
The Icon Theme Specification is in use in several desktops, including KDE and Gnome.

The latest version of the freedesktop icon specification and naming specification can be obtained here:
* http://standards.freedesktop.org/icon-theme-spec/icon-theme-spec-latest.html
* http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

A standard pixmap is a pixmap that can follow some existing GUI style or guideline.

## Fetch an Icon from theme in Qt:
To fetch an icon from the current icon theme:
```cpp
 QIcon undoicon = QIcon::fromTheme("edit-undo");
```

## Fetch an Icon from style in Qt:
To fetch an standard pixmap from the current style from widget:
```cpp
 QIcon trashicon = style()->standardIcon(QStyle::SP_TrashIcon);
```
