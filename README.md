SimpleMinesweeper
=================

Simple implementation of minesweeper in C-language


## Usage

```txt
$ ./minesweeper
Start Minesweeper


  |abcdefghi
--+---------
 1|ooooooooo
 2|ooooooooo
 3|ooooooooo
 4|ooooooooo
 5|ooooooooo
 6|ooooooooo
 7|ooooooooo
 8|ooooooooo
 9|ooooooooo

where? [a-i][1-9] > a1

  |abcdefghi
--+---------
 1|.1ooooooo
 2|12ooooooo
 3|ooooooooo
 4|ooooooooo
 5|ooooooooo
 6|ooooooooo
 7|ooooooooo
 8|ooooooooo
 9|ooooooooo

where? [a-i][1-9] >
```


## Build

Use [Makefile](Makefile).

```sh
$ make
```

If you want to build with MSVC, use [msvc.mk](msvc.mk).
[msvc.mk](msvc.mk) is written for nmake.

```sh
> nmake /f msvc.mk
```


## LICENSE

This software is released under the MIT License, see [LICENSE](LICENSE).
