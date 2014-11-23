// Copyright (c) Warwick Allison, 1999.
// Qt4 conversion copyright (c) Ray Chason, 2012-2014.
// NetHack may be freely redistributed.  See license for details.

// qt4main.cpp -- the main window

extern "C" {
#include "hack.h"
}
#include "patchlevel.h"
#undef Invisible
#undef Warning
#undef index
#undef msleep
#undef rindex
#undef wizard
#undef yn

#include <QtGui/QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QtWidgets>
#endif
#include "qt4main.h"
#include "qt4main.moc"
#include "qt4bind.h"
#include "qt4glyph.h"
#include "qt4inv.h"
#include "qt4key.h"
#include "qt4map.h"
#include "qt4msg.h"
#include "qt4set.h"
#include "qt4stat.h"
#include "qt4str.h"

#ifndef KDE
#include "qt4kde0.moc"
#endif

// temporary
extern char *qt_tilewidth;
extern char *qt_tileheight;
extern int qt_compact_mode;
// end temporary

namespace nethack_qt4 {

// temporary
void centerOnMain( QWidget* w );
// end temporary

/* XPM */
static const char * nh_icon[] = {
"40 40 6 1",
" 	s None c none",
".	c #ffffff",
"X	c #dadab6",
"o	c #6c91b6",
"O	c #476c6c",
"+	c #000000",
"                                        ",
"                                        ",
"                                        ",
"        .      .X..XX.XX      X         ",
"        ..   .....X.XXXXXX   XX         ",
"        ... ....X..XX.XXXXX XXX         ",
"   ..   ..........X.XXXXXXXXXXX   XX    ",
"   .... ........X..XX.XXXXXXXXX XXXX    ",
"   .... ..........X.XXXXXXXXXXX XXXX    ",
"   ooOOO..ooooooOooOOoOOOOOOOXX+++OO++  ",
"   ooOOO..ooooooooOoOOOOOOOOOXX+++OO++  ",
"   ....O..ooooooOooOOoOOOOOOOXX+XXXX++  ",
"   ....O..ooooooooOoOOOOOOOOOXX+XXXX++  ",
"   ..OOO..ooooooOooOOoOOOOOOOXX+++XX++  ",
"    ++++..ooooooooOoOOOOOOOOOXX+++ +++  ",
"     +++..ooooooOooOOoOOOOOOOXX+++  +   ",
"      ++..ooooooooOoOOOOOOOOOXX+++      ",
"        ..ooooooOooOOoOOOOOOOXX+++      ",
"        ..ooooooooOoOOOOOOOOOXX+++      ",
"        ..ooooooOooOOoOOOOOOOXX+++      ",
"        ..ooooooooOoOOOOOOOOOXX+++      ",
"         ..oooooOooOOoOOOOOOXX+++       ",
"         ..oooooooOoOOOOOOOOXX+++       ",
"          ..ooooOooOOoOOOOOXX+++        ",
"          ..ooooooOoOOOOOOOXX++++       ",
"        ..o..oooOooOOoOOOOXX+XX+++      ",
"       ...o..oooooOoOOOOOXX++XXX++      ",
"      ....OO..ooOooOOoOOXX+++XXXX++     ",
"     ...oo..+..oooOoOOOXX++XXooXXX++    ",
"    ...ooo..++..OooOOoXX+++XXooOXXX+    ",
"   ..oooOOXX+++....XXXX++++XXOOoOOXX+   ",
"   ..oooOOXX+++ ...XXX+++++XXOOooOXX++  ",
"   ..oooOXXX+++  ..XX+++  +XXOOooOXX++  ",
"   .....XXX++++             XXXXXXX++   ",
"    ....XX++++              XXXXXXX+    ",
"     ...XX+++                XXXXX++    ",
"                                        ",
"                                        ",
"                                        ",
"                                        "};
/* XPM */
static const char * nh_icon_small[] = {
/* width height ncolors chars_per_pixel */
"16 16 16 1",
/* colors */
"  c #587070",
". c #D1D5C9",
"X c #8B8C84",
"o c #2A2A28",
"O c #9AABA9",
"+ c #6A8FB2",
"@ c #C4CAC4",
"# c #B6BEB6",
"$ c None",
"% c #54564E",
"& c #476C6C",
"* c #ADB2AB",
"= c #ABABA2",
"- c #5E8295",
"; c #8B988F",
": c #E8EAE7",
/* pixels */
"$$$$$$$$$$$$$$$$",
"$$$.$#::.#==*$$$",
"$.*:::::....#*=$",
"$@#:..@#*==#;XX;",
"$@O:+++- &&; X%X",
"$#%.+++- &&;% oX",
"$$o.++-- &&;%%X$",
"$$$:++-- &&;%%$$",
"$$$.O++- &&=o $$",
"$$$=:++- & XoX$$",
"$$*:@O--  ;%Xo$$",
"$*:O#$+--;oOOX $",
"$:+ =o::=oo=-;%X",
"$::.%o$*;X;##@%$",
"$$@# ;$$$$$=*;X$",
"$$$$$$$$$$$$$$$$"
};

#if 0 // RLC
/* XPM */
static const char * map_xpm[] = {
"12 13 4 1",
".	c None",
" 	c #000000000000",
"X	c #0000B6DAFFFF",
"o	c #69A69248B6DA",
"           .",
" XXXXX ooo  ",
" XoooX o    ",
" XoooX o o  ",
" XoooX ooo  ",
" XXoXX o    ",
"  oooooXXX  ",
" oo o oooX  ",
"    o XooX  ",
" oooo XooX  ",
" o  o XXXX  ",
"            ",
".           "};
/* XPM */
static const char * msg_xpm[] = {
"12 13 4 1",
".	c None",
" 	c #FFFFFFFFFFFF",
"X	c #69A69248B6DA",
"o	c #000000000000",
"           .",
" XXX XXX X o",
"           o",
" XXXXX XX  o",
"           o",
" XX XXXXX  o",
"           o",
" XXXXXX    o",
"           o",
" XX XXX XX o",
"           o",
"           o",
".ooooooooooo"};
/* XPM */
static const char * stat_xpm[] = {
"12 13 5 1",
"  c None",
".	c #FFFF00000000",
"X	c #000000000000",
"o	c #FFFFFFFF0000",
"O	c #69A6FFFF0000",
"            ",
"            ",
"...         ",
"...X        ",
"...X    ... ",
"oooX    oooX",
"oooXooo oooX",
"OOOXOOOXOOOX",
"OOOXOOOXOOOX",
"OOOXOOOXOOOX",
"OOOXOOOXOOOX",
"OOOXOOOXOOOX",
" XXXXXXXXXXX"};
#endif
/* XPM */
static const char * info_xpm[] = {
"12 13 4 1",
"  c None",
".	c #00000000FFFF",
"X	c #FFFFFFFFFFFF",
"o	c #000000000000",
"    ...     ",
"  .......   ",
" ...XXX...  ",
" .........o ",
"...XXXX.... ",
"....XXX....o",
"....XXX....o",
"....XXX....o",
" ...XXX...oo",
" ..XXXXX..o ",
"  .......oo ",
"   o...ooo  ",
"     ooo    "};


/* XPM */
static const char * again_xpm[] = {
"12 13 2 1",
" 	c None",
".	c #000000000000",
"    ..      ",
"     ..     ",
"   .....    ",
" .......    ",
"...  ..  .. ",
"..  ..   .. ",
"..        ..",
"..        ..",
"..        ..",
" ..      .. ",
" .......... ",
"   ......   ",
"            "};
/* XPM */
static const char * kick_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #000000000000",
"X	c #FFFF6DB60000",
"            ",
"            ",
"   .  .  .  ",
"  ...  .  . ",
"   ...  .   ",
"    ...  .  ",
"     ...    ",
"XXX   ...   ",
"XXX.  ...   ",
"XXX. ...    ",
"XXX. ..     ",
" ...        ",
"            "};
/* XPM */
static const char * throw_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #FFFF6DB60000",
"X	c #000000000000",
"            ",
"            ",
"            ",
"            ",
"....     X  ",
"....X     X ",
"....X XXXXXX",
"....X     X ",
" XXXX    X  ",
"            ",
"            ",
"            ",
"            "};
/* XPM */
static const char * fire_xpm[] = {
"12 13 5 1",
" 	c None",
".	c #B6DA45140000",
"X	c #FFFFB6DA9658",
"o	c #000000000000",
"O	c #FFFF6DB60000",
" .          ",
" X.         ",
" X .        ",
" X .o       ",
" X  .    o  ",
" X  .o    o ",
"OOOOOOOOoooo",
" X  .o    o ",
" X . o   o  ",
" X .o       ",
" X. o       ",
" . o        ",
"  o         "};
/* XPM */
static const char * get_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #000000000000",
"X	c #FFFF6DB60000",
"            ",
"     .      ",
"    ...     ",
"   . . .    ",
"     .      ",
"     .      ",
"            ",
"   XXXXX    ",
"   XXXXX.   ",
"   XXXXX.   ",
"   XXXXX.   ",
"    .....   ",
"            "};
/* XPM */
static const char * drop_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #FFFF6DB60000",
"X	c #000000000000",
"            ",
"   .....    ",
"   .....X   ",
"   .....X   ",
"   .....X   ",
"    XXXXX   ",
"            ",
"      X     ",
"      X     ",
"    X X X   ",
"     XXX    ",
"      X     ",
"            "};
/* XPM */
static const char * eat_xpm[] = {
"12 13 4 1",
" 	c None",
".	c #000000000000",
"X	c #FFFFB6DA9658",
"o	c #FFFF6DB60000",
"  .X.  ..   ",
"  .X.  ..   ",
"  .X.  ..   ",
"  .X.  ..   ",
"  ...  ..   ",
"   ..  ..   ",
"   ..  ..   ",
"   oo  oo   ",
"   oo  oo   ",
"   oo  oo   ",
"   oo  oo   ",
"   oo  oo   ",
"   oo  oo   "};
/* XPM */
static const char * rest_xpm[] = {
"12 13 2 1",
" 	c None",
".	c #000000000000",
"  .....     ",
"     .      ",
"    .       ",
"   .    ....",
"  .....   . ",
"         .  ",
"        ....",
"            ",
"     ....   ",
"       .    ",
"      .     ",
"     ....   ",
"            "};
/* XPM */
static const char * cast_a_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #FFFF6DB60000",
"X	c #000000000000",
"    .       ",
"    .       ",
"   ..       ",
"   ..       ",
"  ..  .     ",
"  ..  .     ",
" ......     ",
" .. ..  XX  ",
"    .. X  X ",
"   ..  X  X ",
"   ..  XXXX ",
"   .   X  X ",
"   .   X  X "};
/* XPM */
static const char * cast_b_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #FFFF6DB60000",
"X	c #000000000000",
"    .       ",
"    .       ",
"   ..       ",
"   ..       ",
"  ..  .     ",
"  ..  .     ",
" ......     ",
" .. .. XXX  ",
"    .. X  X ",
"   ..  XXX  ",
"   ..  X  X ",
"   .   X  X ",
"   .   XXX  "};
/* XPM */
static const char * cast_c_xpm[] = {
"12 13 3 1",
" 	c None",
".	c #FFFF6DB60000",
"X	c #000000000000",
"    .       ",
"    .       ",
"   ..       ",
"   ..       ",
"  ..  .     ",
"  ..  .     ",
" ......     ",
" .. ..  XX  ",
"    .. X  X ",
"   ..  X    ",
"   ..  X    ",
"   .   X  X ",
"   .    XX  "};

