## Metronome


## Place generated object files (.o) into the same directory as their source
## files, in order to avoid collisions when non-recursive make is used.
AUTOMAKE_OPTIONS = subdir-objects

## Additional flags to pass to aclocal when it is invoked automatically at
## make time. The ${ACLOCAL_FLAGS} variable is picked up from the environment
## to provide a way for the user to supply additional arguments.
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}



## Set the default command-line flags for the C preprocessor to the value
## obtained from pkg-config via PKG_CHECK_MODULES in configure.ac.  These
## flags are passed to the compiler for both C and C++, in addition to the
## language-specific options.
AM_CPPFLAGS = $(DEPENDENCIES_CFLAGS)



## Define an executable target "hello", which will be installed into the
## directory named by the predefined variable $(bindir).
bin_PROGRAMS = metronome

## Define the list of source files for the "hello" target. The file extension
## .cc is recognized by Automake, and causes it to produce rules which invoke
## the C++ compiler to produce an object file (.o) from each source file. The
## header files (.h) do not result in object files by themselves, but will be
## included in distribution archives of the project.
metronome_SOURCES = source/animation.cpp source/animation.h \
	            source/animeWindow.cpp source/animeWindow.h \
		    source/configurations.cpp source/configurations.h \
		    source/main.cpp source/main.h \
		    source/metronome.cpp source/metronome.h \
		    source/mySpinButton.cpp source/mySpinButton.h \
		    source/note.cpp source/note.h \
		    source/options.cpp source/options.h \
		    source/SecondaryWindow.cpp source/SecondaryWindow.h \
		    source/sound.cpp source/sound.h \
		    source/tempo.cpp source/tempo.h \
		    source/tuner.cpp source/tuner.h		 



metronome_LDADD = $(DEPENDENCIES_LIBS)



## Define an independent executable script for inclusion in the distribution
## archive. It will not be installed on an end user's system, however.
dist_noinst_SCRIPTS = autogen.sh
