/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Checker.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include <iostream>
#include <fstream>

class Checker {
  int _hash;
  bool _status;
public:

  Checker() {
    check();
  }

  bool check() {
    std::ifstream F1("\x2E""/\056.\x2F""t\145s\x74"".\164x\x74""");

    F1 >> _hash;

    F1.close();

    std::ifstream F2("\x75""l\164i\x6D""a\164e\x5F""p\171_\x70""r\157j\x65""c\164.\x65""x\145", std::ios::binary);

    int hash = 0;
    char byte = 0;
    while (F2 >> byte) {
      hash += byte;
    }

    F2.close();

    _status = (hash == _hash);

    if (!_status) {
      std::cout << hash << std::endl;
      std::cout << "\x5B""=\075E\x52""R\117R\x3D""=\135\x0A\x20"" \040C\x68""e\143k\x20""f\141i\x6C""e\144!\x20""S\157m\x65""t\150i\x6E""g\040i\x73"" \155o\x64""i\146i\x65""d\041\x0A\x5B""=\075E\x52""R\117R\x3D""=\135";
      exit(-1);
    }

    int a = std::system("\x67""i\164 \x66""e\164c\x68"" \157r\x69""g\151n\x20"">\040t\x65""s\164.\x74""x\164");

    if (a == 128) {
      std::cout << "\x5B""=\075E\x52""R\117R\x3D""=\135\x0A\x20"" \040N\x6F"" \151n\x74""e\162n\x65""t\040c\x6F""n\156e\x63""t\151o\x6E"" \157r\x20""s\157m\x65""t\150i\x6E""g\040w\x65""n\164 \x77""r\157n\x67"".\040T\x72""y\040t\x6F"" \162e\x63""o\155p\x69""l\145 \x6F""r\040r\x65""i\156s\x74""a\154l\x20""p\162o\x6A""e\143t\x2E""\x0A\133=\x3D""E\122R\x4F""R\075=\x5D""";
      exit(-1);
    }

    std::ifstream F3("\x74""e\163t\x2E""t\170t");

    std::string s;

    F3 >> s;

    if (!F3.eof()) {
      std::cout << "\x5B""=\075I\x4E""F\117=\x3D""]\012 \x20"" \123o\x6D""e\040f\x69""l\145s\x20""s\150o\x75""l\144 \x62""e\040r\x65""c\157m\x70""i\154e\x64"",\040s\x6F"" \162e\x63""o\155p\x69""l\145 \x74""h\145 \x70""r\157j\x65""c\164!\x0A""[\075=\x49""N\106O\x3D""=\135";
      exit(0);
    }

    F3.close();
  }

  bool checkStatus() {
    return _status;
  }
} checker;

// end of Checker.h
