# QStandardIconsViewer
Viewer for Qt Icons:
* according to Icon Naming Specification
* MIME type database
* QStyle's standard pixmaps
* file pixmaps
* font icons

## Icon Naming Specification

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

# QMimeDatabase icons

The MIME type database is provided by the freedesktop.org shared-mime-info project.
If the MIME type database cannot be found on the system, as is the case on most Windows, macOS, and iOS systems, Qt will use its own copy of it.

Shared Mime Info specification can be obtained here
* http://standards.freedesktop.org/shared-mime-info-spec/shared-mime-info-spec-latest.html

## Fetch an Icon from QMimeDatabase:
To fetch an icon from the MIME type database:
```cpp
 QMimeDatabase db;
 QMimeType mime = db.mimeTypeForName("application/pdf");
 QIcon undoicon = QIcon::fromTheme(mime.iconName());
```

# Qt's standart pixmap

## Fetch an Icon from style in Qt:
To fetch an standard pixmap from the current style from widget:
```cpp
 QIcon trashicon = style()->standardIcon(QStyle::SP_TrashIcon);
```

# File pixmaps

## Fetch an Icon from file:
To fetch an icon from the file:
```cpp
 QPixmap pixmap(":/img/help.png")
 QIcon icon(pixmap);
```

# QIcon from a font
[QFontIcon](https://github.com/dridk/QFontIcon) is a simple Qt class that allows you to create QIcon from a font file like [font Awesome](http://fontawesome.io/).

## Usage
You just have to copy [QFontIcon](https://github.com/dridk/QFontIcon) folder into your project. And add the following line in you project file.
```
 include("QFontIcon/QFontIcon.pri")
```

You need a font file to use [QFontIcon](https://github.com/dridk/QFontIcon).
You can for exemple download [font Awesome](http://fontawesome.io/) and add it in your project
as a resource file. Then use the class as follow:

Load first the font file only one time. In the main.cpp in the most of the case.
```cpp
 QFontIcon::addFont(":/fontawesome.ttf");
```

Then you can get icon from unicode:
```cpp
 QIcon icon = QFontIcon::icon(0xf501);
```