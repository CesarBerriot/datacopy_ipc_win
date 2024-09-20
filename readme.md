# datacopy_ipc_win
Showcases Inter-Process Communication on Windows using the [DataCopy API](https://learn.microsoft.com/en-us/windows/win32/dataxchg/data-copy).

## FAQ
> ### Is it production ready ?
Except for the following, all code is error-checked.
- standard i/o functions (`scanf`, `printf`, `puts`...)
- `signal`/`raise`
- `malloc`

<br>

> ### Compiling
This project should function under any non-obsolete CMake and MinGW versions, although this is my exact setup :
- CMake v3.27.8
- MinGW-w64 v11.0

<br>

> ### Usage
Simply run the receiver and as many clients as you wish in any order and start sending messages.

<br>

> ### Learn More
This project uses Microsoft's [DataCopy API](https://learn.microsoft.com/en-us/windows/win32/dataxchg/data-copy)
along with [Joseph M. Newcomer's technique](http://www.flounder.com/wm_copydata.htm) to make WM_COPYDATA safe (see *WM_COPYDATA hazards* and *Making WM_COPYDATA safe*).