static QString
aboutMsg()
{
    QString msg;
    msg.sprintf(
    "Qt NetHack is a version of NetHack built\n"
#ifdef KDE
    "using KDE and the Qt GUI toolkit.\n"
#else
    "using the Qt GUI toolkit.\n"
#endif
    "This is version %d.%d.%d\n\n"
    "Homepage:\n     http://trolls.troll.no/warwick/nethack/\n\n"
#ifdef KDE
	  "KDE:\n     http://www.kde.org\n"
#endif
	  "Qt:\n     http://www.troll.no",
	VERSION_MAJOR,
	VERSION_MINOR,
	PATCHLEVEL);
    return msg;
}

class SmallToolButton : public QToolButton {
public:
    SmallToolButton(const QPixmap & pm, const QString &textLabel,
                 const QString& grouptext,
                 QObject * receiver, const char* slot,
                 QWidget * parent) :
	QToolButton(parent)
    {
	setIcon(QIcon(pm));
	setToolTip(textLabel);
	setStatusTip(grouptext);
	connect(this, SIGNAL(clicked(bool)), receiver, slot);
    }

    QSize sizeHint() const
    {
	// get just a couple more pixels for the map
	return QToolButton::sizeHint()-QSize(0,2);
    }
};

NetHackQtMainWindow::NetHackQtMainWindow(NetHackQtKeyBuffer& ks) :
    message(0), map(0), status(0), invusage(0),
    hsplitter(0), vsplitter(0),
    keysink(ks), dirkey(0)
{
    QToolBar* toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->setFocusPolicy(Qt::NoFocus);
    addToolBar(toolbar);
    menubar = menuBar();

    setWindowTitle("Qt NetHack");
    if ( qt_compact_mode )
	setWindowIcon(QIcon(QPixmap(nh_icon_small)));
    else
	setWindowIcon(QIcon(QPixmap(nh_icon)));

    QMenu* game=new QMenu;
    QMenu* apparel=new QMenu;
    QMenu* act1=new QMenu;
    QMenu* act2 = qt_compact_mode ? new QMenu : act1;
    QMenu* magic=new QMenu;
    QMenu* info=new QMenu;

    QMenu *help;

#ifdef KDE
    help = kapp->getHelpMenu( true, "" );
    help->addSeparator();
#else
    help = qt_compact_mode ? info : new QMenu;
#endif

    enum { OnDesktop=1, OnHandhelds=2 };
    struct Macro {
	QMenu* menu;
	const char* name;
	const char* action;
	int flags;
    } item[] = {
	{ game,		0, 0, 3},
	{ game,		"Version\tv",           "v", 3},
	{ game,		"Compilation\tAlt+V",     "\366", 3},
	{ game,		"History\tShift+V",           "V", 3},
	{ game,		"Redraw\tCtrl+R",          "\022", 0}, // useless
	{ game,		"Options\tShift+O",           "O", 3},
	{ game,		"Explore mode\tShift+X",      "X", 3},
	{ game,		0, 0, 3},
	{ game,		"Save\tSy",              "Sy", 3},
	{ game,		"Quit\tAlt+Q",                "\361", 3},

	{ apparel,	"Apparel off\tShift+A",       "A", 2},
	{ apparel,	"Remove many\tShift+A",       "A", 1},
	{ apparel,	0, 0, 3},
	{ apparel,	"Wield weapon\tw",      "w", 3},
	{ apparel,	"Exchange weapons\tx",      "x", 3},
	{ apparel,	"Two weapon combat\t#two",      "#tw", 3},
	{ apparel,	"Load quiver\tShift+Q",       "Q", 3},
	{ apparel,	0, 0, 3},
	{ apparel,	"Wear armour\tShift+W",       "W", 3},
	{ apparel,	"Take off armour\tShift+T",   "T", 3},
	{ apparel,	0, 0, 3},
	{ apparel,	"Put on non-armour\tShift+P", "P", 3},
	{ apparel,	"Remove non-armour\tShift+R", "R", 3},

	{ act1,	"Again\tCtrl+A",           "\001", 2},
	{ act1,	0, 0, 3},
	{ act1,	"Apply\ta?",            "a?", 3},
	{ act1,	"Chat\tAlt+C",            "\343", 3},
	{ act1,	"Close door\tc",        "c", 3},
	{ act1,	"Down\t>",              ">", 3},
	{ act1,	"Drop many\tShift+D",         "D", 2},
	{ act1,	"Drop\td?",             "d?", 2},
	{ act1,	"Eat\te?",              "e?", 2},
	{ act1,	"Engrave\tShift+E",           "E", 3},
	{ act1,	"Fight\tShift+F",             "F", 3},
	{ act1,	"Fire from quiver\tf",  "f", 2},
	{ act1,	"Force\tAlt+F",           "\346", 3},
	{ act1,	"Get\t,",               ",", 2},
	{ act1,	"Jump\tAlt+J",            "\352", 3},
	{ act2,	"Kick\tCtrl+D",              "\004", 2},
	{ act2,	"Loot\tAlt+L",            "\354", 3},
	{ act2,	"Open door\to",         "o", 3},
	{ act2,	"Pay\tp",               "p", 3},
	{ act2,	"Rest\t.",              ".", 2},
	{ act2,	"Ride\t#ri",            "#ri", 3},
	{ act2,	"Search\ts",            "s", 3},
	{ act2,	"Sit\tAlt+S",             "\363", 3},
	{ act2,	"Throw\tt",             "t", 2},
	{ act2,	"Untrap\t#u",             "#u", 3},
	{ act2,	"Up\t<",                "<", 3},
	{ act2,	"Wipe face\tAlt+W",       "\367", 3},

	{ magic,	"Quaff potion\tq?",     "q?", 3},
	{ magic,	"Read scroll/book\tr?", "r?", 3},
	{ magic,	"Zap wand\tz?",         "z?", 3},
	{ magic,	"Zap spell\tShift+Z",        "Z", 3},
	{ magic,	"Dip\tAlt+D",             "\344", 3},
	{ magic,	"Rub\tAlt+R",             "\362", 3},
	{ magic,	"Invoke\tAlt+I",          "\351", 3},
	{ magic,	0, 0, 3},
	{ magic,	"Offer\tAlt+O",           "\357", 3},
	{ magic,	"Pray\tAlt+P",            "\360", 3},
	{ magic,	0, 0, 3},
	{ magic,	"Teleport\tCtrl+T",        "\024", 3},
	{ magic,	"Monster action\tAlt+M",  "\355", 3},
	{ magic,	"Turn undead\tAlt+T",     "\364", 3},

	{ help,		"Help\t?",              "?", 3},
	{ help,		0, 0, 3},
	{ help,		"What is here\t:",      ":", 3},
	{ help,		"What is there\t;",      ";", 3},
	{ help,		"What is...\t/y",        "/y", 2},
	{ help,		0, 0, 1},

	{ info,		"Inventory\ti",         "i", 3},
#ifdef SLASHEM
	{ info,		"Angbandish inventory\t*",    "*", 3},
#endif
	{ info,		"Conduct\t#co",         "#co", 3},
	{ info,		"Discoveries\t\\",      "\\", 3},
	{ info,		"List/reorder spells\t+",     "+", 3},
	{ info,		"Adjust letters\tAlt+A",  "\341", 2},
	{ info,		0, 0, 3},
	{ info,		"Name object\tAlt+N",    "\356y?", 3},
	{ info,		"Name object type\tAlt+N",    "\356n?", 3},
	{ info,		"Name creature\tShift+C",      "C", 3},
	{ info,		0, 0, 3},
	{ info,		"Qualifications\tAlt+E",  "\345", 3},

	{ 0, 0, 0, 0 }
    };

    int i;

    game->addAction("Qt settings...",this,SLOT(doQtSettings(bool)));
    help->addAction("About Qt NetHack...",this,SLOT(doAbout(bool)));
    //help->addAction("NetHack Guidebook...",this,SLOT(doGuidebook(bool)));
    help->addSeparator();

    for (i=0; item[i].menu; i++) {
	if ( item[i].flags & (qt_compact_mode ? 1 : 2) ) {
	    if (item[i].name) {
		QString name = item[i].name;
		if ( qt_compact_mode ) // accelerators aren't
		    name.replace(QRegExp("\t.*"),"");
		QAction *action = item[i].menu->addAction(name);
		action->setData(item[i].action);
	    } else {
		item[i].menu->addSeparator();
	    }
	}
    }

    game->setTitle("Game");
    menubar->addMenu(game);
    apparel->setTitle("Gear");
    menubar->addMenu(apparel);

    if ( qt_compact_mode ) {
	act1->setTitle("A-J");
	menubar->addMenu(act1);
	act2->setTitle("K-Z");
	menubar->addMenu(act2);
	magic->setTitle("Magic");
	menubar->addMenu(magic);
	info->setIcon(QIcon(QPixmap(info_xpm)));
	info->setTitle("Info");
	menubar->addMenu(info);
	//menubar->insertItem(QPixmap(map_xpm), this, SLOT(raiseMap()));
	//menubar->insertItem(QPixmap(msg_xpm), this, SLOT(raiseMessages()));
	//menubar->insertItem(QPixmap(stat_xpm), this, SLOT(raiseStatus()));
	info->addSeparator();
	info->addAction("Map", this, SLOT(raiseMap()));
	info->addAction("Messages", this, SLOT(raiseMessages()));
	info->addAction("Status", this, SLOT(raiseStatus()));
    } else {
	act1->setTitle("Action");
	menubar->addMenu(act1);
	magic->setTitle("Magic");
	menubar->addMenu(magic);
	info->setTitle("Info");
	menubar->addMenu(info);
	menubar->addSeparator();
	help->setTitle("Help");
	menubar->addMenu(help);
    }

    QSignalMapper* sm = new QSignalMapper(this);
    connect(sm, SIGNAL(mapped(const QString&)), this, SLOT(doKeys(const QString&)));
    QToolButton* tb;
    tb = new SmallToolButton( QPixmap(again_xpm),"Again","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "\001" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(get_xpm),"Get","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "," );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(kick_xpm),"Kick","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "\004" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(throw_xpm),"Throw","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "t" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(fire_xpm),"Fire","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "f" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(drop_xpm),"Drop","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "D" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(eat_xpm),"Eat","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "e" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(rest_xpm),"Rest","Action", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "." );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(cast_a_xpm),"Cast A","Magic", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "Za" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(cast_b_xpm),"Cast B","Magic", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "Zb" );
    toolbar->addWidget(tb);
    tb = new SmallToolButton( QPixmap(cast_c_xpm),"Cast C","Magic", sm, SLOT(map()), toolbar );
    sm->setMapping(tb, "Zc" );
    toolbar->addWidget(tb);

    connect(game,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    connect(apparel,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    connect(act1,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    if (act2 != act1)
	connect(act2,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    connect(magic,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    connect(info,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));
    connect(help,SIGNAL(triggered(QAction *)),this,SLOT(doMenuItem(QAction *)));

#ifdef KDE
    setMenu (menubar);
#endif

    int x=0,y=0;
    int w=QApplication::desktop()->width()-10; // XXX arbitrary extra space for frame
    int h=QApplication::desktop()->height()-50;

    int maxwn;
    int maxhn;
    if (qt_tilewidth != NULL) {
	maxwn = atoi(qt_tilewidth) * COLNO + 10;
    } else {
	maxwn = 1400;
    }
    if (qt_tileheight != NULL) {
	maxhn = atoi(qt_tileheight) * ROWNO * 6/4;
    } else {
	maxhn = 1024;
    }

    // Be exactly the size we want to be - full map...
    if (w>maxwn) {
	x+=(w-maxwn)/2;
	w=maxwn; // Doesn't need to be any wider
    }
    if (h>maxhn) {
	y+=(h-maxhn)/2;
	h=maxhn; // Doesn't need to be any taller
    }

    setGeometry(x,y,w,h);

    if ( qt_compact_mode ) {
	stack = new QStackedWidget(this);
	setCentralWidget(stack);
    } else {
	vsplitter = new QSplitter(Qt::Vertical);
	setCentralWidget(vsplitter);
	hsplitter = new QSplitter(Qt::Horizontal);
	invusage = new NetHackQtInvUsageWindow(hsplitter);
	vsplitter->insertWidget(0, hsplitter);
	hsplitter->insertWidget(1, invusage);
    }
}

void NetHackQtMainWindow::zoomMap()
{
    qt_settings->toggleGlyphSize();
}

void NetHackQtMainWindow::raiseMap()
{
    if ( stack->currentWidget() == map->Widget() ) {
	zoomMap();
    } else {
	stack->setCurrentWidget(map->Widget());
    }
}

void NetHackQtMainWindow::raiseMessages()
{
    stack->setCurrentWidget(message->Widget());
}

void NetHackQtMainWindow::raiseStatus()
{
    stack->setCurrentWidget(status->Widget());
}

#if 0 // RLC this isn't used
class NetHackMimeSourceFactory : public Q3MimeSourceFactory {
public:
    const QMimeSource* data(const QString& abs_name) const
    {
	const QMimeSource* r = 0;
	if ( (NetHackMimeSourceFactory*)this == Q3MimeSourceFactory::defaultFactory() )
	    r = Q3MimeSourceFactory::data(abs_name);
	else
	    r = Q3MimeSourceFactory::defaultFactory()->data(abs_name);
	if ( !r ) {
	    int sl = abs_name.length();
	    do {
		sl = abs_name.lastIndexOf('/',sl-1);
		QString name = sl>=0 ? abs_name.mid(sl+1) : abs_name;
		int dot = name.lastIndexOf('.');
		if ( dot >= 0 )
		    name = name.left(dot);
		if ( name == "map" )
		    r = new Q3ImageDrag(QImage(map_xpm));
		else if ( name == "msg" )
		    r = new Q3ImageDrag(QImage(msg_xpm));
		else if ( name == "stat" )
		    r = new Q3ImageDrag(QImage(stat_xpm));
	    } while (!r && sl>0);
	}
	return r;
    }
};
#endif

void NetHackQtMainWindow::doMenuItem(QAction *action)
{
    doKeys(action->data().toString());
}

void NetHackQtMainWindow::doQtSettings(bool)
{
    centerOnMain(qt_settings);
    qt_settings->show();
}

void NetHackQtMainWindow::doAbout(bool)
{
    QMessageBox::about(this, "About Qt NetHack", aboutMsg());
}

#if 0 // RLC this isn't used
void NetHackQtMainWindow::doGuidebook(bool)
{
    QDialog dlg(this);
    new QVBoxLayout(&dlg);
    Q3TextBrowser browser(&dlg);
    NetHackMimeSourceFactory ms;
    browser.setMimeSourceFactory(&ms);
    browser.setSource(QDir::currentPath()+"/Guidebook.html");
    if ( qt_compact_mode )
	dlg.showMaximized();
    dlg.exec();
}
#endif

void NetHackQtMainWindow::doKeys(const QString& k)
{
    keysink.Put(k.toLatin1().constData());
    qApp->exit();
}

void NetHackQtMainWindow::AddMessageWindow(NetHackQtMessageWindow* window)
{
    message=window;
    hsplitter->insertWidget(0, message->Widget());
    ShowIfReady();
}

void NetHackQtMainWindow::AddMapWindow(NetHackQtMapWindow2* window)
{
    map=window;
    vsplitter->insertWidget(1, map->Widget());
    ShowIfReady();
    connect(map,SIGNAL(resized()),this,SLOT(layout()));
}

void NetHackQtMainWindow::AddStatusWindow(NetHackQtStatusWindow* window)
{
    status=window;
    hsplitter->insertWidget(2, status->Widget());
    ShowIfReady();
}

void NetHackQtMainWindow::RemoveWindow(NetHackQtWindow* window)
{
    if (window==status) {
	status=0;
	ShowIfReady();
    } else if (window==map) {
	map=0;
	ShowIfReady();
    } else if (window==message) {
	message=0;
	ShowIfReady();
    }
}

void NetHackQtMainWindow::updateInventory()
{
    if ( invusage )
	invusage->repaint();
}

void NetHackQtMainWindow::fadeHighlighting()
{
    if (status) {
	status->fadeHighlighting();
    }
}

void NetHackQtMainWindow::layout()
{
#if 0
    if ( qt_compact_mode )
	return;
    if (message && map && status) {
	QSize maxs=map->Widget()->maximumSize();
	int maph=std::min(height()*2/3,maxs.height());

	QWidget* c = centralWidget();
	int h=c->height();
	int toph=h-maph;
	int iuw=3*qt_settings->glyphs().width();
	int topw=(c->width()-iuw)/2;

	message->Widget()->setGeometry(0,0,topw,toph);
	invusage->setGeometry(topw,0,iuw,toph);
	status->Widget()->setGeometry(topw+iuw,0,topw,toph);
	map->Widget()->setGeometry(std::max(0,(c->width()-maxs.width())/2),
				   toph,c->width(),maph);
    }
#endif
}

void NetHackQtMainWindow::resizeEvent(QResizeEvent*)
{
    layout();
#ifdef KDE
    updateRects();
#endif         
}

void NetHackQtMainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if ( dirkey ) {
	doKeys(QString(QChar(dirkey)));
	if ( !event->isAutoRepeat() )
	    dirkey = 0;
    }
}

void NetHackQtMainWindow::keyPressEvent(QKeyEvent* event)
{
    // Global key controls

    // For desktop, arrow keys scroll map, since we don't want players
    // to think that's the way to move. For handhelds, the normal way is to
    // click-to-travel, so we allow the cursor keys for fine movements.

    //  321
    //  4 0
    //  567

    if ( event->isAutoRepeat() &&
	event->key() >= Qt::Key_Left && event->key() <= Qt::Key_Down )
	return;

    const char* d = iflags.num_pad ? ndir : sdir; 
    switch (event->key()) {
     case Qt::Key_Up:
	if ( dirkey == d[0] )
	    dirkey = d[1];
	else if ( dirkey == d[4] )
	    dirkey = d[3];
	else
	    dirkey = d[2];
    break; case Qt::Key_Down:
	if ( dirkey == d[0] )
	    dirkey = d[7];
	else if ( dirkey == d[4] )
	    dirkey = d[5];
	else
	    dirkey = d[6];
    break; case Qt::Key_Left:
	if ( dirkey == d[2] )
	    dirkey = d[1];
	else if ( dirkey == d[6] )
	    dirkey = d[7];
	else
	    dirkey = d[0];
    break; case Qt::Key_Right:
	if ( dirkey == d[2] )
	    dirkey = d[3];
	else if ( dirkey == d[6] )
	    dirkey = d[5];
	else
	    dirkey = d[4];
    break; case Qt::Key_PageUp:
	dirkey = 0;
	if (message) message->Scroll(0,-1);
    break; case Qt::Key_PageDown:
	dirkey = 0;
	if (message) message->Scroll(0,+1);
    break; case Qt::Key_Space:
	if ( flags.rest_on_space ) {
	    event->ignore();
	    return;
	}
	case Qt::Key_Enter:
	if ( map )
	    map->clickCursor();
    break; default:
	dirkey = 0;
	event->ignore();
    }
}

void NetHackQtMainWindow::closeEvent(QCloseEvent* e)
{
    if ( program_state.something_worth_saving ) {
	switch ( QMessageBox::information( this, "NetHack",
	    "This will end your NetHack session",
	    "&Save", "&Cancel", 0, 1 ) )
	{
	    case 0:
		// See dosave() function
		if (dosave0()) {
		    u.uhp = -1;
		    NetHackQtBind::qt_exit_nhwindows(0);
		    terminate(EXIT_SUCCESS);
		}
		break;
	    case 1:
		break; // ignore the event
	}
    } else {
	e->accept();
    }
}

void NetHackQtMainWindow::ShowIfReady()
{
    if (message && map && status) {
	QWidget* hp = qt_compact_mode ? static_cast<QWidget *>(stack) : static_cast<QWidget *>(hsplitter);
	QWidget* vp = qt_compact_mode ? static_cast<QWidget *>(stack) : static_cast<QWidget *>(vsplitter);
	message->Widget()->setParent(hp);
	map->Widget()->setParent(vp);
	status->Widget()->setParent(hp);
	if ( qt_compact_mode ) {
	    message->setMap(map);
	    stack->addWidget(map->Widget());
	    stack->addWidget(message->Widget());
	    stack->addWidget(status->Widget());
	    raiseMap();
	} else {
	    layout();
	}
	showMaximized();
    } else if (isVisible()) {
	hide();
    }
}

} // namespace nethack_qt4
