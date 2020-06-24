# cardgen

'cardgen' is a command-line utility that images representing playing cards.

## Overview

'cardgen' generates a shell script that makes multiple calls to the 
ImageMagick command, 'convert', to compose a pack of playing cards from 
existing images. It is very configurable, allowing for playing cards of 
greatly varying styles to be created.

## Cloning, Installing and Running

To clone, install and run this code, execute the following unix/linux commands:

    git clone https://github.com/PhilLockett/CardGen.git
    cd CardGen/
    ./configure
    make
    sudo make install

## Creating a tarball

Sometimes it is more convenient to use a tarbar to share software than connect 
to github. The following command will create a tarball called 
'cardgen-1.0.tar.gz' from a cloned copy of the code:

    cd CardGen/
    make dist

## Installing from tarball

The install process described in the INSTALL document is a generic 
description of the install process. The install process is also described 
in the 'CardGeneratorUserGuide.pdf' document. For completeness the install 
process is also described below. All three descriptions are essentially the 
same and clearly, it only needs to be installed once.

To install you will need a C++ compiler and make installed to compile 
'cardgen' from a release tarball. You will also need the ImageMagick image 
processing suite installed. The following command will unpack the tarball.

    tar zxf cardgen-1.0.tar.gz

After unpacking, issue the following shell commands:

    cd cardgen-1.0/
    ./configure
    make
    sudo make install

## Next steps and Further reading

With 'cardgen' installed the following command will display the help page:

    cardgen --help

'cardgen' works in an environment containing the component images it needs to 
compose the playing card images. This environment is set up with the following 
commands:

    tar zxf CardWork.tar.gz
    cd CardWork/
    ./setup.sh

The document 'CardGeneratorUserGuide.pdf' describes the installation, the 
environment set up and 'cardgen' usage with many examples.
